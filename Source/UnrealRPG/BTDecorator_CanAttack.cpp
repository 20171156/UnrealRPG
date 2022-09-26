// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CanAttack.h"
#include "MonsterCharacterBase.h"
#include "MonsterAIController.h"
#include "PlayerCharacterBase.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_CanAttack::UBTDecorator_CanAttack()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_CanAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (CurrentPawn == nullptr)
	{
		return false;
	}

	auto Target = Cast<APlayerCharacterBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));
	if (Target == nullptr)
	{
		Cast<AMonsterCharacterBase>(CurrentPawn)->ChangeMonsterState(EMonsterState::FOLLOWPLAYER);
		return false;
	}

	return bResult && Target->GetDistanceTo(CurrentPawn) <= 200.f;
}
