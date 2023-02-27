// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CustomStruct.h"
#include "GameFramework/GameModeBase.h"
#include "UnrealRPGGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API AUnrealRPGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AUnrealRPGGameModeBase();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UFUNCTION()
	void OpenGameEndWidget();

	UFUNCTION()
	void OpenInventory();

	UFUNCTION()
	void CloseInventory();

	UFUNCTION()
	void OpenDialogWidget(FString NPCName, TArray<FString> NPCDialog);

	UFUNCTION()
	void UpdateDialogWidget();

	UFUNCTION()
	void CloseDialogWidget();
	
	UFUNCTION()
	bool CheckOpenDialogWidget() { return IsOpenDialogWidget; }

private:
	UFUNCTION()
	void UpdatePlayerInteracting();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UPlayerMainWidget> PlayerMainWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UInventoryWidget> InventoryWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UGameEndWidget> GameEndWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UDialogWidget> NPCDialogWidgetClass;

private:
	UPROPERTY()
	UPlayerMainWidget* PlayerMainWidget;

	UPROPERTY()
	UInventoryWidget* InventoryWidget;

	UPROPERTY()
	UGameEndWidget* GameEndWidget;

	UPROPERTY()
	UDialogWidget* NPCDialogWidget;

	UPROPERTY()
	bool IsOpenDialogWidget = false;
};
