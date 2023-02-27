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

/**
 * 인벤토리 위젯과 연동될 인벤토리 아이템을 가짐
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
	void AddItem(FName ItemName);

	UFUNCTION()
	bool UseItem(FName ItemName, FItemData& ResultItemData);

	UFUNCTION()
	int32 GetItemCount(FName ItemName);

private:
	UFUNCTION()
	void UpdatepPotionSlotCount(FName ItemName);

public:
	FAddNewItem OnAddNewItem;
	FRemoveItem OnRemoveItem;
	FCountCheckItem OnCountCheckItem;
	FChangeHPPotion ChangeHPPotion;
	FChangeMPPotion ChangeMPPotion;

private:
	TMap<FName, class UInventoryItem*> InventoryItemMap;
};