// Fill out your copyright notice in the Description page of Project Settings.


#include "DatatableInstance.h"

UDatatableInstance::UDatatableInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> PlayableData(TEXT("DataTable'/Game/Datatable/StatDatatable_PlayableCharacter.StatDatatable_PlayableCharacter'"));

	if (PlayableData.Succeeded())
	{
		PlayableStat = PlayableData.Object;
	}

	UE_LOG(LogTemp, Warning, TEXT("GameInstance Loading Complete"));
}

const FPlayableCharacterStatData& UDatatableInstance::GetPlayableStatData(int32 Level)
{
	return *PlayableStat->FindRow<FPlayableCharacterStatData>(*FString::FromInt(Level), TEXT(""));
}
