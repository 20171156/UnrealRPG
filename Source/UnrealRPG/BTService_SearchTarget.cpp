// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SearchTarget.h"
#include "MonsterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PlayerCharacterBase.h"
#include "MonsterCharacterBase.h"
#include "CustomEnum.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"

UBTService_SearchTarget::UBTService_SearchTarget()
{
	SearchRadius = 500.f;
	NodeName = TEXT("SearchTarget");
	Interval = 1.f;
}

void UBTService_SearchTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	//if (CurrentPawn == nullptr)
	//	return;
	auto Monster = Cast<AMonsterCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (!IsValid(Monster))
		return;

	UWorld* World = Monster->GetWorld();
	FVector Center = Monster->GetActorLocation();
	//float SearchRadius = 500.f;

	if (World == nullptr)
		return;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams QueryParams(NAME_None, false, Monster);//자기자신 제외

	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(SearchRadius),
		QueryParams);

	if (bResult)
	{
		for (auto& OverlapResult : OverlapResults)
		{
			if (OverlapResult.GetActor()->ActorHasTag("Player"))
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), OverlapResult.GetActor());
				
				DrawDebugSphere(World, Center, SearchRadius, 16, FColor::Green, false, 0.1f);

				return;
			}
		}

		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), nullptr);
		
		DrawDebugSphere(World, Center, SearchRadius, 16, FColor::Red, false, 0.1f);
	}
	else
	{
		//바닥에도 안붙어있단 소리임
		//추후 데스처리할 것
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), nullptr);
		DrawDebugSphere(World, Center, SearchRadius, 16, FColor::Red, false, 0.1f);
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Search Target..."));
}