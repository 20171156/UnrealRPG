// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MonsterHpWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API UMonsterHpWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindHp(class UMonsterStatComponent* StatComp);

	void UpdateHp();

private:
	//언리얼 오브젝트는 공유포인터로 관리되고 있으므로 다른 오브젝트를 가져와야 할 때는 되도록 약포인터 사용할 것
	TWeakObjectPtr<class UMonsterStatComponent> CurrentStatComp;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_HpBar;
};