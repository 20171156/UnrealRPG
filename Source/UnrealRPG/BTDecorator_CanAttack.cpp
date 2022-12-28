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

	//auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	//if (CurrentPawn == nullptr)
	//{
	//	return false;
	//}
	auto Monster = Cast<AMonsterCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (!IsValid(Monster))
		return false;

	auto Target = Cast<APlayerCharacterBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));
	if (!IsValid(Target))
	{
		return false;
	}

	return bResult && Target->GetDistanceTo(Monster) <= 200.f;
}
