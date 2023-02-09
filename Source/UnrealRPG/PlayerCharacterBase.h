// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CustomEnum.h"
#include "PlayerCharacterBase.generated.h"

//DECLARE_MULTICAST_DELEGATE(FPlayerOnAttackEnd);

UCLASS()
class UNREALRPG_API APlayerCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacterBase();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void CharacterDestroy();

	UFUNCTION()
	class UStatComponent* GetStatComponent() { return CurrentStat; }

	bool GetDead() { return bIsDead; }

public:
	UFUNCTION()
	void ChangeCollisionProfile(bool bAbleOverlap);

	UFUNCTION()
	void OnWeaponOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnWeaponOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void ExecuteAnimMontage(const EPlayerAnimState AnimState);

	UFUNCTION()
	void OnAnimMontageStarted(UAnimMontage* Montage);

	UFUNCTION()
	void OnAnimMontageEnded(UAnimMontage* Montage, bool bInterrupted);

private:
	UFUNCTION()
	void PlayerHpZero();

public:
	//Delgate variable
	//FPlayerOnAttackEnd OnPlayerAttackEnd;

private:
	UPROPERTY()
	class USpringArmComponent* SpringArm;

	UPROPERTY()
	class UCameraComponent* Camera;

	UPROPERTY()
	class UStatComponent* CurrentStat;

	UPROPERTY()
	class UPlayableAnimInstance* PlayerAnimInstance;

	UPROPERTY()
	class UCapsuleComponent* WeaponCollisionComponent;

	UPROPERTY()
	bool bIsAttacking = false;

	UPROPERTY()
	bool bIsAttacked = false;

	UPROPERTY()
	bool bIsDead = false;

	UPROPERTY()
	int32 TestAttackCount = 0;
};