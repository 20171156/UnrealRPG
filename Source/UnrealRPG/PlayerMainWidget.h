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
	void BindWidget(class UStatComponent* StatComp);
	void UpdateLevel();
	void UpdateHp();
	void UpdateMp();
	void UpdateSp();
	void UpdateExp();

private:
	TWeakObjectPtr<class UStatComponent> CurrentStatComp;

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
};
