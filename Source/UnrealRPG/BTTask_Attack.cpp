// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "MonsterCharacterBase.h"
#include "SkeletonCharacterBase.h"
#include "MonsterAIController.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;

	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto CurrentPawn = Cast<ASkeletonCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (CurrentPawn == nullptr)
		return EBTNodeResult::Failed;

	CurrentPawn->PrimaryAttack();
	bIsAttacking = true;
	Cast<AMonsterCharacterBase>(CurrentPawn)->ChangeMonsterState(EMonsterState::ATTACKING);

	CurrentPawn->OnMonsterAttackEnd.AddLambda([this]()
		{
			bIsAttacking = false;
		});

	//UE_LOG(LogTemp, Log, TEXT("Monster Attacking!"));
	
	return Result;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!bIsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
