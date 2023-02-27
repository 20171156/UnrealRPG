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
	FItemData* GetItemData(const FName& ItemName);
	FDialogData* GetDialogData(const FName& DialogName);
	FQuestData* GetQuestData(const FName& QuestName);
	
	FName GetItemName(int32 Index);
	
	TArray<FMonsterStatData*> GetAllMonsterData();
	TArray<FItemData*> GetAllItemData();
	TArray<FDialogData*> GetAllDialogData();
	TArray<FQuestData*> GetAllQuestData();


private:
	UPROPERTY()
	class UDataTable* PlayerStat;

	UPROPERTY()
	class UDataTable* MonsterStat;

	UPROPERTY()
	class UDataTable* ItemList;

	UPROPERTY()
	class UDataTable* DialogList;

	UPROPERTY()
	class UDataTable* QuestList;

};
