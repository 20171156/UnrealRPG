// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "MonsterSpawnPoint.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API AMonsterSpawnPoint : public ATargetPoint
{
	GENERATED_BODY()

public:
	AMonsterSpawnPoint();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	void PlayParticleComponent();

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* ParticleComponent;

	UPROPERTY(EditAnywhere, Category = Particle, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* Particle;
};
