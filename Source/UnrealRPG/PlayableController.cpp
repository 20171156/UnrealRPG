// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableController.h"
#include "PlayerCharacterBase.h"
#include "PlayableAnimInstance.h"
#include "GameFramework/PlayerInput.h"
#include "CustomEnum.h"
#include "UnrealRPGGameModeBase.h"

APlayableController::APlayableController()
{

}

void APlayableController::SetupInputComponent()
{
	Super::SetupInputComponent();

	PlayerInput->AddActionMapping(FInputActionKeyMapping(("Jump"), EKeys::SpaceBar));
	PlayerInput->AddActionMapping(FInputActionKeyMapping(("Attack"), EKeys::LeftMouseButton));
	PlayerInput->AddActionMapping(FInputActionKeyMapping(("Menu"), EKeys::M));
	PlayerInput->AddActionMapping(FInputActionKeyMapping(("ZoomIn"), EKeys::MouseScrollUp));
	PlayerInput->AddActionMapping(FInputActionKeyMapping(("ZoomOut"), EKeys::MouseScrollDown));
	
	InputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &APlayableController::Jump);
	InputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &APlayableController::PrimaryAttack);
	InputComponent->BindAction(TEXT("Menu"), EInputEvent::IE_Pressed, this, &APlayableController::ChangeMenu);
	InputComponent->BindAction(TEXT("ZoomIn"), EInputEvent::IE_Pressed, this, &APlayableController::ZoomIn);
	InputComponent->BindAction(TEXT("ZoomOut"), EInputEvent::IE_Pressed, this, &APlayableController::ZoomOut);
	
	PlayerInput->AddAxisMapping(FInputAxisKeyMapping(("UpDown"), EKeys::W, 1.f));
	PlayerInput->AddAxisMapping(FInputAxisKeyMapping(("UpDown"), EKeys::S, -1.f));
	PlayerInput->AddAxisMapping(FInputAxisKeyMapping(("LeftRight"), EKeys::D, 1.f));
	PlayerInput->AddAxisMapping(FInputAxisKeyMapping(("LeftRight"), EKeys::A, -1.f));
	PlayerInput->AddAxisMapping(FInputAxisKeyMapping(("Yaw"), EKeys::MouseX, 0.6f));
	PlayerInput->AddAxisMapping(FInputAxisKeyMapping(("Pitch"), EKeys::MouseY, 0.6f));

	InputComponent->BindAxis(TEXT("UpDown"), this, &APlayableController::MoveUpDown);
	InputComponent->BindAxis(TEXT("LeftRight"), this, &APlayableController::MoveLeftRight);
	InputComponent->BindAxis(TEXT("Yaw"), this, &APlayableController::Yaw);
	InputComponent->BindAxis(TEXT("Pitch"), this, &APlayableController::Pitch);
}

void APlayableController::Jump()
{
	if (IsValid(GetCharacter()))
	{
		if (!Cast<APlayerCharacterBase>(GetCharacter())->GetDead())
		{
			Cast<APlayerCharacterBase>(GetCharacter())->Jump();
		}
	}
}

void APlayableController::PrimaryAttack()
{
	if (IsValid(GetCharacter()))
	{
		if (!Cast<APlayerCharacterBase>(GetCharacter())->GetDead())
		{
			Cast<APlayerCharacterBase>(GetCharacter())->ExecuteAnimMontage(EPlayerAnimState::ATTACKING);
		}
	}
}

void APlayableController::ZoomIn()
{

}

void APlayableController::ZoomOut()
{
}

void APlayableController::ChangeMenu()
{
	//UI TEST INPUT
	IsVisibleUI = !IsVisibleUI;
	AUnrealRPGGameModeBase* GameMode = Cast<AUnrealRPGGameModeBase>(GetWorld()->GetAuthGameMode());

	if (GameMode)
	{
		if (IsVisibleUI)
		{
			//GameMode->OnUI();
		}
		else
		{
			//GameMode->OffUI();
		}
	}
}

void APlayableController::MoveUpDown(float Value)
{
	if (IsValid(GetCharacter()))
	{
		if (!Cast<APlayerCharacterBase>(GetCharacter())->GetDead())
		{
			UpDownValue = Value;

			APawn* const MyPawn = GetPawn();
			if (MyPawn && Value != 0.f)
			{
				FRotator Rot = GetControlRotation();
				FVector Dir = FRotationMatrix(Rot).GetScaledAxis(EAxis::X);
				MyPawn->AddMovementInput(Dir, Value);
			}
		}
	}
}

void APlayableController::MoveLeftRight(float Value)
{
	if (IsValid(GetCharacter()))
	{
		if (!Cast<APlayerCharacterBase>(GetCharacter())->GetDead())
		{
			LeftRightValue = Value;

			APawn* const MyPawn = GetPawn();
			if (MyPawn && Value != 0.f)
			{
				FRotator Rot = GetControlRotation();
				FVector Dir = FRotationMatrix(Rot).GetScaledAxis(EAxis::Y);
				MyPawn->AddMovementInput(Dir, Value);
			}
		}
	}
}

void APlayableController::Yaw(float Value)
{
	if (IsValid(GetCharacter()))
	{
		if (!Cast<APlayerCharacterBase>(GetCharacter())->GetDead())
		{
			if (Value != 0.f)
			{
				AddYawInput(Value);
			}
		}
	}
}

void APlayableController::Pitch(float Value)
{
	if (IsValid(GetCharacter()))
	{
		if (!Cast<APlayerCharacterBase>(GetCharacter())->GetDead())
		{
			if (Value != 0.f)
			{
				AddPitchInput(Value);
			}
		}
	}
}
