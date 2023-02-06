// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "BaseLevelActor.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API ABaseLevelActor : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	ABaseLevelActor();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void MonsterIsDead(AActor* DestroyedActor);
	
	UFUNCTION()
	void SpawnMonster();

private:
	TArray<class AMonsterCharacterBase*> SpawnMonsterArray;
	TArray<class ATargetPoint*> SpawnPointArray;

	int32 SpawnMonsterNum;
};