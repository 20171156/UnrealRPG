// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CustomEnum.h"
#include "MonsterCharacterBase.generated.h"

DECLARE_MULTICAST_DELEGATE(FMonsterOnAttackEnd);
DECLARE_MULTICAST_DELEGATE(FMonsterOnAttackedStart);
DECLARE_MULTICAST_DELEGATE(FMonsterOnAttackedEnd);
//DECLARE_MULTICAST_DELEGATE(FMonsterIsDelete);

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
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	bool GetDead() { return bIsDead; }
	bool GetMonsterArcherType() { return bIsArchery; }

	void SetState(const EMonsterAnimState State);

	const EMonsterAnimState& GetCurrentAnimState() { return CurrentAnimState; }
	const EMonsterAnimState& GetPreviousAnimState() { return PreviousAnimState; }

	UFUNCTION()
	void CharacterDestroy();

public:
	UFUNCTION()
	void ChangeCollisionProfile(bool IsStart);

	UFUNCTION()
	void OnWeaponOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnWeaponOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void ExecuteAnimMontage(const EMonsterAnimState MonsterAnimState);

	UFUNCTION()
	void OnAnimMontageStarted(UAnimMontage* Montage);

	UFUNCTION()
	void OnAnimMontageEnded(UAnimMontage* Montage, bool bInterrupted);

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
	//FMonsterIsDelete OnMonsterIsDelete;

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
	class UStaticMeshComponent* WeaponComponent;//공격가능한 무기 CollisionCheck

	UPROPERTY()
	class UWeaponAnimInstance* WeaponAnimInstance;

	UPROPERTY()
	bool bIsAttacking = false;

	UPROPERTY()
	bool bIsAttacked = false;
	
	UPROPERTY()
	bool bIsDead = false;

	UPROPERTY()
	bool bIsArchery = false;
};
