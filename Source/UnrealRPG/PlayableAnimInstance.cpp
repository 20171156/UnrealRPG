// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableAnimInstance.h"
#include "PlayerCharacterBase.h"
#include "PlayableController.h"
#include "GameFramework/PawnMovementComponent.h"

UPlayableAnimInstance::UPlayableAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("AnimMontage'/Game/Animations/AM_PlayerPrimaryAttack.AM_PlayerPrimaryAttack'"));
	if (AM.Succeeded())
	{
		PrimaryAttackMontage = AM.Object;
	}
}

void UPlayableAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		Speed = Pawn->GetVelocity().Size();

		//auto Player = Cast<APlayerCharacterBase>(Pawn);
		//if (Player)
		//{
		//	IsFalling = Player->GetMovementComponent()->IsFalling();
		//}
		auto PlayerController = Cast<APlayableController>(GetWorld()->GetFirstPlayerController());
		if (PlayerController)
		{
			Vertical = PlayerController->UpDownValue;
			Horizontal = PlayerController->LeftRightValue;
		}
	}
}

void UPlayableAnimInstance::PlayPrimaryAttackMontage()
{
	Montage_Play(PrimaryAttackMontage, 1.f);
}

void UPlayableAnimInstance::JumpToSection(int32 SectionIndex)
{
	FName Name = GetPrimaryAttackMontageSectionName(SectionIndex);
	Montage_JumpToSection(Name, PrimaryAttackMontage);//몽타주 섹션 건너뛰고 플레이
}

FName UPlayableAnimInstance::GetPrimaryAttackMontageSectionName(int32 SectionIndex)
{
	return FName(*FString::Printf(TEXT("PrimaryAttack%d"), SectionIndex));
}

void UPlayableAnimInstance::AnimNotify_AttackHit()
{
	OnAttackHit.Broadcast();
}
