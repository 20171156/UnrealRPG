// Fill out your copyright notice in the Description page of Project Settings.


#include "SorceryAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

ASorceryAIController::ASorceryAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("BehaviorTree'/Game/AI/SkeletonAI/BT_SorceryMonster.BT_SorceryMonster'"));
	if (BT.Succeeded())
	{
		BehaviorTree = BT.Object;
	}
}

void ASorceryAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ASorceryAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BlackboardData, Blackboard))
	{
		if (RunBehaviorTree(BehaviorTree))
		{
			UE_LOG(LogTemp, Log, TEXT("SorceryAI Load Complete!"));
		}
	}
}

void ASorceryAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
