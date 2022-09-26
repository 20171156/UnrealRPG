// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RotateToTarget.h"
#include "MonsterCharacterBase.h"
#include "PlayerCharacterBase.h"
#include "MonsterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_RotateToTarget::UBTTask_RotateToTarget()
{
}

EBTNodeResult::Type UBTTask_RotateToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	//auto CurrentPawn = Cast<AMonsterCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == CurrentPawn)
		return EBTNodeResult::Failed;

	auto Target = Cast<APlayerCharacterBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));
	if (nullptr == Target)
		return EBTNodeResult::Failed;

	FVector LookVector = Target->GetActorLocation() - CurrentPawn->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	CurrentPawn->SetActorRotation(FMath::RInterpTo(CurrentPawn->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));

	return EBTNodeResult::Succeeded;
}
