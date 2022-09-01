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
	//�𸮾� ������Ʈ�� ���������ͷ� �����ǰ� �����Ƿ� �ٸ� ������Ʈ�� �����;� �� ���� �ǵ��� �������� ����� ��
	TWeakObjectPtr<class UMonsterStatComponent> CurrentStatComp;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_HpBar;
};