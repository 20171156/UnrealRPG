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
	virtual void BeginPlay() override;
};
