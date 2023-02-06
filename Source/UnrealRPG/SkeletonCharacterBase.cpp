// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletonCharacterBase.h"
#include "MonsterAnimInstance.h"
#include "MonsterStatComponent.h"
#include "MonsterAIController.h"
#include "WeaponBase.h"

ASkeletonCharacterBase::ASkeletonCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

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

	CurrentStat->InitializeStatData(Tags[1]);//무조건 추후 수정해야함

	UE_LOG(LogTemp, Log, TEXT("Monster Spawn Complete!"));
	UE_LOG(LogTemp, Log, TEXT("MonsterName : %s"), *CurrentStat->GetMonsterName());
	UE_LOG(LogTemp, Log, TEXT("MonsterLevel : %d"), CurrentStat->GetLevel());
	UE_LOG(LogTemp, Log, TEXT("MonsterAtk : %d"), CurrentStat->GetAtk());
	UE_LOG(LogTemp, Log, TEXT("MonsterExp : %d"), CurrentStat->GetExp());
	UE_LOG(LogTemp, Log, TEXT("MonsterHp : %d"), CurrentStat->GetHp());
	UE_LOG(LogTemp, Log, TEXT("MonsterSp : %d"), CurrentStat->GetSp());
	UE_LOG(LogTemp, Log, TEXT("MonsterMp : %d"), CurrentStat->GetMp());
}

void ASkeletonCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//FString ASkeletonCharacterBase::GetEStateAsString(EMonsterState EnumValue)
//{
//	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EMonsterState"), true);
//	if (!enumPtr)
//	{
//		return FString("Invalid");
//	}
//	return enumPtr->GetNameStringByIndex((int32)EnumValue);
//}