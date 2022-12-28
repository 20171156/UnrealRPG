// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "MonsterCharacterBase.h"
#include "GameFramework/PawnMovementComponent.h"

UMonsterAnimInstance::UMonsterAnimInstance()
{
}

void UMonsterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (nullptr != PrimaryAttackMontage)
	{
		AllSectionIndex = PrimaryAttackMontage->CompositeSections.Num();
	}

}

void UMonsterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();

	if (!bIsDead && IsValid(Pawn))
	{
		Speed = Pawn->GetVelocity().Size();
	}
}

void UMonsterAnimInstance::PlayPrimaryAttackMontage()
{
	Montage_Play(PrimaryAttackMontage, 1.f);

	auto Pawn = TryGetPawnOwner();
	if (!Cast<AMonsterCharacterBase>(Pawn)->GetMonsterArcherType())
	{
		JumpToSection();
	}
}

void UMonsterAnimInstance::PlayAttackedMontage()
{
	Montage_Play(AttackedMontage, 1.0f);
}

void UMonsterAnimInstance::PlayDyingMontage()
{
	Montage_Play(DyingMontage, 1.f);
}

void UMonsterAnimInstance::JumpToSection()
{
	FName Name = GetPrimaryAttackMontageSectionName();
	Montage_JumpToSection(Name, PrimaryAttackMontage);
	
	CurrentSectionIndex = (CurrentSectionIndex + 1) % AllSectionIndex;
}

const FName UMonsterAnimInstance::GetCurrentSection()
{
	return Montage_GetCurrentSection(PrimaryAttackMontage);
}

FName UMonsterAnimInstance::GetPrimaryAttackMontageSectionName()
{
	return FName(*FString::Printf(TEXT("PrimaryAttack%d"), CurrentSectionIndex));
}

void UMonsterAnimInstance::AnimNotify_BowAnimChange()
{
	FName name = GetCurrentSection();

	OnWeaponAnimChange.Broadcast(name);
}