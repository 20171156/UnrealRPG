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

	UFUNCTION()
	void SpawnArrow();

	UFUNCTION()
	void FireMagic();

	UFUNCTION()
	void FireArrow();

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY()
	class AProjectile* Projectile;
};
