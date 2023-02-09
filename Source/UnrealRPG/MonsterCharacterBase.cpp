// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterCharacterBase.h"
#include "MonsterStatComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
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

	//모든 WeaponComponent Collision 비활성화
	auto WeaponActors = GetComponentsByTag(UActorComponent::StaticClass(), FName{ TEXT("WeaponComponent") });
	for (const auto& WeaponActor : WeaponActors)
	{
		if (IsValid(Cast<UStaticMeshComponent>(WeaponActor)))
		{
			Cast<UStaticMeshComponent>(WeaponActor)->SetCollisionProfileName("NoCollision");
		}
		else
		{
			Cast<USkeletalMeshComponent>(WeaponActor)->SetCollisionProfileName("NoCollision");
		}
	}

	//무기 중 애니메이션을 가지는 WeaponAnim 체크
	auto SkelComps = GetComponentsByTag(USkeletalMeshComponent::StaticClass(), FName{ TEXT("WeaponComponent") });
	for (const auto& SkelComp : SkelComps)
	{
		if (IsValid(Cast<USkeletalMeshComponent>(SkelComp)))
		{
			auto comp = Cast<USkeletalMeshComponent>(SkelComp);
			WeaponAnimInstance = Cast<UWeaponAnimInstance>(comp->GetAnimInstance());
		}
	}

	//Weapon은 HitEvent가 발동해야 한다
	//무기 중 Attackable tag를 가진 무기만 Overlap 가능
	auto StaticComps = GetComponentsByTag(UActorComponent::StaticClass(), FName{ TEXT("Attackable") });
	for (const auto& StaticComp : StaticComps)
	{
		if (IsValid(Cast<UStaticMeshComponent>(StaticComp)))
		{
			WeaponComponent = Cast<UStaticMeshComponent>(StaticComp);
			WeaponComponent->BodyInstance.bNotifyRigidBodyCollision = true;
			WeaponComponent->OnComponentBeginOverlap.AddDynamic(this, &AMonsterCharacterBase::OnWeaponOverlapBegin);
			WeaponComponent->OnComponentEndOverlap.AddDynamic(this, &AMonsterCharacterBase::OnWeaponOverlapEnd);
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

float AMonsterCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CurrentStat->OnAttacked(DamageAmount);

	if (!bIsDead)
	{
		SetState(EMonsterAnimState::ATTACKED);
		bIsAttacked = true;

		OnMonsterAttackEnd.Broadcast();//어떤 상태의 ai든 중단시켜야 함(일단 attack상태만 중단시키기)
		ExecuteAnimMontage(EMonsterAnimState::ATTACKED);
	}

	return DamageAmount;
}


void AMonsterCharacterBase::SetState(const EMonsterAnimState NewState)
{
	if (NewState != CurrentAnimState)
	{
		PreviousAnimState = CurrentAnimState;
	}

	CurrentAnimState = NewState;
}

const int32 AMonsterCharacterBase::GetCurrentStat(ECharacterStatType StatType)
{
	switch (StatType)
	{
	case ECharacterStatType::LEVEL:
	{
		return CurrentStat->GetLevel();
	}
	case ECharacterStatType::HP:
	{
		return CurrentStat->GetHp();
	}
	case ECharacterStatType::SP:
	{
		return CurrentStat->GetSp();
	}
	case ECharacterStatType::MP:
	{
		return CurrentStat->GetMp();
	}
	case ECharacterStatType::ATK:
	{
		return CurrentStat->GetAtk();
	}
	case ECharacterStatType::EXP:
	{
		return CurrentStat->GetExp();
	}
	default:
	{

		break;
	}
	}

	return 0;
}

void AMonsterCharacterBase::ChangeCollisionProfile(bool bAbleOverlap)
{
	if (bAbleOverlap)
	{
		//AnimMontage에 의해 공격 가능 상태가 되면 WeaponCollision을 활성화
		WeaponComponent->SetCollisionProfileName("Weapon");
	}
	else
	{
		//평소에는 불필요한 충돌을 줄이기 위해 WeaponCollision을 비활성화
		WeaponComponent->SetCollisionProfileName("NoCollision");
		bIsAttacking = false;
	}
}

void AMonsterCharacterBase::OnWeaponOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this)
	{
		return;
	}

	if (!bIsAttacking)
	{
		if (OtherActor->ActorHasTag(FName(TEXT("Player"))))
		{
			FDamageEvent DamageEvent;
			OtherActor->TakeDamage(CurrentStat->GetAtk(), DamageEvent, GetController(), this);
			bIsAttacking = true;
		}
	}
}

void AMonsterCharacterBase::OnWeaponOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (this == OtherActor)
	{
		return;
	}

	if (bIsAttacking)
	{
	}
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
}

void AMonsterCharacterBase::OnAnimMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	FString MontageName = Montage->GetName();

	if (bInterrupted)
	{
		//UE_LOG(LogTemp, Log, TEXT("[Monster End MontageName : %s(Interrupted Case)]"), *MontageName);
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
		//else if (MontageName.Contains(FString(TEXT("Dying"))))
		//{
		//	FTimerHandle DestroyHandle;
		//	float WaitTime = 1.5f;
		//	GetWorld()->GetTimerManager().SetTimer(DestroyHandle, FTimerDelegate::CreateLambda([&]()
		//		{
		//			Destroy();
		//			GetWorldTimerManager().ClearTimer(DestroyHandle);
		//		}), WaitTime, false);
		//}
		//UE_LOG(LogTemp, Log, TEXT("[End MontageName : %s]"), *MontageName);
	}
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
	ExecuteAnimMontage(EMonsterAnimState::DEAD);
	bIsDead = true;

	GetMesh()->SetCollisionProfileName("NoCollision");

	////경험치 추가
	//CurrentStat->GetExp();
}

void AMonsterCharacterBase::CharacterDestroy()
{
	FTimerHandle DestroyHandle;
	float WaitTime = 1.5f;
	GetWorld()->GetTimerManager().SetTimer(DestroyHandle, FTimerDelegate::CreateLambda([&]()
		{
			Destroy();
			GetWorldTimerManager().ClearTimer(DestroyHandle);
		}), WaitTime, false);
}
