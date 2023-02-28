// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItem.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

UInventoryItem::UInventoryItem()
{
	ItemCount = 0;
}

void UInventoryItem::InitializeItemData(FName InputItemName)
{
	auto DataInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!IsValid(DataInstance))
	{
		return;
	}

	ItemName = InputItemName;

	auto Data = DataInstance->GetItemData(InputItemName);
	ItemData = *Data;

	IncreaseItem();
}

void UInventoryItem::IncreaseItem()
{
	++ItemCount;
}

bool UInventoryItem::DecreaseItem()
{
	if (ItemCount > 0)
	{
		--ItemCount;

		if (ItemCount == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//else
	//{
	//	ItemCount = 0;

	//	return true;
	//}

	return false;
}
