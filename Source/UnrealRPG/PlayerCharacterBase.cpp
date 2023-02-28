// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "StatComponent.h"
#include "Inventory.h"
#include "PlayerQuestSystem.h"
#include "MonsterCharacterBase.h"
#include "PlayableAnimInstance.h"
#include "InteractionInterface.h"

#include "UnrealRPGGameModeBase.h"
#include "DrawDebugHelpers.h"//디버깅용 코드

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

	//캐릭터 생성할 때 인벤토리 시스템, 퀘스트 시스템 생성
	Inventory = CreateDefaultSubobject<UInventory>(TEXT("INVENTORY"));
	QuestSystem = CreateDefaultSubobject<UPlayerQuestSystem>(TEXT("QUESTSYSTEM"));
}

void APlayerCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PlayerAnimInstance = Cast<UPlayableAnimInstance>(GetMesh()->GetAnimInstance());
	if (PlayerAnimInstance)
	{
		PlayerAnimInstance->OnMontageStarted.AddDynamic(this, &APlayerCharacterBase::OnAnimMontageStarted);
		PlayerAnimInstance->OnMontageEnded.AddDynamic(this, &APlayerCharacterBase::OnAnimMontageEnded);
	}

	auto WeaponComps = GetComponentsByTag(UCapsuleComponent::StaticClass(), FName{ TEXT("WeaponComponent") });
	for (const auto& WeaponComp : WeaponComps)
	{
		WeaponCollisionComponent = Cast<UCapsuleComponent>(WeaponComp);
		WeaponCollisionComponent->SetCollisionProfileName("NoCollision");

		WeaponCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacterBase::OnWeaponOverlapBegin);
		WeaponCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacterBase::OnWeaponOverlapEnd);
	}

	CurrentStat->PlayerHpZero.AddUObject(this, &APlayerCharacterBase::PlayerHpZero);
}

// Called when the game starts or when spawned
void APlayerCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	Inventory->InitializeInventory();
	QuestSystem->InitializeQuestSystem();

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

	if (QuestState == EPlayerQuestState::ACCEPTED)
	{
		FQuestData Quest = QuestSystem->GetQuestData();
		int32 CurrentItemCount = Inventory->GetItemCount(FName(*Quest.QuestItemName));
		if (CurrentItemCount == Quest.QuestRequireCount)
		{
			QuestState = EPlayerQuestState::COMPLETE;
		}
	}
}

float APlayerCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CurrentStat->OnAttacked(DamageAmount);
	UE_LOG(LogTemp, Log, TEXT("Player HP : %d"), CurrentStat->GetHp());
	
	if (!bIsDead)
	{
		bIsAttacked = true;

		ExecuteAnimMontage(EPlayerAnimState::ATTACKED);
	}

	return DamageAmount;
}

void APlayerCharacterBase::CharacterDestroy()
{
	Destroy();

	AUnrealRPGGameModeBase* GameMode = Cast<AUnrealRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	GameMode->OpenGameEndWidget();
}

void APlayerCharacterBase::SetPossibleInteraction(bool PossibleInteraction, AActor* OverlapActor/*= nullptr*/)
{
	if (PossibleInteraction)
	{
		InteractionActor = OverlapActor;
	}
	else
	{
		InteractionActor = nullptr;
	}

	IsPossibleInteraction = PossibleInteraction;
}

void APlayerCharacterBase::InteractActor()
{
	if(InteractionActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
	{
		if (IsValid(InteractionActor))
		{
			IInteractionInterface* Actor = Cast<IInteractionInterface>(InteractionActor);
			Actor->ExecuteInteraction(this);
		}
	}
}

void APlayerCharacterBase::SetQuestData(FQuestData QuestData)
{
	QuestSystem->SetNewQuest(QuestData);

	if (QuestData.QuestItemName != FString{})
	{
		//인벤토리에도 퀘스트 아이템 이름 연동시켜둔다
		Inventory->SetQuestItemName(QuestData.QuestItemName);

		//혹시 인벤토리에 퀘스트 아이템이 있을 수 있기 때문에 관련해서 업데이트한다
		Inventory->CheckExistQuestItem();
	}
}

FQuestData APlayerCharacterBase::GetQuestData()
{
	return QuestSystem->GetQuestData();
}

void APlayerCharacterBase::ClearQuest()
{
	FQuestData Quest = QuestSystem->GetQuestData();
	Inventory->DeleteItem(Quest.QuestItemName, Quest.QuestRequireCount);//아이템을 인벤토리에서 갯수만큼 제거
	int32 GainExp = QuestSystem->ClearQuest();//퀘스트 시스템에서 퀘스트 정리
	CurrentStat->SetCurrentExp(GainExp);//보상 처리
}

void APlayerCharacterBase::SetPlayerStat(FPlayerStatData PlayerStat)
{
	CurrentStat->InputPlayerStat(PlayerStat);
}

FPlayerStatData APlayerCharacterBase::GetPlayerStat()
{
	return CurrentStat->GetPlayerStat();
}

void APlayerCharacterBase::SetInventoryItemList(TMap<FName, int32> InventoryItems)
{
	Inventory->LoadInventoryItems(InventoryItems);
}

TMap<FName, int32> APlayerCharacterBase::GetInventoryItemList()
{
	return Inventory->GetInventoryItems();
}

void APlayerCharacterBase::ChangeCollisionProfile(bool bAbleOverlap)
{
	if (bAbleOverlap)
	{
		//AnimMontage에 의해 공격 가능 상태가 되면 WeaponCollision을 활성화
		WeaponCollisionComponent->SetCollisionProfileName("Weapon");
	}
	else
	{
		//평소에는 불필요한 충돌을 줄이기 위해 WeaponCollision을 비활성화
		WeaponCollisionComponent->SetCollisionProfileName("NoCollision");
		bIsAttacking = false;
	}
}

void APlayerCharacterBase::OnWeaponOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this)
	{
		return;
	}

	if (!bIsAttacking)
	{
		if (OtherActor->ActorHasTag(FName(TEXT("Monster"))))
		{
			FDamageEvent DamageEvent;
			OtherActor->TakeDamage(CurrentStat->GetAtk(), DamageEvent, GetController(), this);
			bIsAttacking = true;
			
			auto Monster = Cast<AMonsterCharacterBase>(OtherActor);
			if (Monster->GetDead())
			{
				CurrentStat->SetCurrentExp(Monster->GetCurrentStat(ECharacterStatType::EXP));
			}

			++TestAttackCount;
			//UE_LOG(LogTemp, Log, TEXT("[HitActor : %s] [HiComponent : %s] Attack : %d!"), *OtherActor->GetName(), *OtherComp->GetName(), TestAttackCount);
		}
	}
}

void APlayerCharacterBase::OnWeaponOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (this == OtherActor)
	{
		return;
	}

	if (bIsAttacking)
	{
		//UE_LOG(LogTemp, Log, TEXT("[HitActor : %s] [HiComponent : %s] AttackEnd : %d!"), *OtherActor->GetName(), *OtherComp->GetName(), TestAttackCount);
	}
}

void APlayerCharacterBase::ExecuteAnimMontage(const EPlayerAnimState AnimState)
{
	if (!bIsDead)
	{
		switch (AnimState)
		{
		case EPlayerAnimState::PEACE:
		{
			break;
		}
		case EPlayerAnimState::CHASE:
		{
			break;
		}
		case EPlayerAnimState::ATTACKING:
		{
			PlayerAnimInstance->PlayPrimaryAttackMontage();
			break;
		}
		case EPlayerAnimState::ATTACKED:
		{
			PlayerAnimInstance->PlayAttackedMontage();
			break;
		}
		case EPlayerAnimState::DEAD:
		{
			PlayerAnimInstance->PlayDyingMontage();
			break;
		}
		default:
			break;
		}

	}
}

void APlayerCharacterBase::OnAnimMontageStarted(UAnimMontage* Montage)
{
	FString MontageName = Montage->GetName();
	//UE_LOG(LogTemp, Log, TEXT("[Player Start MontageName : %s]"), *MontageName);
}

void APlayerCharacterBase::OnAnimMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	FString MontageName = Montage->GetName();

	if (bInterrupted)
	{
		//UE_LOG(LogTemp, Log, TEXT("[Player End MontageName : %s(Interrupted Case)]"), *MontageName);
	}
	else
	{
		/*if (MontageName.Contains(FString(TEXT("Dying"))))
		{
			Destroy();
		}*/
	}
}

void APlayerCharacterBase::PickUpItem(FName ItemName)
{
	Inventory->AddItem(ItemName);
}

void APlayerCharacterBase::UseItem(FName ItemName)
{
	FItemData ResultItemData;
	Inventory->UseItem(ItemName, ResultItemData);

	bool IsUse = false;
	if (IsUse)//아이템 사용됨
	{
		if (ItemName == FName("HPPotion"))
		{
			CurrentStat->SetCurrentHp(ResultItemData.ItemValue.Hp);
		}
		else if (ItemName == FName("MPPotion"))
		{
			CurrentStat->SetCurrentHp(ResultItemData.ItemValue.Mp);
		}
	}
	else//아이템 없어서 사용 불가
	{

	}


}

void APlayerCharacterBase::PlayerHpZero()
{
	ExecuteAnimMontage(EPlayerAnimState::DEAD);
	bIsDead = true;

	//나머지 weapon들도 다 없애버려야할듯
	GetMesh()->SetCollisionProfileName("NoCollision");
}
