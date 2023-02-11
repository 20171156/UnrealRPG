// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLevelActor.h"
#include "Engine/TargetPoint.h"
#include "MonsterSpawnPoint.h"
#include "MonsterCharacterBase.h"
#include "Item.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "CustomStruct.h"
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

	SpawnMonster();
}

void ABaseLevelActor::MonsterIsDead(AActor* DestroyedActor)
{
	//포션 드랍
	SpawnPotion(DestroyedActor);

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

	auto MonsterArray = DataInstance->GetMonsterAllData();
	for (int32 i = 0; i < SpawnMonsterNum; ++i)
	{
		int32 SectionNum = FMath::RandRange(0, MonsterArray.Num() - 1);
		auto SelectMonster = StaticLoadClass(AMonsterCharacterBase::StaticClass(), NULL, *(MonsterArray[SectionNum]->Path));

		AMonsterCharacterBase* SpawnedMonster = nullptr;
		do
		{
			int32 SpawnLocationNum = FMath::RandRange(0, SpawnPointArray.Num() - 1);

			FActorSpawnParameters SpawnParams;
			//FRotator Rotator = FRotator::ZeroRotator;
			FRotator SpawnRotator;
			FVector SpawnLocation;
			SpawnParams.Owner = this;

			if (SpawnPointArray.IsValidIndex(SpawnLocationNum))
			{
				SpawnLocation = SpawnPointArray[SpawnLocationNum]->GetActorLocation();
				SpawnRotator = SpawnPointArray[SpawnLocationNum]->GetActorRotation();
			}

			//SpawnedMonster = GetWorld()->SpawnActor<AMonsterCharacterBase>(SelectMonster, SpawnLocation, Rotator, SpawnParams);
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

void ABaseLevelActor::SpawnPotion(AActor* DestroyedActor)
{
	int32 SectionNum = FMath::RandRange(0, 1);

	auto DataInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!IsValid(DataInstance))
	{
		return;
	}

	auto PotionData = DataInstance->GetPotionAllData();
	auto SelectPotion = StaticLoadClass(AItem::StaticClass(), NULL, *(PotionData[SectionNum]->Path));

	FActorSpawnParameters SpawnParams;
	FRotator SpawnRotator = DestroyedActor->GetActorRotation();
	FVector SpawnLocation = DestroyedActor->GetActorLocation();
	SpawnParams.Owner = this;

	auto Potion = GetWorld()->SpawnActor<AItem>(SelectPotion, SpawnLocation, SpawnRotator, SpawnParams);

	if (!IsValid(Potion))
	{
		return;
	}
}
