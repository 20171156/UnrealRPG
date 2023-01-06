// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "WeaponAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API UWeaponAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UWeaponAnimInstance();
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	void PlayWeaponAttackMontage();
	void JumpToSection(FName SectionName);
	
	//const FName GetCurrentSection();

private:
	UFUNCTION()
	void AnimNotify_PauseWeapon();

private:
	UPROPERTY()
	int32 AllSectionIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MontageToPlay, Meta = (AllowPrivateAccess = true))
	UAnimMontage* WeaponAttackMontage;
};
