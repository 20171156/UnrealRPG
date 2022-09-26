// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CustomEnum.h"
#include "MonsterCharacterBase.generated.h"

DECLARE_MULTICAST_DELEGATE(FMonsterOnAttackEnd);

UCLASS()
class UNREALRPG_API AMonsterCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonsterCharacterBase();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ChangeMonsterState(const EMonsterState& ChangeState);
	const EMonsterState& GetMonsterState() { return CurrentState; }

	void SetAttacking(bool bIsAttack) { bIsAttacking = bIsAttack; }
	bool GetAttacking() { return bIsAttacking; }


public:
	//Delgate variable
	FMonsterOnAttackEnd OnMonsterAttackEnd;

public:
	UFUNCTION()
	void PrimaryAttack();

	UFUNCTION()
	void AttackCheck();

	UFUNCTION()
	void OnPrimaryAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

protected:
	UPROPERTY(VisibleAnywhere)
	class UMonsterStatComponent* CurrentStat;

	UPROPERTY(VisibleAnywhere)
	EMonsterState CurrentState;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HpBarWidget;
	
	UPROPERTY()
	class UMonsterAnimInstance* MonsterAnimInstance;

private:
	UPROPERTY(VisibleAnywhere, Category = State)
	bool bIsAttacking = false;
	
	UPROPERTY(VisibleAnywhere, Category = State)
	bool bIsAttacked = false;

	//UPROPERTY()
	//int32 AttackIndex = 0;
};
