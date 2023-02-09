// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "MonsterCharacterBase.h"
#include "SkeletonCharacterBase.h"
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
		JumpToSection(PrimaryAttackMontage);
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

void UMonsterAnimInstance::Stop()
{
	Montage_Stop(0.f, DyingMontage);
}

void UMonsterAnimInstance::JumpToSection(const UAnimMontage* Montage)
{
	FName Name = Montage->GetSectionName(CurrentSectionIndex);
	Montage_JumpToSection(Name, Montage);
	
	CurrentSectionIndex = (CurrentSectionIndex + 1) % AllSectionIndex;
}

const FName UMonsterAnimInstance::GetCurrentSection()
{
	return Montage_GetCurrentSection(PrimaryAttackMontage);
}

void UMonsterAnimInstance::AnimNotify_BowAnimChange()
{
	FName name = GetCurrentSection();

	OnWeaponAnimChange.Broadcast(name);
}

void UMonsterAnimInstance::AnimNotify_BowAnimStop()
{
	OnWeaponAnimStop.Broadcast();
}

void UMonsterAnimInstance::AnimNotify_MonsterIsDead()
{
	auto Pawn = TryGetPawnOwner();
	Cast<AMonsterCharacterBase>(Pawn)->CharacterDestroy();
}

void UMonsterAnimInstance::AnimNotify_FireProjectile()
{
	auto Pawn = TryGetPawnOwner();
	Cast<ASkeletonCharacterBase>(Pawn)->FireMagic();
}

void UMonsterAnimInstance::AnimNotify_SpawnArrow()
{
	auto Pawn = TryGetPawnOwner();
	Cast<ASkeletonCharacterBase>(Pawn)->SpawnArrow();
}

void UMonsterAnimInstance::AnimNotify_FireArrow()
{
	auto Pawn = TryGetPawnOwner();
	Cast<ASkeletonCharacterBase>(Pawn)->FireArrow();
}
