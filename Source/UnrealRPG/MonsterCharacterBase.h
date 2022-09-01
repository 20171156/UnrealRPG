// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CustomEnum.h"
#include "MonsterCharacterBase.generated.h"

UENUM()//몬스터 상태 확인
enum class MONSTERSTATE : uint8
{
	SPAWN UMETA(DisplayName = "SPAWN"),
	WALK UMETA(DisplayName = "WALK"),
	FOLLOWCHAR UMETA(DisplayName = "FOLLOWCHAR"),
	ATTACK UMETA(DisplayName = "ATTACK"),
	RETURN_SPAWNPOINT UMETA(DisplayName = "RETURNSPAWNPOINT"),
};

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

	void SetAttacking(bool bIsAttack) { bIsAttacking = bIsAttack; }
	bool GetAttacking() { return bIsAttacking; }

private:
	UPROPERTY(VisibleAnywhere)
	class UMonsterStatComponent* CurrentStat;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* RightWeapon;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* BackWeapon;

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* RightWeaponCollision;

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* BackWeaponCollision;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HpBar;

	UPROPERTY(VisibleAnywhere, Category = State)
	bool bIsAttacking = false;

	UPROPERTY(VisibleAnywhere, Category = State)
	bool bIsAttacked = false;

	UPROPERTY()
	ECharacterType CharacterEnumType;

	UPROPERTY()
	class UMonsterAnimInstance* MonsterAnimInstance;
};
