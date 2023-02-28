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

void UInventory::SetQuestItemName(FString ItemName)
{
	QuestItemName = ItemName;
}

void UInventory::AddItem(FName ItemName/*, FString QuestItemName = FString{}*/)
{
	auto ItemValue = InventoryItemMap.Find(ItemName);

	if (nullptr == ItemValue)//처음 추가한 경우 아이템 추가
	{
		UInventoryItem* NewItem = NewObject<UInventoryItem>(this, UInventoryItem::StaticClass());
		NewItem->InitializeItemData(ItemName);
		InventoryItemMap.Emplace(ItemName, NewItem);
		OnAddNewItem.Broadcast(NewItem);
		
		//추가된 아이템이 퀘스트 아이템이라면 위젯에 갯수를 업데이트한다
		if (ItemName.ToString() == QuestItemName)
		{
			NewItem->SetQuestItem(true);
			OnAddQuestItem.Broadcast();
		}

		//추가된 아이템이 물약이라면 PotionSlot을 업데이트한다
		if (NewItem->GetItemData().ItemType == EItemType::CONSUMABLE)
		{
			UpdatepPotionSlotCount(ItemName);
		}
	}
	else//이미 존재하는 경우 갯수만 늘림
	{
		(*ItemValue)->IncreaseItem();
		OnCountCheckItem.Broadcast(*ItemValue);

		if (ItemName.ToString() == QuestItemName)
		{
			(*ItemValue)->SetQuestItem(true);
			OnAddQuestItem.Broadcast();
		}

		if ((*ItemValue)->GetItemData().ItemType == EItemType::CONSUMABLE)
		{
			UpdatepPotionSlotCount(ItemName);
		}
	}
}

bool UInventory::UseItem(FName ItemName, FItemData& ResultItemData/*, FString QuestItemName = FString{}*/)
{
	auto ItemValue = InventoryItemMap.Find(ItemName);

	if (nullptr == ItemValue)//찾는 아이템 없을 경우(사용안됨)
	{
		return false;
	}
	else//이미 존재하는 경우 갯수만 줄임(어쨌든 사용됨)
	{
		bool IsZeroCount = (*ItemValue)->DecreaseItem();
		OnCountCheckItem.Broadcast(*ItemValue);

		if ((*ItemValue)->GetItemData().ItemType == EItemType::CONSUMABLE)
		{
			UpdatepPotionSlotCount(ItemName);
		}

		if (IsZeroCount)
		{
			//TileView에서 아이템 제거
			OnRemoveItem.Broadcast(*ItemValue);
		}

		ResultItemData = (*ItemValue)->GetItemData();

		return true;
	}
}

void UInventory::DeleteItem(FString ItemName, int32 ItemCount)
{
	if (QuestItemName == ItemName)
	{
		bool IsZeroCount = false;
		auto ItemValue = InventoryItemMap.Find(FName(*QuestItemName));
		for (int32 i = 0; i < ItemCount; ++i)
		{
			IsZeroCount = (*ItemValue)->DecreaseItem();
		}

		OnCountCheckItem.Broadcast(*ItemValue);

		if ((*ItemValue)->GetItemData().ItemType == EItemType::CONSUMABLE)
		{
			UpdatepPotionSlotCount(FName(*QuestItemName));
		}

		if (IsZeroCount)
		{
			OnRemoveItem.Broadcast(*ItemValue);
		}
	}

	QuestItemName = FString{};//퀘스트 끝났으니까 데이터 초기화
}

int32 UInventory::GetItemCount(FName ItemName)
{
	auto ItemValue = InventoryItemMap.Find(ItemName);

	if (nullptr == ItemValue)
	{
		return 0;
	}
	else
	{
		return Cast<UInventoryItem>(*ItemValue)->GetItemCount();
	}
}

void UInventory::LoadInventoryItems(TMap<FName, int32> InventoryItems)
{
	for (const auto& Item : InventoryItems)
	{
		for (int32 i = 0; i < Item.Value; ++i)
		{
			AddItem(Item.Key);
		}
	}
}

void UInventory::CheckExistQuestItem(/*FString ItemName*/)
{
	for (const auto& Item : InventoryItemMap)
	{
		if (Item.Key.ToString() == QuestItemName)
		{
			Item.Value->SetQuestItem(true);
		}
	}
}

TMap<FName, int32> UInventory::GetInventoryItems()
{
	TMap<FName, int32> SaveInventoryItems;

	for (const auto& Item : InventoryItemMap)
	{
		SaveInventoryItems.Emplace(Item.Key, Item.Value->GetItemCount());
	}

	return SaveInventoryItems;
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