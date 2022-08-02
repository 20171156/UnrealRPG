// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayableController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API APlayableController : public APlayerController
{
	GENERATED_BODY()

public:
	APlayableController();

public:
	virtual void SetupInputComponent() override;

	UFUNCTION()
	void Jump();

	UFUNCTION()
	void Attack();

	UFUNCTION()
	void MoveUpDown(float Value);

	UFUNCTION()
	void MoveLeftRight(float Value);

	UFUNCTION()
	void Yaw(float Value);

	
};
