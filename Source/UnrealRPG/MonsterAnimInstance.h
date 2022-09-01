// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

//DECLARE_MULTICAST_DELEGATE(FMonsterSpawningMontage);
//DECLARE_MULTICAST_DELEGATE(FMonsterAttackHitMontage);
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

private:
	void PlayMontage();

	UFUNCTION()
	void AnimNotify_SpawningMontage();

public:
	//FMonsterSpawningMontage MonsterSpawningMontage;
	//FMonsterAttackHitMontage MonsterAttackHitMontage;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsFalling;

	//추후 aicontroller에 의해 움직일 때 받아와서 체크할 것
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Horizontal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Vertical;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	//UAnimMontage* SpawningMontage;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	//UAnimMontage* PrimaryAttackMontage;
};
