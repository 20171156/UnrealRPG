// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckMonsterState.h"
#include "MonsterAIController.h"
#include "MonsterCharacterBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CustomEnum.h"

UBTService_CheckMonsterState::UBTService_CheckMonsterState()
{
}

void UBTService_CheckMonsterState::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (CurrentPawn == nullptr)
		return;

	AMonsterCharacterBase* Monster = Cast<AMonsterCharacterBase>(CurrentPawn);
	if (Monster)
	{
		//if (EMonsterAnimState::ATTACKED <= Monster->GetCurrentAnimState())
		//{
			//auto State = Monster->GetCurrentAnimState();
			//if (Monster->GetDead())
			//{
			//	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("State")), (uint8)EMonsterAnimState::DEAD);
			//}
			//else if(Monster->GetAttacked())
			//{
			//	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("State")), (uint8)EMonsterAnimState::ATTACKED);
			//}
			//else
			//{
			//	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("State")), (uint8)State);
			//	return;
			//}

		auto test1 = Monster->GetPreviousAnimState();
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("PreviousState")), (uint8)test1);

		auto test2 = Monster->GetCurrentAnimState();
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("State")), (uint8)test2);
		//}
	}
}