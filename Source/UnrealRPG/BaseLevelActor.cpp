// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLevelActor.h"
#include "PlayerCharacterBase.h"
#include "Engine/TargetPoint.h"
#include "MonsterSpawnPoint.h"
#include "MonsterCharacterBase.h"
#include "Item.h"
#include "CustomStruct.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Public/EngineUtils.h"

ABaseLevelActor::ABaseLevelActor()
{
	//PrimaryActorTick.bCanEverTick = true;
	
	SpawnMonsterNum = 2;
}

void ABaseLevelActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ABaseLevelActor::BeginPlay()
{
	Super::BeginPlay();

	srand(time(0));

	UWorld* world = GetWorld();
	for (const auto& TargetActor : TActorRange<AMonsterSpawnPoint>(world))
	{
		if (IsValid(TargetActor))
		{
			SpawnPointArray.Emplace(TargetActor);
		}
	}

	if (SpawnPointArray.Num() != 0)
	{
		SpawnMonster();
	}
}

void ABaseLevelActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ABaseLevelActor::MonsterIsDead(AActor* DestroyedActor)
{
	//포션 드랍
	SpawnItem(DestroyedActor);

	//새로운 몬스터 소환
	SpawnMonsterArray.RemoveSingle(Cast<AMonsterCharacterBase>(DestroyedActor));

	if (0 != SpawnMonsterArray.Num())
	{
		return;
	}
	
	SpawnMonster();
}

void ABaseLevelActor::SpawnMonster()
{
	auto DataInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!IsValid(DataInstance))
	{
		return;
	}

	auto MonsterArray = DataInstance->GetAllMonsterData();
	for (int32 i = 0; i < SpawnMonsterNum; ++i)
	{
		int32 SectionNum = FMath::RandRange(0, MonsterArray.Num() - 1);
		auto SelectMonster = StaticLoadClass(AMonsterCharacterBase::StaticClass(), NULL, *(MonsterArray[SectionNum]->Path));

		AMonsterCharacterBase* SpawnedMonster = nullptr;
		do
		{
			int32 SpawnLocationNum = FMath::RandRange(0, SpawnPointArray.Num() - 1);

			FActorSpawnParameters SpawnParams;
			FRotator SpawnRotator;
			FVector SpawnLocation;
			SpawnParams.Owner = this;

			if (SpawnPointArray.IsValidIndex(SpawnLocationNum))
			{
				SpawnLocation = SpawnPointArray[SpawnLocationNum]->GetActorLocation();
				SpawnRotator = SpawnPointArray[SpawnLocationNum]->GetActorRotation();
			}

			SpawnedMonster = GetWorld()->SpawnActor<AMonsterCharacterBase>(SelectMonster, SpawnLocation, SpawnRotator, SpawnParams);
			
			if (IsValid(SpawnedMonster))
			{
				SpawnPointArray[SpawnLocationNum]->PlayParticleComponent();
				SpawnMonsterArray.Emplace(SpawnedMonster);
				SpawnedMonster->OnDestroyed.AddDynamic(this, &ABaseLevelActor::MonsterIsDead);

				//UE_LOG(LogTemp, Log, TEXT("Monster Spawn Complete! %d"), SpawnLocationNum);
			}
		} while (!IsValid(SpawnedMonster));
	}
}

void ABaseLevelActor::SpawnItem(AActor* DestroyedActor)
{
	int32 SectionNum = FMath::RandRange(0, 4);

	auto DataInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!IsValid(DataInstance))
	{
		return;
	}

	auto ItemData = DataInstance->GetAllItemData();
	auto ItemClass = (ItemData[SectionNum]->ItemClass).LoadSynchronous();

	FActorSpawnParameters SpawnParams;
	FRotator SpawnRotator = DestroyedActor->GetActorRotation();
	FVector SpawnLocation = DestroyedActor->GetActorLocation();
	SpawnParams.Owner = this;

	auto ItemActor = GetWorld()->SpawnActor<AItem>(ItemClass, SpawnLocation, SpawnRotator, SpawnParams);
	if (IsValid(ItemActor))
	{
		ItemActor->InitializeItemName(DataInstance->GetItemName(SectionNum));
	}

	if (!IsValid(ItemActor))
	{
		return;
	}
}
