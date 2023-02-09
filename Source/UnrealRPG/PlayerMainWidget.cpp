// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMainWidget.h"
#include "StatComponent.h"
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

void UPlayerMainWidget::BindWidget(UStatComponent* StatComp)
{
	CurrentStatComp = StatComp;

	StatComp->PlayerLevelChanged.AddUObject(this, &UPlayerMainWidget::UpdateLevel);
	StatComp->PlayerHpChanged.AddUObject(this, &UPlayerMainWidget::UpdateHp);
	StatComp->PlayerMpChanged.AddUObject(this, &UPlayerMainWidget::UpdateMp);
	StatComp->PlayerSpChanged.AddUObject(this, &UPlayerMainWidget::UpdateSp);
	StatComp->PlayerExpChanged.AddUObject(this, &UPlayerMainWidget::UpdateExp);
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
