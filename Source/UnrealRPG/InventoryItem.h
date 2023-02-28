// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CustomStruct.h"
#include "InventoryItem.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API UInventoryItem : public UObject
{
	GENERATED_BODY()

public:
	UInventoryItem();
	
	UFUNCTION()
	void InitializeItemData(FName InputItemName);

	UFUNCTION()
	void IncreaseItem();

	UFUNCTION()
	bool DecreaseItem();

	void SetQuestItem(bool QuestItem) { IsQuestItem = QuestItem; }
	bool GetQuestItem(bool QuestItem) { return IsQuestItem; }

public:
	FName GetItemName() { return ItemName; }
	const FItemData& GetItemData() { return ItemData; }
	int32 GetItemCount() { return ItemCount; }

private:
	UPROPERTY()
	FName ItemName;

	UPROPERTY()
	FItemData ItemData;
	
	UPROPERTY()
	int32 ItemCount;

	UPROPERTY()
	bool IsQuestItem = false;
};
