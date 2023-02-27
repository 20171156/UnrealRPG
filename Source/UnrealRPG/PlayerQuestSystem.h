// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomStruct.h"
#include "UObject/NoExportTypes.h"
#include "PlayerQuestSystem.generated.h"

DECLARE_MULTICAST_DELEGATE(FChangeQuestData);
//DECLARE_MULTICAST_DELEGATE(FChangeQuestItemCount);

/**
 * ����Ʈ �ý��� Ŭ���� : ����ְų� �ϳ��� ����Ʈ�� ���� �� ���� / �κ��丮 �ý��۰� ����
 * NPC�� ��ȭ�� �� ����Ʈ�� �κ��丮 ������ ���ؼ� �Ϸ�ó��
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
