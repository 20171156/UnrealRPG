// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Attacked.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API UBTTask_Attacked : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_Attacked();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	bool bIsAttacked = false;

};
