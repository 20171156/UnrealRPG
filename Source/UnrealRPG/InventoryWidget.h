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

private:
	void UpdatePotionNumText(ECharacterStatType PotionType);

private:
	TWeakObjectPtr<class UInventory> PlayerInventory;

	UPROPERTY(meta = (BindWidget))
	class UImage* HPPotionImage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HPPotionNum;

	UPROPERTY(meta = (BindWidget))
	class UImage* MPPotionImage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MPPotionNum;
};
