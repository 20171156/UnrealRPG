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

	AMonsterCharacterBase* Pawn = Cast<AMonsterCharacterBase>(TryGetPawnOwner());
	Pawn->OnMonsterAttackEnd.AddUObject(this, &UMonsterAnimInstance::MonsterAttackEnded);
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();

	if (IsValid(Pawn))
	{
		Speed = Pawn->GetVelocity().Size();
	}
}

void UMonsterAnimInstance::PlayPrimaryAttackMontage()
{
	Montage_Play(PrimaryAttackMontage, 1.f);
	FName test = GetCurrentSection();
}

void UMonsterAnimInstance::JumpToSection(/*int32 SectionIndex*/)
{
	FName Name = GetPrimaryAttackMontageSectionName(/*SectionIndex*/);
	Montage_JumpToSection(Name, PrimaryAttackMontage);

	CurrentSectionIndex = (CurrentSectionIndex + 1) % AllSectionIndex;
}

const FName UMonsterAnimInstance::GetCurrentSection()
{
	return Montage_GetCurrentSection(PrimaryAttackMontage);
}

const int32& UMonsterAnimInstance::GetAllSectionIndex()
{
	return AllSectionIndex;
}

FName UMonsterAnimInstance::GetPrimaryAttackMontageSectionName(/*int32 SectionIndex*/)
{
	return FName(*FString::Printf(TEXT("PrimaryAttack%d"), CurrentSectionIndex));
}

void UMonsterAnimInstance::MonsterAttackEnded()
{
	//CurrentSectionIndex = 0;
}

void UMonsterAnimInstance::AnimNotify_AttackHit()
{
	OnAttackHit.Broadcast();
}

void UMonsterAnimInstance::AnimNotify_BowAnimChange()
{
	FName name = GetCurrentSection();
	OnWeaponAnimChange.Broadcast(name);
}