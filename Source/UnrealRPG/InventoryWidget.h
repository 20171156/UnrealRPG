// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CustomEnum.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UInventoryWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	void BindWidget(class UInventory* Inventory);

	UFUNCTION()
	void AddItemInventory(class UInventoryItem* Item);
	
	UFUNCTION()
	void RemoveItemInventory(class UInventoryItem* Item);

	UFUNCTION()
	void UpdateItemCountInventory(class UInventoryItem* Item);

private:
	TWeakObjectPtr<class UInventory> PlayerInventory;

	UPROPERTY(Meta = (BindWidget))
	class UTileView* InventoryTileView;
};
