// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcheryAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CustomEnum.h"

AArcheryAIController::AArcheryAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("BehaviorTree'/Game/AI/SkeletonAI/BT_ArcheryMonster.BT_ArcheryMonster'"));
	if (BT.Succeeded())
	{
		BehaviorTree = BT.Object;
	}
}

void AArcheryAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AArcheryAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BlackboardData, Blackboard))
	{
		if (RunBehaviorTree(BehaviorTree))
		{
			GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("State")), (uint8)EMonsterAnimState::PEACE);
			GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("PreviousState")), (uint8)EMonsterAnimState::PEACE);
			UE_LOG(LogTemp, Log, TEXT("ArcheryAI Load Complete!"));
		}
	}
}

void AArcheryAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
