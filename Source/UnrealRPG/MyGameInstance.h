// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "CustomStruct.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMyGameInstance();

	FPlayerStatData* GetPlayerData(const int32& Level);
	FMonsterStatData* GetMonsterData(const FName& MonsterName);
	FPlayerStatData* GetPotionData(const FName& PotionName);
	
	TArray<FMonsterStatData*> GetMonsterAllData();
	TArray<FPlayerStatData*> GetPotionAllData();

private:
	UPROPERTY()
	class UDataTable* PlayerStat;

	UPROPERTY()
	class UDataTable* MonsterStat;

	UPROPERTY()
	class UDataTable* PotionStat;
};
