// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "InventoryItem.h"
#include "CustomEnum.h"

UInventory::UInventory()
{
}

void UInventory::InitializeInventory()
{
	ChangeHPPotion.Broadcast();
	ChangeMPPotion.Broadcast();
}

void UInventory::AddItem(FName ItemName, bool IsQuestItem/* = false*/)
{
	auto ItemValue = InventoryItemMap.Find(ItemName);
	
	if (nullptr == ItemValue)//ó�� �߰��� ��� ������ �߰�
	{
		UInventoryItem* Item = NewObject<UInventoryItem>(this, UInventoryItem::StaticClass());
		Item->InitializeItemData(ItemName);
		InventoryItemMap.Emplace(ItemName, Item);
	
		OnAddNewItem.Broadcast(Item);

		if (Item->GetItemData().ItemType == EItemType::CONSUMABLE)
		{
			UpdatepPotionSlotCount(ItemName);
		}
	}
	else//�̹� �����ϴ� ��� ������ �ø�
	{
		(*ItemValue)->IncreaseItem();

		OnCountCheckItem.Broadcast((*ItemValue));

		if ((*ItemValue)->GetItemData().ItemType == EItemType::CONSUMABLE)
		{
			UpdatepPotionSlotCount(ItemName);
		}
	}

	//�߰��� �������� ����Ʈ �������̶�� ������ ������ ������Ʈ�Ѵ�
	if (IsQuestItem)
	{
		OnAddQuestItem.Broadcast();
	}
}

bool UInventory::UseItem(FName ItemName, FItemData& ResultItemData, bool IsQuestItem/* = false*/)
{
	auto ItemValue = InventoryItemMap.Find(ItemName);

	if (nullptr != ItemValue)//�̹� �����ϴ� ��� ������ ����(��·�� ����)
	{
		bool IsZeroCount = (*ItemValue)->DecreaseItem();
		OnCountCheckItem.Broadcast((*ItemValue));

		if ((*ItemValue)->GetItemData().ItemType == EItemType::CONSUMABLE)
		{
			UpdatepPotionSlotCount(ItemName);
		}

		if (IsZeroCount)
		{
			//TileView���� ������ ����
			OnRemoveItem.Broadcast((*ItemValue));
		}

		ResultItemData = (*ItemValue)->GetItemData();
		return true;
	}
	else//ã�� ������ ���� ���(���ȵ�)
	{
		//...
		return false;
	}

	//���� �������� ����Ʈ �������̶�� ������ ������ ������Ʈ�Ѵ�
	if (IsQuestItem)
	{
		OnAddQuestItem.Broadcast();
	}
}

int32 UInventory::GetItemCount(FName ItemName)
{
	auto ItemValue = InventoryItemMap.Find(ItemName);

	if (nullptr != ItemValue)
	{
		return Cast<UInventoryItem>(*ItemValue)->GetItemCount();
	}
	else
	{
		return 0;
	}
}

void UInventory::UpdatepPotionSlotCount(FName ItemName)
{
	if (ItemName == FName("HPPotion"))
	{
		ChangeHPPotion.Broadcast();
	}
	else if (ItemName == FName("MPPotion"))
	{
		ChangeMPPotion.Broadcast();
	}
}