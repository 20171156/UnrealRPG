// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UPlayerMainWidget> PlayerMainWidgetClass;

private:
	UPROPERTY()
	UPlayerMainWidget* PlayerMainWidget;
};
