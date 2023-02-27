// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameEndWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API UGameEndWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UGameEndWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnClickedButton();

private:
	UPROPERTY(Meta = (BindWidget))
	class UButton* QuitButton;
};
