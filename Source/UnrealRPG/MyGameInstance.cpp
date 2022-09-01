// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> PlayerData(TEXT("DataTable'/Game/Datatable/StatDatatable_PlayableCharacter.StatDatatable_PlayableCharacter'"));
	
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

FCharacterStatData* UMyGameInstance::GetPlayerData(const int32& Level)
{
	return PlayerStat->FindRow<FCharacterStatData>(*FString::FromInt(Level), TEXT("Missing PlayerData"));
}

FCharacterStatData* UMyGameInstance::GetMonsterData(const FName& MonsterName)
{
	return MonsterStat->FindRow<FCharacterStatData>(MonsterName, TEXT("Missing MonsterData"));
}