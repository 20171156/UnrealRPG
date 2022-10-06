// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletonCharacterBase.h"
#include "MonsterAnimInstance.h"
#include "MonsterStatComponent.h"
#include "MonsterAIController.h"
#include "WeaponBase.h"

ASkeletonCharacterBase::ASkeletonCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(FName("Skeleton"));

	CurrentState = EMonsterState::IDLE;
	
	//AI Class Setting
	AIControllerClass = AMonsterAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ASkeletonCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ASkeletonCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentStat->InitializeStatData(Tags[2]);//일단 추후 테스트
}

void ASkeletonCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, GetEStateAsString(CurrentState));
}

FString ASkeletonCharacterBase::GetEStateAsString(EMonsterState EnumValue)
{
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EMonsterState"), true);
	if (!enumPtr)
	{
		return FString("Invalid");
	}
	return enumPtr->GetNameStringByIndex((int32)EnumValue);
}