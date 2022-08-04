// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayableStatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALRPG_API UPlayableStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayableStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:
	void SetLevel(int32 NewLevel);
	void SetCurrentHp(int32 NewHp);
	void SetCurrentStamina(int32 NewStamina);
	void SetCurrentExperience(int32 NewExperience, bool isInit = false);

	const int32& GetLevel() { return Level; }
	const int32& GetExperience() { return CurrentExperience; }
	const int32& GetHp() { return CurrentHp; }
	const int32& GetStamina() { return CurrentStamina; }
	const int32& GetAttack() { return Attack; }

	const int32& GetMaxExperience() { return MaxExperience; }
	const int32& GetMaxHp() { return MaxHp; }
	const int32& GetMaxStamina() { return MaxStamina; }

private:
	//이 스탯들 모두 데이터테이블로 관리하는 데이터
	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 MaxExperience;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 MaxHp;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 MaxStamina;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Attack;

	//계속 변화하는 데이터
	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 CurrentExperience;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 CurrentHp;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 CurrentStamina;
};
