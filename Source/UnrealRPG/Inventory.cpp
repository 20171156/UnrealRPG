// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

UInventory::UInventory()
{

}

void UInventory::InitInventory()
{
	//ó���� �Ѱ��� ��� ������
	++HPPotionNum;
	++MPPotionNum;
}

void UInventory::AddPotion(ECharacterStatType ItemType)
{
	switch (ItemType)
	{
	case ECharacterStatType::HP:
	{
		if (HPPotionNum <= MaxPotionNum)
		{
			++HPPotionNum;
		}
		break;
	}
	case ECharacterStatType::SP:
	{
		break;
	}
	case ECharacterStatType::MP:
	{
		if (MPPotionNum <= MaxPotionNum)
		{
			++MPPotionNum;
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

	OnAddPotion.Broadcast(ItemType);
}

bool UInventory::UsePotion(ECharacterStatType ItemType)
{
	switch (ItemType)
	{
	case ECharacterStatType::HP:
	{
		if (HPPotionNum == 0)
		{
			return false;
		}

		--HPPotionNum;
		OnUsePotion.Broadcast(ItemType);

		return true;

		break;
	}
	case ECharacterStatType::SP:
	{
		break;
	}
	case ECharacterStatType::MP:
	{
		if (MPPotionNum == 0)
		{
			return false;
		}

		--MPPotionNum;
		OnUsePotion.Broadcast(ItemType);

		return true;

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

	return false;
}