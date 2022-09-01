// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPatrolPos.h"
#include "MonsterAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MonsterCharacterBase.h"
#include "MonsterAnimInstance.h"

UBTTask_FindPatrolPos::UBTTask_FindPatrolPos()
{
	NodeName = TEXT("FindPatrolPos");
}

EBTNodeResult::Type UBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (CurrentPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (NavSystem == nullptr)
		return EBTNodeResult::Failed;

	FNavLocation RandomLocation;
	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.f, RandomLocation))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("PatrolPos")), RandomLocation.Location);
		
		//FVector CurrentPawnLocation = Cast<AMonsterCharacterBase>(CurrentPawn)->GetMesh()->GetComponentLocation();
		//FVector CurrentPawnLocation = CurrentPawn->GetActorLocation();
		//FVector ToTarget = RandomLocation.Location - CurrentPawnLocation;
		//FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
		//Cast<AMonsterCharacterBase>(CurrentPawn)->GetMesh()->SetWorldRotation(LookAtRotation);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
