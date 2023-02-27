// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomStruct.h"
#include "UObject/NoExportTypes.h"
#include "PlayerQuestSystem.generated.h"

DECLARE_MULTICAST_DELEGATE(FChangeQuestData);
//DECLARE_MULTICAST_DELEGATE(FChangeQuestItemCount);

/**
 * 퀘스트 시스템 클래스 : 비어있거나 하나의 퀘스트를 가질 수 있음 / 인벤토리 시스템과 연결
 * NPC와 대화할 때 퀘스트와 인벤토리 아이템 비교해서 완료처리
 * 
 */
UCLASS()
class UNREALRPG_API UPlayerQuestSystem : public UObject
{
	GENERATED_BODY()
	
public:
	UPlayerQuestSystem();

	UFUNCTION()
	void InitializeQuestSystem();

	UFUNCTION()
	void SetNewQuest(const FQuestData& Data);

	UFUNCTION()
	void ClearQuest();

	UFUNCTION()
	const FQuestData& GetQuestData() { return Quest; }

public:
	FChangeQuestData ChangeQuestData;

private:
	UPROPERTY()
	FQuestData Quest;

	TWeakObjectPtr<class UInventory> Inventory;
};
