// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetState.h"
#include "MonsterAIController.h"
#include "MonsterCharacterBase.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetState::UBTTask_SetState()
{
	//bNotifyTick = false;
}

EBTNodeResult::Type UBTTask_SetState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (CurrentPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AMonsterCharacterBase* Monster = Cast<AMonsterCharacterBase>(CurrentPawn);
	if (Monster)
	{
		//uint8 PreviousState = OwnerComp.GetBlackboardComponent()->GetValueAsEnum(FName(TEXT("State")));
		//OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("PreviousState")), PreviousState);
		
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("State")), (uint8)State);
		Monster->SetState(State);
	}

	return EBTNodeResult::Succeeded;
}
