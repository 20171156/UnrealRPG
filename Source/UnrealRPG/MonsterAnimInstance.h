// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackHit);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnWeaponAnimChange, FName);

/**
 * 
 */
UCLASS()
class UNREALRPG_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMonsterAnimInstance();
	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	void PlayPrimaryAttackMontage();
	void JumpToSection(/*int32 SectionIndex*/);
	const FName GetCurrentSection();
	
	const int32& GetAllSectionIndex();

private:
	FName GetPrimaryAttackMontageSectionName(/*int32 SectionIndex*/);
	void MonsterAttackEnded();

	//AllClass Notify
	UFUNCTION()
	void AnimNotify_AttackHit();

	UFUNCTION()
	void AnimNotify_BowAnimChange();

public:
	FOnAttackHit OnAttackHit;
	FOnWeaponAnimChange OnWeaponAnimChange;

private:
	UPROPERTY()
	int32 CurrentSectionIndex = 0;

	UPROPERTY()
	int32 AllSectionIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MontageToPlay, Meta = (AllowPrivateAccess = true))
	UAnimMontage* PrimaryAttackMontage;
};