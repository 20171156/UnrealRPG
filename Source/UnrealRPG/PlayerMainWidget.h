// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerMainWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API UPlayerMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPlayerMainWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	void BindWidget(class UStatComponent* StatCompClass, class UInventory* InventoryClass, class UPlayerQuestSystem* QuestClass);
	void UpdateLevel();
	void UpdateHp();
	void UpdateMp();
	void UpdateSp();
	void UpdateExp();
	void UpdateHPPotionNum();
	void UpdateMPPotionNum();
	void UpdateQuest();

private:
	void ChangeQuestDialogColor();

private:
	TWeakObjectPtr<class UStatComponent> CurrentStatComp;

	TWeakObjectPtr<class UInventory> Inventory;

	TWeakObjectPtr<class UPlayerQuestSystem> QuestSystem;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* LevelText;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HPBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* MPBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* SPBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* EXPBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HPPotionNum;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MPPotionNum;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* QuestText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* QuestItemCount;

	//UPROPERTY(meta = (BindWidget))
	//class UTextBlock* InventoryQuestItemCount;

	//UPROPERTY(meta = (BindWidget))
	//class UTextBlock* RequiredQuestItemCount;
};
