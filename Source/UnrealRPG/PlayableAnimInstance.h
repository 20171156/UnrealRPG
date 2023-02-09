// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayableAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API UPlayableAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPlayableAnimInstance();

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	void PlayPrimaryAttackMontage();
	void PlayAttackedMontage();
	void PlayDyingMontage();

private:
	void JumpToSection(const UAnimMontage* Montage);

	UFUNCTION()
	void AnimNotify_PlayerIsDead();

private:
	UPROPERTY()
	int32 CurrentSectionIndex = 0;

	UPROPERTY()
	int32 AllSectionIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsFalling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Horizontal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Vertical;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MontageToPlay, Meta = (AllowPrivateAccess = true))
	UAnimMontage* PrimaryAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MontageToPlay, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackedMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MontageToPlay, Meta = (AllowPrivateAccess = true))
	UAnimMontage* DyingMontage;
};
