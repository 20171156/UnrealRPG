// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CustomEnum.h"
#include "Inventory.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FAddPotion, ECharacterStatType);
DECLARE_MULTICAST_DELEGATE_OneParam(FUsePotion, ECharacterStatType);

/**
 * 
 */
UCLASS()
class UNREALRPG_API UInventory : public UObject
{
	GENERATED_BODY()
	
public:
	UInventory();

public:
	void InitInventory();
	void AddPotion(ECharacterStatType ItemType);
	bool UsePotion(ECharacterStatType ItemType);

	const uint32& GetHPPotionNum() { return HPPotionNum; }
	const uint32& GetMPPotionNum() { return MPPotionNum; }

public:
	FAddPotion OnAddPotion;
	FUsePotion OnUsePotion;

private:
	uint32 HPPotionNum = 0;
	uint32 MPPotionNum = 0;
	uint32 MaxPotionNum = 5;
};