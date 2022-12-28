// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "StatComponent.h"
#include "MonsterCharacterBase.h"
#include "PlayableAnimInstance.h"
#include "DrawDebugHelpers.h"//������ �ڵ�

// Sets default values
APlayerCharacterBase::APlayerCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(FName("Player"));
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	CurrentStat = CreateDefaultSubobject<UStatComponent>(TEXT("STAT"));

	SpringArm->TargetArmLength = 300.f;
	SpringArm->SetRelativeRotation(FRotator(-38.f, 0.f, 0.f));
	GetMesh()->SetRelativeLocationAndRotation(FVector{ 0.f, 0.f, -88.f }, FRotator{ 0.f, -90.f, 0.f });

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

}

void APlayerCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PlayerAnimInstance = Cast<UPlayableAnimInstance>(GetMesh()->GetAnimInstance());
	if (PlayerAnimInstance)
	{
		PlayerAnimInstance->OnMontageEnded.AddDynamic(this, &APlayerCharacterBase::OnPrimaryAttackMontageEnded);
	}
}

// Called when the game starts or when spawned
void APlayerCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	auto WeaponComp = GetComponentsByClass(UCapsuleComponent::StaticClass());
	for (const auto& Comp : WeaponComp)
	{
		if (Comp->ComponentHasTag(FName(TEXT("WeaponComponent"))))
		{
			WeaponCollisionComponent = Cast<UCapsuleComponent>(Comp);
			Cast<UCapsuleComponent>(Comp)->SetCollisionProfileName("NoCollision");

			WeaponCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacterBase::OnOverlapBegin);
			WeaponCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacterBase::OnOverlapEnd);
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Player Spawn Complete!"));
	UE_LOG(LogTemp, Log, TEXT("PlayerName : %s"), *CurrentStat->GetName());
	UE_LOG(LogTemp, Log, TEXT("PlayerLevel : %d"), CurrentStat->GetLevel());
	UE_LOG(LogTemp, Log, TEXT("PlayerAtk : %d"), CurrentStat->GetAtk());
	UE_LOG(LogTemp, Log, TEXT("PlayerExp : %d"), CurrentStat->GetExp());
	UE_LOG(LogTemp, Log, TEXT("PlayerHp : %d"), CurrentStat->GetHp());
	UE_LOG(LogTemp, Log, TEXT("PlayerSp : %d"), CurrentStat->GetSp());
	UE_LOG(LogTemp, Log, TEXT("PlayerMp : %d"), CurrentStat->GetMp());
}

// Called every frame
void APlayerCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float APlayerCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	CurrentStat->OnAttacked(DamageAmount);

	return DamageAmount;
}

void APlayerCharacterBase::ChangeComponentCollisionRule()
{
	if (bIsAttacking)
	{
		//AnimMontage�� ���� ���� ���� ���°� �Ǹ� WeaponCollision�� Ȱ��ȭ
		WeaponCollisionComponent->SetCollisionProfileName("Weapon");
	}
	else
	{
		//��ҿ��� ���ʿ��� �浹�� ���̱� ���� WeaponCollision�� ��Ȱ��ȭ
		WeaponCollisionComponent->SetCollisionProfileName("NoCollision");
	}
}

void APlayerCharacterBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsAttacking)
	{
		return;
	}

	if (!OtherActor->ActorHasTag(FName(TEXT("Monster"))))
	{
		return;
	}
	
	if (FString(TEXT("CharacterMesh0")) != OtherComp->GetName())
	{
		return;
	}

	if (bIsOverlapped)
	{
		return;
	}

	FDamageEvent DamageEvent;
	OtherActor->TakeDamage(CurrentStat->GetAtk(), DamageEvent, GetController(), this);
	bIsOverlapped = true;

	++TestAttackCount;
	UE_LOG(LogTemp, Log, TEXT("[HitActor : %s] [HiComponent : %s] Attack : %d!"), *OtherActor->GetName(), *OtherComp->GetName(), TestAttackCount);
}

void APlayerCharacterBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!bIsAttacking)
	{
		return;
	}

	if (!OtherActor->ActorHasTag(FName(TEXT("Monster"))))
	{
		return;
	}

	if (FString(TEXT("CharacterMesh0")) != OtherComp->GetName())
	{
		return;
	}

	if (bIsOverlapped)
	{
		//Cast<AMonsterCharacterBase>(OtherActor)->IsAttacked(true);

		UE_LOG(LogTemp, Log, TEXT("[HitActor : %s] [HiComponent : %s] AttackEnd : %d!"), *OtherActor->GetName(), *OtherComp->GetName(), TestAttackCount);
	}

}

void APlayerCharacterBase::PrimaryAttack()
{
	if (bIsPlayAnimation)
	{
		return;
	}

	PlayerAnimInstance->PlayPrimaryAttackMontage();
	PlayerAnimInstance->JumpToSection(AttackIndex);
	AttackIndex = (AttackIndex + 1) % 3;

	bIsPlayAnimation = true;
}

void APlayerCharacterBase::OnPrimaryAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	bIsPlayAnimation = false;
}
