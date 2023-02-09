// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomStruct.h"
#include "StatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FPlayerLevelChanged);
DECLARE_MULTICAST_DELEGATE(FPlayerHpChanged);
DECLARE_MULTICAST_DELEGATE(FPlayerMpChanged);
DECLARE_MULTICAST_DELEGATE(FPlayerSpChanged);
DECLARE_MULTICAST_DELEGATE(FPlayerExpChanged);
DECLARE_MULTICAST_DELEGATE(FPlayerHpZero);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALRPG_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatComponent();

protected:
	// Called when the game starts
	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;

private:
	void SetLevel(const int32& NewLevel);

public:
	const FString& GetName() { return CharacterName; }
	const int32& GetLevel() { return Level; }
	const int32& GetAtk() { return Atk; }
	const int32& GetMaxExp() { return MaxExp; }
	const int32& GetMaxHp() { return MaxHp; }
	const int32& GetMaxSp() { return MaxSp; }
	const int32& GetMaxMp() { return MaxMp; }

	const int32& GetHp() { return CurrentHp; }
	const int32& GetSp() { return CurrentSp; }
	const int32& GetMp() { return CurrentMp; }
	const int32& GetExp() { return CurrentExp; }

	const float GetHpRatio() { return CurrentHp / (float)MaxHp; }
	const float GetSpRatio() { return CurrentSp / (float)MaxSp; }
	const float GetMpRatio() { return CurrentMp / (float)MaxMp; }
	const float GetExpRatio() { return CurrentExp / (float)MaxExp; }

	void SetCurrentExp(const int32& NewExperience);

private:
	void SetName(const FString& NewName);
	void SetCurrentHp(const int32& NewHp);
	void SetCurrentSp(const int32& NewStamina);
	void SetCurrentMp(const int32& NewMana);

public:
	void OnAttacked(const int32& DamageAmount);

public:
	FPlayerLevelChanged PlayerLevelChanged;
	FPlayerHpChanged PlayerHpChanged;
	FPlayerMpChanged PlayerMpChanged;
	FPlayerSpChanged PlayerSpChanged;
	FPlayerExpChanged PlayerExpChanged;
	FPlayerHpZero PlayerHpZero;

private:
	//고정 데이터
	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	FString CharacterName;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Level;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Atk;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 MaxExp;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 MaxHp;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 MaxSp;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 MaxMp;


	//변화 데이터
	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 CurrentExp;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 CurrentHp;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 CurrentSp;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 CurrentMp;
};
