// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterAIController.h"
#include "SorceryAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API ASorceryAIController : public AMonsterAIController
{
	GENERATED_BODY()

public:
	ASorceryAIController();

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	UPROPERTY()
	class UBehaviorTree* BehaviorTree;
	
};
