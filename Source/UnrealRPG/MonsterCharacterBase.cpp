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
		MonsterAnimInstance->OnMontageEnded.AddDynamic(this, &AMonsterCharacterBase::OnPrimaryAttackMontageEnded);
		MonsterAnimInstance->OnAttackHit.AddUObject(this, &AMonsterCharacterBase::AttackCheck);
		MonsterAnimInstance->OnWeaponAnimChange.AddUObject(this, &AMonsterCharacterBase::PlayWeaponAnimation);
	}

	auto Components = GetComponentsByTag(USkeletalMeshComponent::StaticClass(), FName{ TEXT("WeaponComponent") });
	for (auto Comp : Components)
	{
		USkeletalMeshComponent* SMComp = Cast<USkeletalMeshComponent>(Comp);
		if (nullptr != SMComp)
		{
			WeaponAnimInstance = Cast<UWeaponAnimInstance>(SMComp->GetAnimInstance());
			WeaponAnimInstance->OnMontageEnded.AddDynamic(this, &AMonsterCharacterBase::OnWeaponMontageEnded);
		}
	}
}

// Called when the game starts or when spawned
void AMonsterCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("Monster Spawn Complete!"));
	UE_LOG(LogTemp, Log, TEXT("MonsterName : %s"), *CurrentStat->GetMonsterName().ToString());
	UE_LOG(LogTemp, Log, TEXT("MonsterLevel : %d"), CurrentStat->GetLevel());
	UE_LOG(LogTemp, Log, TEXT("MonsterAtk : %d"), CurrentStat->GetAtk());
	UE_LOG(LogTemp, Log, TEXT("MonsterExp : %d"), CurrentStat->GetExp());
	UE_LOG(LogTemp, Log, TEXT("MonsterHp : %d"), CurrentStat->GetHp());
	UE_LOG(LogTemp, Log, TEXT("MonsterSp : %d"), CurrentStat->GetSp());
	UE_LOG(LogTemp, Log, TEXT("MonsterMp : %d"), CurrentStat->GetMp());
}

// Called every frame
void AMonsterCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMonsterCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMonsterCharacterBase::ChangeMonsterState(const EMonsterState& ChangeState)
{
	CurrentState = ChangeState;
}

void AMonsterCharacterBase::AttackCheck()
{
}

void AMonsterCharacterBase::PrimaryAttack()
{
	if (GetAttacking())
	{
		return;
	}

	MonsterAnimInstance->PlayPrimaryAttackMontage();

	if (FName{ TEXT("Archer") } != Tags[2])
	{
		MonsterAnimInstance->JumpToSection();
	}

	SetAttacking(true);
}

void AMonsterCharacterBase::PlayWeaponAnimation(FName SectionName)
{
	WeaponAnimInstance->PlayWeaponAttackMontage();
	WeaponAnimInstance->JumpToSection(SectionName);
}

void AMonsterCharacterBase::OnPrimaryAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	SetAttacking(false);

	OnMonsterAttackEnd.Broadcast();
}

void AMonsterCharacterBase::OnWeaponMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	WeaponAnimInstance->StopWeaponMontage();
}
