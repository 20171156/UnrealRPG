// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacterBase.generated.h"

DECLARE_MULTICAST_DELEGATE(FPlayerOnAttackEnd);

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
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void IsAttacking(bool bIsAttacking_)
	{
		if (bIsAttacking_)
		{
			bIsOverlapped = false;
		}
		bIsAttacking = bIsAttacking_;
	}
	void IsAttacked(bool bIsAttacked_) { bIsAttacked = bIsAttacked_; }

	bool GetAttacking() { return bIsAttacking; }
	bool GetAttacked() { return bIsAttacked; }

public:
	//Delgate variable
	FPlayerOnAttackEnd OnPlayerAttackEnd;

public:
	UFUNCTION()
	void ChangeCollisionProfile();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void PrimaryAttack();

	UFUNCTION()
	void OnPrimaryAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

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
	bool bIsOverlapped = false;

	UPROPERTY()
	bool bIsDeath = false;

	UPROPERTY()
	bool bIsPlayAnimation = false;

	UPROPERTY()
	int32 AttackIndex = 0;

	UPROPERTY()
	int32 TestAttackCount = 0;

	//충돌체크 변수 임시저장
	UPROPERTY()
	AActor* OverlapActor;

	UPROPERTY()
	UPrimitiveComponent* OverlapComp;
};