// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyBTTask_Dead.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API UMyBTTask_Dead : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UMyBTTask_Dead();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
