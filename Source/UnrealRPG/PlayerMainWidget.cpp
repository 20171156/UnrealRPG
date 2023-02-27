// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMainWidget.h"
#include "StatComponent.h"
#include "Inventory.h"
#include "PlayerQuestSystem.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

UPlayerMainWidget::UPlayerMainWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UPlayerMainWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerMainWidget::BindWidget(UStatComponent* StatCompClass, UInventory* InventoryClass, UPlayerQuestSystem* QuestClass)
{
	if (IsValid(StatCompClass) && IsValid(InventoryClass))
	{
		CurrentStatComp = StatCompClass;
		Inventory = InventoryClass;
		QuestSystem = QuestClass;

		StatCompClass->PlayerLevelChanged.AddUObject(this, &UPlayerMainWidget::UpdateLevel);
		StatCompClass->PlayerHpChanged.AddUObject(this, &UPlayerMainWidget::UpdateHp);
		StatCompClass->PlayerMpChanged.AddUObject(this, &UPlayerMainWidget::UpdateMp);
		StatCompClass->PlayerSpChanged.AddUObject(this, &UPlayerMainWidget::UpdateSp);
		StatCompClass->PlayerExpChanged.AddUObject(this, &UPlayerMainWidget::UpdateExp);

		InventoryClass->ChangeHPPotion.AddUObject(this, &UPlayerMainWidget::UpdateHPPotionNum);
		InventoryClass->ChangeMPPotion.AddUObject(this, &UPlayerMainWidget::UpdateMPPotionNum);

		QuestClass->ChangeQuestData.AddUObject(this, &UPlayerMainWidget::UpdateQuestDialog);
		QuestClass->ChangeQuestData.AddUObject(this, &UPlayerMainWidget::UpdateQuestItemCount);
		InventoryClass->OnAddQuestItem.AddUObject(this, &UPlayerMainWidget::UpdateQuestItemCount);
	}
}

void UPlayerMainWidget::UpdateLevel()
{
	if (CurrentStatComp.IsValid())
	{
		if (nullptr != LevelText)
		{
			FString InttoString = FString::FromInt(CurrentStatComp->GetLevel());
			LevelText->SetText(FText::FromString(InttoString));
		}
	}
}

void UPlayerMainWidget::UpdateHp()
{
	if (CurrentStatComp.IsValid())
	{
		if (nullptr != HPBar)
		{
			HPBar->SetPercent(CurrentStatComp->GetHpRatio());
		}
	}
}

void UPlayerMainWidget::UpdateMp()
{
	if (CurrentStatComp.IsValid())
	{
		if (nullptr != MPBar)
		{
			MPBar->SetPercent(CurrentStatComp->GetMpRatio());
		}
	}
}

void UPlayerMainWidget::UpdateSp()
{
	if (CurrentStatComp.IsValid())
	{
		if (nullptr != SPBar)
		{
			SPBar->SetPercent(CurrentStatComp->GetSpRatio());
		}
	}
}

void UPlayerMainWidget::UpdateExp()
{
	if (CurrentStatComp.IsValid())
	{
		if (nullptr != EXPBar)
		{
			EXPBar->SetPercent(CurrentStatComp->GetExpRatio());
		}
	}
}

void UPlayerMainWidget::UpdateHPPotionNum()
{
	if (Inventory.IsValid())
	{
		if (nullptr != HPPotionNum)
		{
			FString InttoString = FString::FromInt(Inventory->GetItemCount(FName("HPPotion")));
			HPPotionNum->SetText(FText::FromString(InttoString));
		}
	}
}

void UPlayerMainWidget::UpdateMPPotionNum()
{
	if (Inventory.IsValid())
	{
		if (nullptr != MPPotionNum)
		{
			FString InttoString = FString::FromInt(Inventory->GetItemCount(FName("MPPotion")));
			MPPotionNum->SetText(FText::FromString(InttoString));
		}
	}
}

void UPlayerMainWidget::UpdateQuestDialog()
{
	if (QuestSystem.IsValid())
	{
		FQuestData Quest = QuestSystem->GetQuestData();
		if (FString{} == Quest.QuestDialog)//퀘스트 데이터가 비어있다면 비어있다고 표시해주기
		{
			FName Text = FName("No Quest");
			QuestText->SetText(FText::FromName(Text));
		}
		else
		{
			if (nullptr != QuestText)
			{
				QuestText->SetText(FText::FromString(Quest.QuestDialog));
			}
		}
	}
}

void UPlayerMainWidget::UpdateQuestItemCount()
{
	if (Inventory.IsValid())
	{
		FQuestData Quest = QuestSystem->GetQuestData();
		
		if (nullptr != QuestItemCount)
		{
			int32 CurrentCount = Inventory->GetItemCount(FName(*Quest.QuestItemName));
			FString CountText = FString::Printf(TEXT("%d / %d"), CurrentCount, Quest.QuestRequireCount);
			QuestItemCount->SetText(FText::FromString(CountText));

			if (CurrentCount >= Quest.QuestRequireCount)
			{
				ChangeQuestDialogColor();
			}
		}
	}
}

void UPlayerMainWidget::ChangeQuestDialogColor()
{
	QuestItemCount->SetColorAndOpacity(FLinearColor::Red);
}
