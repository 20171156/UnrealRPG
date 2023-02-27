// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "InventoryItem.h"

UInventoryItemWidget::UInventoryItemWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UInventoryItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventoryItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	auto InventoryItem = Cast<UInventoryItem>(ListItemObject);

	FString InttoString = FString::FromInt(InventoryItem->GetItemCount());
	ItemCount->SetText(FText::FromString(InttoString));

	ItemImage->SetBrushFromTexture(InventoryItem->GetItemData().InventoryIconTexture);
	
}

void UInventoryItemWidget::UpdateItemImage(UInventoryItem* ListItemObject)
{
	if (IsValid(ListItemObject))
	{
		if (nullptr != ItemImage)
		{
			ItemImage->SetBrushFromTexture(ListItemObject->GetItemData().InventoryIconTexture);
		}
	}
}

void UInventoryItemWidget::UpdateItemCount(UInventoryItem* ListItemObject)
{
	if (IsValid(ListItemObject))
	{
		if (nullptr != ItemCount)
		{
			FString InttoString = FString::FromInt(ListItemObject->GetItemCount());
			ItemCount->SetText(FText::FromString(InttoString));
		}
	}
}