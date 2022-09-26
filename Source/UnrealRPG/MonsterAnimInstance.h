// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackHit);

/**
 * 
 */
UCLASS()
class UNREALRPG_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMonsterAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	void InitializeValue();

public:
	bool IsWeaponAttackMontageExist();
	void PlayPrimaryAttackMontage();
	void PlayWeaponAttackMontage();//If exist WeaponAnimation, Play this function
	void JumpToSection(/*int32 SectionIndex*/);

private:
	FName GetPrimaryAttackMontageSectionName(/*int32 SectionIndex*/);

	//AllClass Notify
	UFUNCTION()
	void AnimNotify_AttackHit();

public:
	FOnAttackHit OnAttackHit;

private:
	UPROPERTY()
	int32 SectionIndex = 0;

	UPROPERTY()
	int32 AllSectionIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MontageToPlay, Meta = (AllowPrivateAccess = true))
	UAnimMontage* PrimaryAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MontageToPlay, Meta = (AllowPrivateAccess = true))
	UAnimMontage* WeaponAttackMontage;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MontageToPlay, Meta = (AllowPrivateAccess = true))
	//UAnimMontage* PrimaryAttackMontage;
};
