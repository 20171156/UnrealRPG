// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

AMonsterAIController::AMonsterAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BB(TEXT("BlackboardData'/Game/AI/SkeletonAI/BB_Monster.BB_Monster'"));
	if (BB.Succeeded())
	{
		BlackboardData = BB.Object;
	}
}

void AMonsterAIController::BeginPlay()
{
	Super::BeginPlay();

}

void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//if (UseBlackboard(BlackboardData, Blackboard))
	//{
		//if (RunBehaviorTree(BehaviorTree))
		//{
		//	UE_LOG(LogTemp, Log, TEXT("BlackboardData and BehaviorTree Load!"));
		//}
	//}
}

void AMonsterAIController::OnUnPossess()
{
	Super::OnUnPossess();
}