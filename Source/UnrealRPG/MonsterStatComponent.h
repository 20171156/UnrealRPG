// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomStruct.h"
#include "MonsterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FMonsterHpChanged);
DECLARE_MULTICAST_DELEGATE(FMonsterHpZero);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALRPG_API UMonsterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMonsterStatComponent();

protected:
	// Called when the game starts
	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;

public:	
	void InitializeStatData(const FName& MonsterName);

	const FName& GetMonsterName() { return CharacterName; }
	const int32& GetLevel() { return Level; }
	const int32& GetAtk() { return Atk; }
	const int32& GetExp() { return Exp; }
	
	const int32& GetMaxHp() { return MaxHp; }
	const int32& GetMaxSp() { return MaxSp; }
	const int32& GetMaxMp() { return MaxMp; }

	const int32& GetHp() { return CurrentHp; }
	const int32& GetSp() { return CurrentSp; }
	const int32& GetMp() { return CurrentMp; }

	const float GetHpRatio() { return CurrentHp / (float)MaxHp; }

private:
	void SetCurrentHp(const int32& NewHp);
	void SetCurrentSp(const int32& NewStamina);
	void SetCurrentMp(const int32& NewMana);

public:
	void OnAttacked(const int32& DamageAmount);

public:
	FMonsterHpChanged MonsterHpChanged;
	FMonsterHpZero MonsterHpZero;

private:
	//고정 데이터
	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	FName CharacterName;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Level;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Atk;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Exp;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 MaxHp;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 MaxSp;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 MaxMp;

	//변화 데이터
	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 CurrentHp;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 CurrentSp;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 CurrentMp;
};
