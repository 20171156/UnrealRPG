// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_Dead.h"

UMyBTTask_Dead::UMyBTTask_Dead()
{
}

EBTNodeResult::Type UMyBTTask_Dead::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	return EBTNodeResult::InProgress;
}

void UMyBTTask_Dead::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
