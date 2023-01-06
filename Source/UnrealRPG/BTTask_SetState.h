// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CustomEnum.h"
#include "BTTask_SetState.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API UBTTask_SetState : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_SetState();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, Category = Blackboard)
	EMonsterAnimState State;
};
