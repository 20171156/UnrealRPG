// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SearchTarget.h"
#include "MonsterAIController.h"
#include "PlayerCharacterBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MonsterCharacterBase.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"

UBTService_SearchTarget::UBTService_SearchTarget()
{
	NodeName = TEXT("SearchTarget");
	Interval = 1.f;
}

void UBTService_SearchTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (CurrentPawn == nullptr)
		return;

	UWorld* World = CurrentPawn->GetWorld();
	FVector Center = CurrentPawn->GetActorLocation();
	float SearchRadius = 500.f;

	if (World == nullptr)
		return;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams QueryParams(NAME_None, false, CurrentPawn);//자기자신 제외

	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(SearchRadius),
		QueryParams);

	if (bResult)
	{
		for (auto& OverlapResult : OverlapResults)
		{
			if (OverlapResult.GetActor()->ActorHasTag("Player"))
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), OverlapResult.GetActor());

				Cast<AMonsterCharacterBase>(CurrentPawn)->ChangeMonsterState(EMonsterState::FOLLOWPLAYER);
				DrawDebugSphere(World, Center, SearchRadius, 16, FColor::Green, false, 0.2f);

				return;
			}
		}

		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), nullptr);

		Cast<AMonsterCharacterBase>(CurrentPawn)->ChangeMonsterState(EMonsterState::AROUND);
		DrawDebugSphere(World, Center, SearchRadius, 16, FColor::Red, false, 0.2f);
	}
	else
	{
		//바닥에도 안붙어있단 소리임
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), nullptr);

		Cast<AMonsterCharacterBase>(CurrentPawn)->ChangeMonsterState(EMonsterState::AROUND);
		DrawDebugSphere(World, Center, SearchRadius, 16, FColor::Red, false, 0.2f);
	}
}