// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterHpWidget.h"
#include "MonsterStatComponent.h"
#include "Components/ProgressBar.h"
#include "Components/Button.h"

void UMonsterHpWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMonsterHpWidget::BindHp(UMonsterStatComponent* StatComp)
{
	CurrentStatComp = StatComp;
	StatComp->MonsterHpChanged.AddUObject(this, &UMonsterHpWidget::UpdateHp);
}

void UMonsterHpWidget::UpdateHp()
{
	if (CurrentStatComp.IsValid())
	{
		if (nullptr != HPBar)
		{
			HPBar->SetPercent(CurrentStatComp->GetHpRatio());
		}
	}
}
