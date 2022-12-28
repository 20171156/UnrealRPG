// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponAnimInstance.h"

UWeaponAnimInstance::UWeaponAnimInstance()
{
	
}

void UWeaponAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (nullptr != WeaponAttackMontage)
	{
		AllSectionIndex = WeaponAttackMontage->CompositeSections.Num();
	}
}

void UWeaponAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UWeaponAnimInstance::PlayWeaponAttackMontage()
{
	Montage_Play(WeaponAttackMontage, 1.f);
}

void UWeaponAnimInstance::JumpToSection(FName SectionName)
{
	Montage_JumpToSection(SectionName, WeaponAttackMontage);
}

//const FName UWeaponAnimInstance::GetCurrentSection()
//{
//	return Montage_GetCurrentSection(WeaponAttackMontage);
//}

void UWeaponAnimInstance::AnimNotify_StopAnim()
{
	Montage_Pause(WeaponAttackMontage);
}
