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
		//AnimState = MonsterAnimInstance->GetAnimState();
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
	PreviousAnimState = CurrentAnimState;
	CurrentAnimState = NewState;
}

void AMonsterCharacterBase::ChangeComponentCollisionRule()
{
	//if (bableAttacking)
	//{
	//	//AnimMontage에 의해 공격 가능 상태가 되면 WeaponCollision을 활성화
	//	WeaponCollisionComponent->SetCollisionProfileName("Weapon");
	//}
	//else
	//{
	//	//평소에는 불필요한 충돌을 줄이기 위해 WeaponCollision을 비활성화
	//	WeaponCollisionComponent->SetCollisionProfileName("NoCollision");
	//}
}

void AMonsterCharacterBase::ExecuteAnimMontage(const EMonsterAnimState MonsterAnimState)
{
	//MonsterAnimInstance->StopAllMontages(0.f);
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

}

void AMonsterCharacterBase::OnAnimMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	FString MontageName = Montage->GetName();

	if (bInterrupted)
	{
		if (MontageName.Contains(FString(TEXT("Attacked"))))
		{
			OnMonsterAttackEnd.Broadcast();//공격당해서 중단됨
		}
	}
	else//정상적으로 끝난 케이스
	{
		if (MontageName.Contains(FString(TEXT("Attacked"))))
		{
			SetState(PreviousAnimState);
		}
		else if (MontageName.Contains(FString(TEXT("PrimaryAttack"))))
		{
			OnMonsterAttackEnd.Broadcast();
		}
	}
}

float AMonsterCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	CurrentStat->OnAttacked(DamageAmount);

	SetState(EMonsterAnimState::ATTACKED);
	bIsAttacked = true;

	OnMonsterAttackedStart.Broadcast();//어떤 상태의 ai든 중단시켜야 함
	ExecuteAnimMontage(EMonsterAnimState::ATTACKED);
	
	return DamageAmount;
}

void AMonsterCharacterBase::PlayWeaponAnimation(FName SectionName)
{
	WeaponAnimInstance->PlayWeaponAttackMontage();
	WeaponAnimInstance->JumpToSection(SectionName);
}

void AMonsterCharacterBase::MonsterHpZero()
{
	SetState(EMonsterAnimState::DEAD);
	bIsDead = true;

	OnMonsterDying.Broadcast();
	ExecuteAnimMontage(EMonsterAnimState::DEAD);

	//나머지 weapon들도 다 없애버려야할듯
	GetMesh()->SetCollisionProfileName("NoCollision");
	HpBarWidget->SetCollisionProfileName("NoCollision");
}