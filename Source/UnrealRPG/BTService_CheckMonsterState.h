// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckMonsterState.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API UBTService_CheckMonsterState : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_CheckMonsterState();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
