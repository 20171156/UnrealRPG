// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_MonsterIsDead.h"
#include "MonsterAIController.h"
#include "MonsterCharacterBase.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_MonsterIsDead::UBTService_MonsterIsDead()
{
	Interval = 0.1f;
}

void UBTService_MonsterIsDead::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (CurrentPawn == nullptr)
		return;

	AMonsterCharacterBase* Monster = Cast<AMonsterCharacterBase>(CurrentPawn);
	if (Monster)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName(TEXT("IsDead")), Monster->GetDead());
	}
}
