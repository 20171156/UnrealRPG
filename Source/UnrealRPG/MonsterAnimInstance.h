// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomEnum.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnWeaponAnimStop);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnWeaponAnimChange, FName);

UCLASS()
class UNREALRPG_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMonsterAnimInstance();
	
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	void PlayPrimaryAttackMontage();
	void PlayAttackedMontage();
	void PlayDyingMontage();
	void Stop();

private:
	void JumpToSection(const UAnimMontage* Montage);

	const FName GetCurrentSection();
	
private:
	UFUNCTION()
	void AnimNotify_BowAnimChange();

	UFUNCTION()
	void AnimNotify_BowAnimStop();

	UFUNCTION()
	void AnimNotify_MonsterIsDead();

	UFUNCTION()
	void AnimNotify_FireProjectile();

	UFUNCTION()
	void AnimNotify_SpawnArrow();

	UFUNCTION()
	void AnimNotify_FireArrow();

public:
	FOnWeaponAnimChange OnWeaponAnimChange;
	FOnWeaponAnimStop OnWeaponAnimStop;

private:
	UPROPERTY()
	int32 CurrentSectionIndex = 0;

	UPROPERTY()
	int32 AllSectionIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bIsDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MontageToPlay, Meta = (AllowPrivateAccess = true))
	UAnimMontage* PrimaryAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MontageToPlay, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackedMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MontageToPlay, Meta = (AllowPrivateAccess = true))
	UAnimMontage* DyingMontage;
};