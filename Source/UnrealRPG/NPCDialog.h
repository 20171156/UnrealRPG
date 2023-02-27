// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomStruct.h"
#include "UObject/NoExportTypes.h"
#include "NPCDialog.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API UNPCDialog : public UObject
{
	GENERATED_BODY()
	
public:
	UNPCDialog();

	UFUNCTION()
	void CreateNPCDialog(const EPlayerQuestState State, FName NPCName);

	UFUNCTION()
	void ResetDialogAndQuestData();

	UFUNCTION()
	TArray<FString> GetDialogData() { return CombineDialogArray; }

	UFUNCTION()
	FQuestData GetCombineQuestData() { return CombineQuest; }

private:
	UFUNCTION()
	void AcceptQuestDialog();

	UFUNCTION()
	void CommonDialog();

	UFUNCTION()
	void CompleteQuestDialog();

	UFUNCTION()
	void CombineQuestDialog();

private:	
	UPROPERTY()
	class UMyGameInstance* DataInstance;

	UPROPERTY()
	TArray<FString> CombineDialogArray;

	UPROPERTY()
	FQuestData CombineQuest;

	UPROPERTY()
	FName QuestNPCName;
};
