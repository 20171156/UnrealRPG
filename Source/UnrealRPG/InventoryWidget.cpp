// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Inventory.h"

UInventoryWidget::UInventoryWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventoryWidget::BindWidget(UInventory* Inventory)
{
	PlayerInventory = Inventory;

	Inventory->OnAddPotion.AddUObject(this, &UInventoryWidget::UpdatePotionNumText);
	Inventory->OnUsePotion.AddUObject(this, &UInventoryWidget::UpdatePotionNumText);
}

void UInventoryWidget::UpdatePotionNumText(ECharacterStatType PotionType)
{
	switch (PotionType)
	{
	case ECharacterStatType::HP:
	{
		if (nullptr != HPPotionNum)
		{
			FString InttoString = FString::FromInt(PlayerInventory->GetHPPotionNum());
			HPPotionNum->SetText(FText::FromString(InttoString));
		}
		break;
	}
	case ECharacterStatType::SP:
	{
		break;
	}
	case ECharacterStatType::MP:
	{
		if (nullptr != MPPotionNum)
		{
			FString InttoString = FString::FromInt(PlayerInventory->GetMPPotionNum());
			MPPotionNum->SetText(FText::FromString(InttoString));
		}
		break;
	}
	case ECharacterStatType::ATK:
	{
		break;
	}
	case ECharacterStatType::EXP:
	{
		break;
	}
	default:
	{
		break;
	}
	}



}
