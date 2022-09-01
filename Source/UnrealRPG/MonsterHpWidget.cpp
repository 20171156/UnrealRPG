// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterHpWidget.h"
#include "MonsterStatComponent.h"
#include "Components/ProgressBar.h"

void UMonsterHpWidget::BindHp(UMonsterStatComponent* StatComp)
{
	CurrentStatComp = StatComp;
	StatComp->MonsterHpChanged.AddUObject(this, &UMonsterHpWidget::UpdateHp);
}

void UMonsterHpWidget::UpdateHp()
{
	if (CurrentStatComp.IsValid())
	{
		PB_HpBar->SetPercent(CurrentStatComp->GetHpRatio());
	}
}
