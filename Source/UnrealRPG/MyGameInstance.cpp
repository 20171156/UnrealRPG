// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "PlayerCharacterBase.h"

UMyGameInstance::UMyGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> PlayerData(TEXT("DataTable'/Game/Datatable/StatDatatable_Player.StatDatatable_Player'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> MonsterData(TEXT("DataTable'/Game/Datatable/StatDatatable_Monster.StatDatatable_Monster'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> ItemData(TEXT("DataTable'/Game/Datatable/ItemData.ItemData'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> CommonDialogData(TEXT("DataTable'/Game/Datatable/NPCCommonDialog.NPCCommonDialog'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> QuestDialogData(TEXT("DataTable'/Game/Datatable/NPCQuestDialog.NPCQuestDialog'"));

	if (PlayerData.Succeeded())
	{
		PlayerStat = PlayerData.Object;
		UE_LOG(LogTemp, Warning, TEXT("PlayerData Loading Complete."));
	}

	if (MonsterData.Succeeded())
	{
		MonsterStat = MonsterData.Object;
		UE_LOG(LogTemp, Warning, TEXT("MonsterData Loading Complete."));
	}

	if (ItemData.Succeeded())
	{
		ItemList = ItemData.Object;
		UE_LOG(LogTemp, Warning, TEXT("ItemData Loading Complete."));
	}

	if (CommonDialogData.Succeeded())
	{
		DialogList = CommonDialogData.Object;
		UE_LOG(LogTemp, Warning, TEXT("DialogList Loading Complete."));
	}

	if (QuestDialogData.Succeeded())
	{
		QuestList = QuestDialogData.Object;
		UE_LOG(LogTemp, Warning, TEXT("QuestList Loading Complete."));
	}

	InitlializePlayerData();

	UE_LOG(LogTemp, Warning, TEXT("GameInstance Loading Complete."));
}

FPlayerStatData* UMyGameInstance::GetPlayerData(const int32& Level)
{
	return PlayerStat->FindRow<FPlayerStatData>(*FString::FromInt(Level), TEXT("Do not find PlayerData"));
}

FMonsterStatData* UMyGameInstance::GetMonsterData(const FName& MonsterName)
{
	return MonsterStat->FindRow<FMonsterStatData>(MonsterName, TEXT("Do not find MonsterData"));
}

FItemData* UMyGameInstance::GetItemData(const FName& ItemName)
{
	return ItemList->FindRow<FItemData>(ItemName, TEXT("Do not find ItemData"));
}

FDialogData* UMyGameInstance::GetDialogData(const FName& DialogName)
{
	return DialogList->FindRow<FDialogData>(DialogName, TEXT("Do not find DialogData"));
}

FQuestData* UMyGameInstance::GetQuestData(const FName& QuestName)
{
	return QuestList->FindRow<FQuestData>(QuestName, TEXT("Do not find QuestData"));
}

FName UMyGameInstance::GetItemName(int32 Index)
{
	TArray<FName> ItemName = ItemList->GetRowNames();
	if (ItemName.IsValidIndex(Index))
	{
		return ItemName[Index];
	}
	else
	{
		return FName{};
	}
}

TArray<FMonsterStatData*> UMyGameInstance::GetAllMonsterData()
{
	TArray<FMonsterStatData*> Arr;
	MonsterStat->GetAllRows(TEXT("Missing MonsterData"), Arr);
	
	return Arr;
}

TArray<FItemData*> UMyGameInstance::GetAllItemData()
{
	TArray<FItemData*> Arr;
	ItemList->GetAllRows(TEXT("Missing ItemData"), Arr);

	return Arr;
}

TArray<FDialogData*> UMyGameInstance::GetAllDialogData()
{
	TArray<FDialogData*> Arr;
	ItemList->GetAllRows(TEXT("Missing DialogData"), Arr);

	return Arr;
}

TArray<FQuestData*> UMyGameInstance::GetAllQuestData()
{
	TArray<FQuestData*> Arr;
	ItemList->GetAllRows(TEXT("Missing QuestData"), Arr);

	return Arr;
}

void UMyGameInstance::SavePlayerData(APlayerCharacterBase* Player)
{
	//레벨이 교체될 때 플레이어의 퀘스트, 인벤토리, 플레이어 스탯 등의 데이터를 보관하고 있어야 한다
	//항상 순서가 지켜져야 한다(퀘스트->인벤토리 순으로)
	SavePlayerStat = Player->GetPlayerStat();//스탯
	SavePlayerQuestState = Player->GetQuestState();//퀘스트 상태
	SavePlayerQuest = Player->GetQuestData();//퀘스트 데이터
	SavePlayerIventoryItems = Player->GetInventoryItemList();//인벤토리
}

void UMyGameInstance::LoadPlayerData(APlayerCharacterBase* Player)
{
	//항상 순서가 지켜져야 한다(퀘스트->인벤토리 순으로)
	Player->SetPlayerStat(SavePlayerStat);
	Player->SetQuestState(SavePlayerQuestState);
	Player->SetQuestData(SavePlayerQuest);
	Player->SetInventoryItemList(SavePlayerIventoryItems);
}

void UMyGameInstance::InitlializePlayerData()
{
	//항상 순서가 지켜져야 한다(퀘스트->인벤토리 순으로)
	SavePlayerStat = *GetPlayerData(1);
	SavePlayerStat.Exp = 0;
	SavePlayerQuestState = EPlayerQuestState::EMPTY;
	SavePlayerQuest;
	SavePlayerIventoryItems;
}
