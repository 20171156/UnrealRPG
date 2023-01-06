// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attacked.h"
#include "MonsterCharacterBase.h"
#include "SkeletonCharacterBase.h"
#include "MonsterAIController.h"

UBTTask_Attacked::UBTTask_Attacked()
{
	bNotifyTick = true;

	NodeName = TEXT("Attacked");
}

EBTNodeResult::Type UBTTask_Attacked::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<ASkeletonCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (!IsValid(Monster))
		return EBTNodeResult::Failed;

	bIsAttacked = true;

	Monster->OnMonsterAttackedEnd.AddLambda([this]()
		{
			bIsAttacked = false;
		});

	Monster->OnMonsterAttackedStart.AddLambda([this]()
		{
			bIsAttacked = false;
		});

	return EBTNodeResult::InProgress;
}

void UBTTask_Attacked::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!bIsAttacked)
	{
		//Attacked Animation이 종료되면 그 이전의 행동으로 복귀해야 한다
		auto Monster = Cast<AMonsterCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
		if (!IsValid(Monster))
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}