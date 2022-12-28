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
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	void PlayPrimaryAttackMontage();
	void JumpToSection(int32 SectionIndex);

private:
	FName GetPrimaryAttackMontageSectionName(int32 SectionIndex);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsFalling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Horizontal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Vertical;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* PrimaryAttackMontage;
};
