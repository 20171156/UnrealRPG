// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetPreviousState.h"
#include "MonsterAIController.h"
#include "MonsterCharacterBase.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetPreviousState::UBTTask_SetPreviousState()
{

}

EBTNodeResult::Type UBTTask_SetPreviousState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
		uint8 State = OwnerComp.GetBlackboardComponent()->GetValueAsEnum(FName(TEXT("PreviousState")));
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("State")), State);

		State = OwnerComp.GetBlackboardComponent()->GetValueAsEnum(FName(TEXT("State")));
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("PreviousState")), (uint8)State);

		Monster->SetState((EMonsterAnimState)State);
	}

	return EBTNodeResult::Succeeded;
}

void UBTTask_SetPreviousState::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}
