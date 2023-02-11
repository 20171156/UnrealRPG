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
	void PrimaryAttack();
	
	UFUNCTION()
	void ZoomIn();

	UFUNCTION()
	void ZoomOut();

	UFUNCTION()//Test
	void ChangeMenu();

	UFUNCTION()
	void MoveUpDown(float Value);

	UFUNCTION()
	void MoveLeftRight(float Value);

	UFUNCTION()
	void Yaw(float Value);

	UFUNCTION()
	void Pitch(float Value);

	UFUNCTION()
	void UseItem1();

	UFUNCTION()
	void UseItem2();

public:
	UPROPERTY()
	float UpDownValue = 0.f;

	UPROPERTY()
	float LeftRightValue = 0.f;

private:
	UPROPERTY()
	bool IsVisibleUI = false;

	UPROPERTY()
	int32 AttackIndex = 0;
};
