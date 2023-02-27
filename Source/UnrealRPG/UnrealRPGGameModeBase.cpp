// Copyright Epic Games, Inc. All Rights Reserved.


#include "UnrealRPGGameModeBase.h"

#include "PlayerCharacterBase.h"
#include "PlayableController.h"

#include "PlayerMainWidget.h"
#include "InventoryWidget.h"
#include "GameEndWidget.h"
#include "DialogWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
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
	}

	if (GameEndWidgetClass)
	{
		GameEndWidget = CreateWidget<UGameEndWidget>(GetWorld(), GameEndWidgetClass);
	}

	if (NPCDialogWidgetClass)
	{
		NPCDialogWidget = CreateWidget<UDialogWidget>(GetWorld(), NPCDialogWidgetClass);
	}

	UWorld* world = GetWorld();
	for (const auto& Player : TActorRange<APlayerCharacterBase>(world))
	{
		if (IsValid(Player))
		{
			PlayerMainWidget->BindWidget(Player->GetStatComponent(), Player->GetInventory(), Player->GetQuestSystem());
			InventoryWidget->BindWidget(Player->GetInventory());
			break;
		}
	}
}

void AUnrealRPGGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AUnrealRPGGameModeBase::OpenGameEndWidget()
{
	GameEndWidget->AddToViewport();

	//FInputModeUIOnly InputModeData;
	////InputModeData.SetWidgetToFocus(GameEndWidget->GetCachedWidget());
	//InputModeData.SetWidgetToFocus(GameEndWidget->TakeWidget());
	//InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	//
	//PlayerControllerClass.GetDefaultObject()->SetInputMode(InputModeData);
	//PlayerControllerClass.GetDefaultObject()->bShowMouseCursor = true;

}

void AUnrealRPGGameModeBase::OpenInventory()
{
	if (!InventoryWidget->IsVisible())
	{
		InventoryWidget->AddToViewport();
	}
}

void AUnrealRPGGameModeBase::CloseInventory()
{
	InventoryWidget->RemoveFromViewport();
}

void AUnrealRPGGameModeBase::OpenDialogWidget(ACharacter* NPC)
{
	PlayerMainWidget->RemoveFromViewport();
	InventoryWidget->RemoveFromViewport();

	if (!NPCDialogWidget->IsVisible())
	{
		NPCDialogWidget->AddToViewport();
		NPCDialogWidget->BindWidget(NPC);
	}

	IsOpenDialogWidget = true;

	UpdatePlayerInteracting();
}

void AUnrealRPGGameModeBase::UpdateDialogWidget()
{
	NPCDialogWidget->UpdateDialog();
}

void AUnrealRPGGameModeBase::CloseDialogWidget(const FQuestData& QuestData)
{
	if (!PlayerMainWidget->IsVisible())
	{
		PlayerMainWidget->AddToViewport();
	}

	NPCDialogWidget->RemoveFromViewport();

	IsOpenDialogWidget = false;

	UpdatePlayerInteracting();

	UWorld* world = GetWorld();
	for (const auto& Player : TActorRange<APlayerCharacterBase>(world))
	{
		if (IsValid(Player))
		{
			Player->SetQuestData(QuestData);
			Player->SetQuestState(EPlayerQuestState::ACCEPTED);
			
			//EPlayerQuestState State = Player->GetQuestState();
			//switch (State)
			//{
			//case EPlayerQuestState::EMPTY:
			//{
			//	Player->SetQuestData(QuestData);
			//	Player->SetQuestState(EPlayerQuestState::ACCEPTED);
			//	break;
			//}
			//case EPlayerQuestState::ACCEPTED:
			//{
			//	break;
			//}
			//case EPlayerQuestState::COMPLETE:
			//{
			//	break;
			//}
			//default:
			//{
			//	break;
			//}
			//}

			break;
		}
	}
}

void AUnrealRPGGameModeBase::UpdatePlayerInteracting()
{
	UWorld* world = GetWorld();
	for (const auto& Player : TActorRange<APlayerCharacterBase>(world))
	{
		if (IsValid(Player))
		{
			Player->SetInteracting(IsOpenDialogWidget);
			break;
		}
	}
}