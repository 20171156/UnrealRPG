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
	void BindWidget(FString NPCName, TArray<FString> NPCDialogArray);

	UFUNCTION()
	void UpdateDialog();

private:
	UFUNCTION()
	void CloseDialog();

private:
	UPROPERTY()
	TArray<FString> DialogArray;

	UPROPERTY()
	int32 DialogCount = 0;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NPCNameText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NPCDialogText;

};
