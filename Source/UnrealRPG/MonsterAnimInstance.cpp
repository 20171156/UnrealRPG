// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "MonsterCharacterBase.h"
#include "GameFramework/PawnMovementComponent.h"

UMonsterAnimInstance::UMonsterAnimInstance()
{
}

void UMonsterAnimInstance::InitializeValue()
{
	if (nullptr != PrimaryAttackMontage)
	{
		AllSectionIndex = PrimaryAttackMontage->CompositeSections.Num();
	}
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	auto Pawn = TryGetPawnOwner();

	if (IsValid(Pawn))
	{
		Speed = Pawn->GetVelocity().Size();
	}
}

bool UMonsterAnimInstance::IsWeaponAttackMontageExist()
{
	if (nullptr == WeaponAttackMontage)
	{
		return false;
	}
	else
	{
		return true;
	}

	return false;
}

void UMonsterAnimInstance::PlayPrimaryAttackMontage()
{
	Montage_Play(PrimaryAttackMontage, 1.f);
}

void UMonsterAnimInstance::PlayWeaponAttackMontage()
{
	Montage_Play(WeaponAttackMontage, 1.f);
}

void UMonsterAnimInstance::JumpToSection(/*int32 SectionIndex*/)
{
	FName Name = GetPrimaryAttackMontageSectionName(/*SectionIndex*/);
	Montage_JumpToSection(Name, PrimaryAttackMontage);
	
	if (IsWeaponAttackMontageExist())
	{
		Montage_JumpToSection(Name, WeaponAttackMontage);
	}

	SectionIndex = (SectionIndex + 1) % AllSectionIndex;
}

FName UMonsterAnimInstance::GetPrimaryAttackMontageSectionName(/*int32 SectionIndex*/)
{
	return FName(*FString::Printf(TEXT("PrimaryAttack%d"), SectionIndex));
}

void UMonsterAnimInstance::AnimNotify_AttackHit()
{
	OnAttackHit.Broadcast();
}
