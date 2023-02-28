// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CustomStruct.h"
#include "Inventory.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FAddNewItem, class UInventoryItem*);
DECLARE_MULTICAST_DELEGATE_OneParam(FRemoveItem, class UInventoryItem*);
DECLARE_MULTICAST_DELEGATE_OneParam(FCountCheckItem, class UInventoryItem*);
DECLARE_MULTICAST_DELEGATE(FChangeHPPotion);
DECLARE_MULTICAST_DELEGATE(FChangeMPPotion);
DECLARE_MULTICAST_DELEGATE(FAddQuestItem);

/**
 * �κ��丮 ������ ������ �κ��丮 �������� ����
 */
UCLASS()
class UNREALRPG_API UInventory : public UObject
{
	GENERATED_BODY()
	
public:
	UInventory();

	UFUNCTION()
	void InitializeInventory();

	UFUNCTION()
	void SetQuestItemName(FString ItemName);

	UFUNCTION()
	void AddItem(FName ItemName/*, FString QuestItemName = FString{}*/);

	UFUNCTION()
	bool UseItem(FName ItemName, FItemData& ResultItemData/*, FString QuestItemName = FString{}*/);

	UFUNCTION()
	void DeleteItem(FString ItemName, int32 ItemCount);

	UFUNCTION()
	int32 GetItemCount(FName ItemName);

	UFUNCTION()
	void LoadInventoryItems(TMap<FName, int32> InventoryItems);

	UFUNCTION()
	void CheckExistQuestItem(/*FString ItemName*/);

	TMap<FName, int32> GetInventoryItems();

private:
	UFUNCTION()
	void UpdatepPotionSlotCount(FName ItemName);

public:
	FAddNewItem OnAddNewItem;
	FRemoveItem OnRemoveItem;
	FCountCheckItem OnCountCheckItem;
	FChangeHPPotion ChangeHPPotion;
	FChangeMPPotion ChangeMPPotion;
	FAddQuestItem OnAddQuestItem;

private:
	TMap<FName, class UInventoryItem*> InventoryItemMap;

	UPROPERTY()
	FString QuestItemName;
};