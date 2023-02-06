// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> PlayerData(TEXT("DataTable'/Game/Datatable/StatDatatable_Player.StatDatatable_Player'"));
	
	static ConstructorHelpers::FObjectFinder<UDataTable> MonsterData(TEXT("DataTable'/Game/Datatable/StatDatatable_Monster.StatDatatable_Monster'"));

	if (PlayerData.Succeeded())
	{
		PlayerStat = PlayerData.Object;
		UE_LOG(LogTemp, Warning, TEXT("PlayerData Loading Complete"));
	}

	if (MonsterData.Succeeded())
	{
		MonsterStat = MonsterData.Object;
		UE_LOG(LogTemp, Warning, TEXT("MonsterData Loading Complete"));
	}

	UE_LOG(LogTemp, Warning, TEXT("GameInstance Loading Complete"));
}

FPlayerStatData* UMyGameInstance::GetPlayerData(const int32& Level)
{
	return PlayerStat->FindRow<FPlayerStatData>(*FString::FromInt(Level), TEXT("Missing PlayerData"));
}

FMonsterStatData* UMyGameInstance::GetMonsterData(const FName& MonsterName)
{
	return MonsterStat->FindRow<FMonsterStatData>(MonsterName, TEXT("Missing MonsterData"));
}

TArray<FMonsterStatData*> UMyGameInstance::GetMonsterAllData()
{
	TArray<FMonsterStatData*> Arr;
	MonsterStat->GetAllRows(TEXT("Missing MonsterData"), Arr);
	
	return Arr;
}
