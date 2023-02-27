// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "InventoryItemWidget.h"
#include "Components/TileView.h"
#include "Inventory.h"
#include "InventoryItem.h"

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

	Inventory->OnAddNewItem.AddUObject(this, &UInventoryWidget::AddItemInventory);
	Inventory->OnRemoveItem.AddUObject(this, &UInventoryWidget::RemoveItemInventory);

	Inventory->OnCountCheckItem.AddUObject(this, &UInventoryWidget::UpdateItemCountInventory);
}

void UInventoryWidget::AddItemInventory(UInventoryItem* Item)
{
	InventoryTileView->AddItem(Item);
}

void UInventoryWidget::RemoveItemInventory(UInventoryItem* Item)
{
	InventoryTileView->RemoveItem(Item);
}

//(�κ��丮 ���µǾ� ������)
//������ ǥ�õ� ������ ����Ʈ�� ������Ʈ �ؾ��ϴ� ������ �̸��� ������ ��ġ�ϸ� �� ���� �����͸� ������Ʈ�Ѵ�
void UInventoryWidget::UpdateItemCountInventory(UInventoryItem* Item)
{
	auto ItemLists = InventoryTileView->GetListItems();
	for (const auto& OneItem : ItemLists)
	{
		//if (Cast<UInventoryItem>(OneItem)->GetItemName() == Item->GetItemName())
		if(OneItem == Item)
		{
			int32 ItemIndex = InventoryTileView->GetIndexForItem(Item);
			TArray<UUserWidget*> Widgets = InventoryTileView->GetDisplayedEntryWidgets();
			if (0 != Widgets.Num())
			{
				Cast<UInventoryItemWidget>(Widgets[ItemIndex])->UpdateItemCount(Item);
			}

			return;
		}
	}
}
