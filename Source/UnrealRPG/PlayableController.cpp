// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableController.h"
#include "PlayableCharacter.h"

APlayableController::APlayableController()
{
}

void APlayableController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &APlayableController::Jump);
	InputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &APlayableController::Attack);

	InputComponent->BindAxis(TEXT("UpDown"), this, &APlayableController::MoveUpDown);
	InputComponent->BindAxis(TEXT("LeftRight"), this, &APlayableController::MoveLeftRight);
	InputComponent->BindAxis(TEXT("Yaw"), this, &APlayableController::Yaw);
}

void APlayableController::Jump()
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		Cast<APlayableCharacter>(MyPawn)->Jump();
	}
}

void APlayableController::Attack()
{
}

void APlayableController::MoveUpDown(float Value)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn && Value != 0.f)
	{
		FRotator Rot = GetControlRotation();
		FVector Dir = FRotationMatrix(Rot).GetScaledAxis(EAxis::X);
		MyPawn->AddMovementInput(Dir, Value);
	}
}

void APlayableController::MoveLeftRight(float Value)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn && Value != 0.f)
	{
		FRotator Rot = GetControlRotation();
		FVector Dir = FRotationMatrix(Rot).GetScaledAxis(EAxis::Y);
		MyPawn->AddMovementInput(Dir, Value);
	}
}

void APlayableController::Yaw(float Value)
{
	if (Value != 0.f)
	{
		AddYawInput(Value);
	}
}