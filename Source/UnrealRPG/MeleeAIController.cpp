// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

AMeleeAIController::AMeleeAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("BehaviorTree'/Game/AI/SkeletonAI/BT_MeleeMonster.BT_MeleeMonster'"));
	if (BT.Succeeded())
	{
		BehaviorTree = BT.Object;
	}
}

void AMeleeAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AMeleeAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BlackboardData, Blackboard))
	{
		if (RunBehaviorTree(BehaviorTree))
		{
			UE_LOG(LogTemp, Log, TEXT("MeleeAI Load Complete!"));
		}
	}
}

void AMeleeAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
