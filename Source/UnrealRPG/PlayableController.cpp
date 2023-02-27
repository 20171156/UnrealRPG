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
	PlayerInput->AddActionMapping(FInputActionKeyMapping(("ZoomIn"), EKeys::MouseScrollUp));
	PlayerInput->AddActionMapping(FInputActionKeyMapping(("ZoomOut"), EKeys::MouseScrollDown));

	PlayerInput->AddActionMapping(FInputActionKeyMapping(("UseItem1"), EKeys::One));
	PlayerInput->AddActionMapping(FInputActionKeyMapping(("UseItem2"), EKeys::Two));

	PlayerInput->AddActionMapping(FInputActionKeyMapping(("Inventory"), EKeys::I));

	PlayerInput->AddActionMapping(FInputActionKeyMapping(("Interaction"), EKeys::G));
	
	InputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &APlayableController::Jump);
	InputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &APlayableController::PrimaryAttack);
	InputComponent->BindAction(TEXT("ZoomIn"), EInputEvent::IE_Pressed, this, &APlayableController::ZoomIn);
	InputComponent->BindAction(TEXT("ZoomOut"), EInputEvent::IE_Pressed, this, &APlayableController::ZoomOut);

	InputComponent->BindAction(TEXT("UseItem1"), EInputEvent::IE_Pressed, this, &APlayableController::UseItem1);
	InputComponent->BindAction(TEXT("UseItem2"), EInputEvent::IE_Pressed, this, &APlayableController::UseItem2);

	InputComponent->BindAction(TEXT("Inventory"), EInputEvent::IE_Pressed, this, &APlayableController::CheckOpenInventory);

	InputComponent->BindAction(TEXT("Interaction"), EInputEvent::IE_Pressed, this, &APlayableController::ExecuteInteraction);
	
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
			if (!Cast<APlayerCharacterBase>(GetCharacter())->GetInteracting())
			{
				Cast<APlayerCharacterBase>(GetCharacter())->Jump();
			}
		}
	}
}

void APlayableController::PrimaryAttack()
{
	if (IsValid(GetCharacter()))
	{
		if (!Cast<APlayerCharacterBase>(GetCharacter())->GetDead())
		{
			if (!Cast<APlayerCharacterBase>(GetCharacter())->GetInteracting())
			{
				Cast<APlayerCharacterBase>(GetCharacter())->ExecuteAnimMontage(EPlayerAnimState::ATTACKING);
			}
		}
	}
}

void APlayableController::ZoomIn()
{

}

void APlayableController::ZoomOut()
{
}

void APlayableController::MoveUpDown(float Value)
{
	if (IsValid(GetCharacter()))
	{
		if (!Cast<APlayerCharacterBase>(GetCharacter())->GetDead())
		{
			if (!Cast<APlayerCharacterBase>(GetCharacter())->GetInteracting())
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
}

void APlayableController::MoveLeftRight(float Value)
{
	if (IsValid(GetCharacter()))
	{
		if (!Cast<APlayerCharacterBase>(GetCharacter())->GetDead())
		{
			if (!Cast<APlayerCharacterBase>(GetCharacter())->GetInteracting())
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
}

void APlayableController::Yaw(float Value)
{
	if (IsValid(GetCharacter()))
	{
		if (!Cast<APlayerCharacterBase>(GetCharacter())->GetDead())
		{
			if (!Cast<APlayerCharacterBase>(GetCharacter())->GetInteracting())
			{
				if (Value != 0.f)
				{
					AddYawInput(Value);
				}
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
			if (!Cast<APlayerCharacterBase>(GetCharacter())->GetInteracting())
			{
				if (Value != 0.f)
				{
					AddPitchInput(Value);
				}
			}
		}
	}
}

void APlayableController::UseItem1()
{
	if (IsValid(GetCharacter()))
	{
		if (!Cast<APlayerCharacterBase>(GetCharacter())->GetInteracting())
		{
			Cast<APlayerCharacterBase>(GetCharacter())->UseItem(FName("HPPotion"));
		}
	}
}

void APlayableController::UseItem2()
{
	if (IsValid(GetCharacter()))
	{
		if (!Cast<APlayerCharacterBase>(GetCharacter())->GetInteracting())
		{
			Cast<APlayerCharacterBase>(GetCharacter())->UseItem(FName("MPPotion"));
		}
	}
}

void APlayableController::CheckOpenInventory()
{
	AUnrealRPGGameModeBase* GameMode = Cast<AUnrealRPGGameModeBase>(GetWorld()->GetAuthGameMode());

	if (IsValid(GetCharacter()))
	{
		if (!Cast<APlayerCharacterBase>(GetCharacter())->GetInventoryState())
		{
			GameMode->OpenInventory();
			Cast<APlayerCharacterBase>(GetCharacter())->SetInventoryState(true);
		}
		else
		{
			GameMode->CloseInventory();
			Cast<APlayerCharacterBase>(GetCharacter())->SetInventoryState(false);
		}
	}
}

void APlayableController::ExecuteInteraction()
{
	AUnrealRPGGameModeBase* GameMode = Cast<AUnrealRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	
	//DialogWidget이 열려있는 상태라면 대화가 끝나기 전까지 대화만 업데이트한다(일단은 대화 업데이트 직속으로...)
	if (GameMode->CheckOpenDialogWidget())
	{
		GameMode->UpdateDialogWidget();
	}
	else//그게 아니라면 Interaction을 시작한다
	{
		if (IsValid(GetCharacter()))
		{
			APlayerCharacterBase* MainPlayer = Cast<APlayerCharacterBase>(GetCharacter());
			if (MainPlayer->GetPossibleInteraction())
			{
				MainPlayer->InteractActor();
			}
		}
	}
}