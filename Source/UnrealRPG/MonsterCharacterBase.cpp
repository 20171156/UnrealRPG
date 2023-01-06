// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterCharacterBase.h"
#include "MonsterStatComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MonsterHpWidget.h"
#include "MonsterAnimInstance.h"
#include "WeaponAnimInstance.h"
#include "MonsterAIController.h"

// Sets default values
AMonsterCharacterBase::AMonsterCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(FName("Monster"));

	CurrentStat = CreateDefaultSubobject<UMonsterStatComponent>(TEXT("STAT"));
	HpBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HP_WIDGET"));

	HpBarWidget->SetupAttachment(GetMesh());
	HpBarWidget->SetDrawSize(FVector2D(200.f, 50.f));
	HpBarWidget->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
	HpBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HpBarWidget->SetCollisionProfileName("NoCollision");

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
}

void AMonsterCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	HpBarWidget->InitWidget();
	auto HpWidget = Cast<UMonsterHpWidget>(HpBarWidget->GetUserWidgetObject());
	if (HpWidget)
	{
		HpWidget->BindHp(CurrentStat);
	}

	MonsterAnimInstance = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	if (MonsterAnimInstance)
	{
		MonsterAnimInstance->OnMontageStarted.AddDynamic(this, &AMonsterCharacterBase::OnAnimMontageStarted);
		MonsterAnimInstance->OnMontageEnded.AddDynamic(this, &AMonsterCharacterBase::OnAnimMontageEnded);
		MonsterAnimInstance->OnWeaponAnimChange.AddUObject(this, &AMonsterCharacterBase::PlayWeaponAnimation);
		MonsterAnimInstance->OnWeaponAnimStop.AddUObject(this, &AMonsterCharacterBase::StopWeaponAnimation);
	}

	auto SkelComps = GetComponentsByTag(USkeletalMeshComponent::StaticClass(), FName{ TEXT("WeaponComponent") });
	for (auto SkelComp : SkelComps)
	{
		USkeletalMeshComponent* SMComp = Cast<USkeletalMeshComponent>(SkelComp);
		if (nullptr != SMComp)
		{
			WeaponAnimInstance = Cast<UWeaponAnimInstance>(SMComp->GetAnimInstance());
		}
	}

	CurrentStat->MonsterHpZero.AddUObject(this, &AMonsterCharacterBase::MonsterHpZero);
}

// Called when the game starts or when spawned
void AMonsterCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	//Archery Monster
	for (const auto& Tag : Tags)
	{
		FString StringTag = Tag.ToString();
		if (StringTag.Contains(FString(TEXT("Archer"))))
		{
			bIsArchery = true;
			break;
		}
	}
}

// Called every frame
void AMonsterCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonsterCharacterBase::SetState(const EMonsterAnimState NewState)
{
	if (NewState != CurrentAnimState)
	{
		PreviousAnimState = CurrentAnimState;
	}

	CurrentAnimState = NewState;
}

void AMonsterCharacterBase::ChangeCollisionProfile()
{
	//if (bableAttacking)
	//{
	//	//AnimMontage�� ���� ���� ���� ���°� �Ǹ� WeaponCollision�� Ȱ��ȭ
	//	WeaponCollisionComponent->SetCollisionProfileName("Weapon");
	//}
	//else
	//{
	//	//��ҿ��� ���ʿ��� �浹�� ���̱� ���� WeaponCollision�� ��Ȱ��ȭ
	//	WeaponCollisionComponent->SetCollisionProfileName("NoCollision");
	//}
}

void AMonsterCharacterBase::ExecuteAnimMontage(const EMonsterAnimState MonsterAnimState)
{
	switch (MonsterAnimState)
	{
	case EMonsterAnimState::PEACE:
	{
		break;
	}
	case EMonsterAnimState::CHASE:
	{
		break;
	}
	case EMonsterAnimState::ATTACKING:
	{
		MonsterAnimInstance->PlayPrimaryAttackMontage();
		break;
	}
	case EMonsterAnimState::ATTACKED:
	{
		MonsterAnimInstance->PlayAttackedMontage();
		break;
	}
	case EMonsterAnimState::DEAD:
	{
		MonsterAnimInstance->PlayDyingMontage();
		break;
	}
	default:
		break;
	}
}

void AMonsterCharacterBase::OnAnimMontageStarted(UAnimMontage* Montage)
{
	FString MontageName = Montage->GetName();
	UE_LOG(LogTemp, Log, TEXT("[Start MontageName : %s]"), *MontageName);
}

void AMonsterCharacterBase::OnAnimMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	FString MontageName = Montage->GetName();

	if (bInterrupted)
	{
		UE_LOG(LogTemp, Log, TEXT("[End MontageName : %s(Interrupted Case)]"), *MontageName);
	}
	else
	{
		if (MontageName.Contains(FString(TEXT("Attacked"))))
		{
			SetState(PreviousAnimState);
		}
		else if (MontageName.Contains(FString(TEXT("PrimaryAttack"))))
		{
			OnMonsterAttackEnd.Broadcast();
		}
		else if (MontageName.Contains(FString(TEXT("Dying"))))
		{
			Destroy();
		}
		UE_LOG(LogTemp, Log, TEXT("[End MontageName : %s]"), *MontageName);
	}

}

float AMonsterCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	CurrentStat->OnAttacked(DamageAmount);

	SetState(EMonsterAnimState::ATTACKED);
	bIsAttacked = true;

	OnMonsterAttackEnd.Broadcast();//� ������ ai�� �ߴܽ��Ѿ� ��(�ϴ� attack���¸� �ߴܽ�Ű��)
	ExecuteAnimMontage(EMonsterAnimState::ATTACKED);

	return DamageAmount;
}

void AMonsterCharacterBase::PlayWeaponAnimation(FName SectionName)
{
	WeaponAnimInstance->PlayWeaponAttackMontage();
	WeaponAnimInstance->JumpToSection(SectionName);
}

void AMonsterCharacterBase::StopWeaponAnimation()
{
	WeaponAnimInstance->StopAllMontages(0.f);
}

void AMonsterCharacterBase::MonsterHpZero()
{
	SetState(EMonsterAnimState::DEAD);
	bIsDead = true;

	OnMonsterDying.Broadcast();
	ExecuteAnimMontage(EMonsterAnimState::DEAD);

	//������ weapon�鵵 �� ���ֹ������ҵ�
	GetMesh()->SetCollisionProfileName("NoCollision");
	HpBarWidget->SetCollisionProfileName("NoCollision");
}