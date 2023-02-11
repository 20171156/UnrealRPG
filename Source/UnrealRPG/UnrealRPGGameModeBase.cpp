// Copyright Epic Games, Inc. All Rights Reserved.


#include "UnrealRPGGameModeBase.h"
#include "PlayerCharacterBase.h"
#include "PlayableController.h"
#include "PlayerMainWidget.h"
#include "InventoryWidget.h"
#include "Runtime/Engine/Public/EngineUtils.h"

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

	if (PlayerMainWidgetClass)
	{
		PlayerMainWidget = CreateWidget<UPlayerMainWidget>(GetWorld(), PlayerMainWidgetClass);
		PlayerMainWidget->AddToViewport();
	}

	if (InventoryWidgetClass)
	{
		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
		InventoryWidget->AddToViewport();
	}


	UWorld* world = GetWorld();
	for (const auto& Player : TActorRange<APlayerCharacterBase>(world))
	{
		if (IsValid(Player))
		{
			PlayerMainWidget->BindWidget(Player->GetStatComponent());
			InventoryWidget->BindWidget(Player->GetInventory());

			break;
		}
	}
}

void AUnrealRPGGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
