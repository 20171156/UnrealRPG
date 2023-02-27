// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API UDialogWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UDialogWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void BindWidget(ACharacter* NPCClass/*class ANPC* NPCClass*/);

	UFUNCTION()
	void UpdateDialog();

private:
	UFUNCTION()
	void CloseDialog();

private:
	UPROPERTY()
	class ANPC* NPC;

	UPROPERTY()
	TArray<FString> DialogArray;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NPCName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NPCDialog;

	UPROPERTY(meta = (BindWidget))
	int32 DialogCount = 0;
};
