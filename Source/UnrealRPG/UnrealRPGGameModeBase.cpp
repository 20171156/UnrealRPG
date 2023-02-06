// Copyright Epic Games, Inc. All Rights Reserved.


#include "UnrealRPGGameModeBase.h"
#include "PlayerCharacterBase.h"
#include "PlayableController.h"
#include "Blueprint/UserWidget.h"

AUnrealRPGGameModeBase::AUnrealRPGGameModeBase()
{
	DefaultPawnClass = APlayerCharacterBase::StaticClass();

	static ConstructorHelpers::FClassFinder<ACharacter> BP_PlayableCharacter(TEXT("Blueprint'/Game/Blueprints/BP_PlayerCharacter.BP_PlayerCharacter_c'"));

	if (BP_PlayableCharacter.Succeeded())
	{
		DefaultPawnClass = BP_PlayableCharacter.Class;
	}

	PlayerControllerClass = APlayableController::StaticClass();
}

void AUnrealRPGGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (Widget)
	{
		Menu = CreateWidget<UUserWidget>(GetWorld(), Widget);
	}
}

void AUnrealRPGGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AUnrealRPGGameModeBase::OnUI()
{
	if (Menu)
	{
		Menu->AddToViewport();
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	}
}

void AUnrealRPGGameModeBase::OffUI()
{
	if (Menu)
	{
		Menu->RemoveFromViewport();
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	}
}
