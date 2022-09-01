// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CustomEnum.h"
#include "PlayerCharacterBase.generated.h"

DECLARE_MULTICAST_DELEGATE(FPlayerOnAttackEnd);

UCLASS()
class UNREALRPG_API APlayerCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetAttacking(bool bIsAttack) { bIsAttacking = bIsAttack; }
	bool GetAttacking() { return bIsAttacking; }

public:
	//Delgate variable
	FPlayerOnAttackEnd OnPlayerAttackEnd;

public:
	UFUNCTION()
	void PrimaryAttack();//일반공격
	
	UFUNCTION()
	void AttackCheck();//몬스터와 Hit되면 호출

	UFUNCTION()
	void OnPrimaryAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);//실행중인 몽타주 애니메이션이 종료되면 호출

private:
	UPROPERTY()
	ECharacterType CharacterEnumType;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* RightWeapon;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* LeftWeapon;

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* RightWeaponCollision;

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* LeftWeaponCollision;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	class UStatComponent* CurrentStat;

	UPROPERTY()
	class UPlayableAnimInstance* PlayerAnimInstance;

	UPROPERTY(VisibleAnywhere, Category = State)
	bool bIsAttacking = false;

	UPROPERTY(VisibleAnywhere, Category = State)
	bool bIsAttacked = false;

	UPROPERTY()
	int32 AttackIndex = 0;
};
