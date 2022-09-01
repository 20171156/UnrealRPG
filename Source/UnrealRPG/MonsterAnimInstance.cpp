// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "MonsterCharacterBase.h"
#include "GameFramework/PawnMovementComponent.h"

UMonsterAnimInstance::UMonsterAnimInstance()
{
	//static ConstructorHelpers::FObjectFinder<UAnimMontage> SpawningM(TEXT("AnimMontage'/Game/Animations/SkeletonWarloadSpawning_Montage.SkeletonWarloadSpawning_Montage'"));
	//if (SpawningM.Succeeded())
	//{
	//	SpawningMontage = SpawningM.Object;
	//}
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	auto Pawn = TryGetPawnOwner();

	if (IsValid(Pawn))
	{
		Speed = Pawn->GetVelocity().Size();

		auto Monster = Cast<AMonsterCharacterBase>(Pawn);
	}
}

void UMonsterAnimInstance::PlayMontage()
{
}

void UMonsterAnimInstance::AnimNotify_SpawningMontage()
{
}
