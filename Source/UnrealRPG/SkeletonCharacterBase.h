// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterCharacterBase.h"
#include "SkeletonCharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API ASkeletonCharacterBase : public AMonsterCharacterBase
{
	GENERATED_BODY()
		
public:
	ASkeletonCharacterBase();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FString GetEStateAsString(EMonsterState EnumValue);

private:
	UPROPERTY()
	FName LeftWeaponSocket = TEXT("WeaponLeft_Socket");

	UPROPERTY()
	FName RightWeaponSocket = TEXT("WeaponRight_Socket");

	UPROPERTY()
	FName ShieldWeaponSocket = TEXT("Shield_Socket");

	UPROPERTY()
	FName BackWeaponSocket = TEXT("WeaponBack_Socket");

};
