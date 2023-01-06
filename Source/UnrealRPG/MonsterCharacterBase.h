// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CustomEnum.h"
#include "MonsterCharacterBase.generated.h"

DECLARE_MULTICAST_DELEGATE(FMonsterOnAttackEnd);
DECLARE_MULTICAST_DELEGATE(FMonsterOnAttackedStart);
DECLARE_MULTICAST_DELEGATE(FMonsterOnAttackedEnd);
DECLARE_MULTICAST_DELEGATE(FMonsterOnDying);

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
	virtual void Tick(float DeltaTime) override;

//GET-SET Function
public:
	void IsAttacking(bool bableAttacking_) { bableAttacking = bableAttacking_; }
	bool GetDead() { return bIsDead; }
	bool GetAttacked() { return bIsAttacked; }
	bool GetMonsterArcherType() { return bIsArchery; }
	void SetState(const EMonsterAnimState State);

	const EMonsterAnimState& GetCurrentAnimState() { return CurrentAnimState; }
	const EMonsterAnimState& GetPreviousAnimState() { return PreviousAnimState; }

public:
	UFUNCTION()
	void ChangeCollisionProfile();

	UFUNCTION()
	void ExecuteAnimMontage(const EMonsterAnimState MonsterAnimState);

	UFUNCTION()
	void OnAnimMontageStarted(UAnimMontage* Montage);

	UFUNCTION()
	void OnAnimMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	UFUNCTION()
	void PlayWeaponAnimation(FName SectionName);

	UFUNCTION()
	void StopWeaponAnimation();

	UFUNCTION()
	void MonsterHpZero();


public:
	//Delgate variable
	FMonsterOnAttackEnd OnMonsterAttackEnd;
	FMonsterOnAttackedStart OnMonsterAttackedStart;
	FMonsterOnAttackedEnd OnMonsterAttackedEnd;
	FMonsterOnDying OnMonsterDying;

protected:
	UPROPERTY()
	EMonsterAnimState CurrentAnimState = EMonsterAnimState::PEACE;

	UPROPERTY()
	EMonsterAnimState PreviousAnimState = EMonsterAnimState::PEACE;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	class UWidgetComponent* HpBarWidget;

	UPROPERTY()
	class UMonsterStatComponent* CurrentStat;

	UPROPERTY()
	class UMonsterAnimInstance* MonsterAnimInstance;

	UPROPERTY()
	class UWeaponAnimInstance* WeaponAnimInstance;

	UPROPERTY()
	bool bableAttacking = false;//공격가능한 타이밍체크하는 변수

	UPROPERTY()
	bool bIsDead = false;

	UPROPERTY()
	bool bIsAttacked = false;

	UPROPERTY()
	bool bIsArchery = false;
};
