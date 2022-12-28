// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "MonsterCharacterBase.h"
#include "MonsterAIController.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;

	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<AMonsterCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (!IsValid(Monster))
		return EBTNodeResult::Failed;

	Monster->ExecuteAnimMontage(EMonsterAnimState::ATTACKING);
	bIsAttacking = true;

	Monster->OnMonsterAttackEnd.AddLambda([this]()
		{
			bIsAttacking = false;
		});

	Monster->OnMonsterAttackedStart.AddLambda([this]()
		{
			bEnd = true;
		});

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	auto Monster = Cast<AMonsterCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (!IsValid(Monster))
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	if (!bIsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	if (bEnd)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		bEnd = false;
	}

}