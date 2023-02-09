// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableAnimInstance.h"
#include "PlayerCharacterBase.h"
#include "PlayableController.h"
#include "GameFramework/PawnMovementComponent.h"

UPlayableAnimInstance::UPlayableAnimInstance()
{
}

void UPlayableAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (nullptr != PrimaryAttackMontage)
	{
		AllSectionIndex = PrimaryAttackMontage->CompositeSections.Num();
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

	JumpToSection(PrimaryAttackMontage);
}

void UPlayableAnimInstance::PlayAttackedMontage()
{
	Montage_Play(AttackedMontage, 1.f);
}

void UPlayableAnimInstance::PlayDyingMontage()
{
	Montage_Play(DyingMontage, 1.f);
}

void UPlayableAnimInstance::JumpToSection(const UAnimMontage* Montage)
{
	FName Name = Montage->GetSectionName(CurrentSectionIndex);
	Montage_JumpToSection(Name, Montage);

	CurrentSectionIndex = (CurrentSectionIndex + 1) % AllSectionIndex;
}

void UPlayableAnimInstance::AnimNotify_PlayerIsDead()
{
	auto Pawn = TryGetPawnOwner();
	Cast<APlayerCharacterBase>(Pawn)->CharacterDestroy();
}
