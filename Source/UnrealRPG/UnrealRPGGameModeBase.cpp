// Copyright Epic Games, Inc. All Rights Reserved.


#include "UnrealRPGGameModeBase.h"

#include "PlayerCharacterBase.h"
#include "PlayableController.h"

#include "PlayerMainWidget.h"
#include "InventoryWidget.h"
#include "GameEndWidget.h"
#include "DialogWidget.h"

#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
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

void AUnrealRPGGameModeBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

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
	APlayerCharacterBase* Player = Cast<APlayerCharacterBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (IsValid(Player))
	{
		PlayerMainWidget->BindWidget(Player->GetStatComponent(), Player->GetInventory(), Player->GetQuestSystem());
		InventoryWidget->BindWidget(Player->GetInventory());
	}

	//새 맵 로드했을 때 넣을 데이터
	auto DataInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (IsValid(DataInstance))
	{
		DataInstance->LoadPlayerData(Player);
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

void AUnrealRPGGameModeBase::OpenDialogWidget(FString NPCName, TArray<FString> NPCDialogArray)
{
	PlayerMainWidget->RemoveFromViewport();
	InventoryWidget->RemoveFromViewport();

	if (!NPCDialogWidget->IsVisible())
	{
		NPCDialogWidget->AddToViewport();
		NPCDialogWidget->BindWidget(NPCName, NPCDialogArray);
	}

	IsOpenDialogWidget = true;

	UpdatePlayerInteracting();
}

void AUnrealRPGGameModeBase::UpdateDialogWidget()
{
	NPCDialogWidget->UpdateDialog();
}

void AUnrealRPGGameModeBase::CloseDialogWidget()
{
	if (!PlayerMainWidget->IsVisible())
	{
		PlayerMainWidget->AddToViewport();
	}

	NPCDialogWidget->RemoveFromViewport();

	IsOpenDialogWidget = false;

	UpdatePlayerInteracting();
}

//플레이어가 인터랙팅 중에는 키입력을 막아야 함
void AUnrealRPGGameModeBase::UpdatePlayerInteracting()
{
	UWorld* world = GetWorld();
	APlayerCharacterBase* Player = Cast<APlayerCharacterBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	if (IsValid(Player))
	{
		Player->SetInteracting(IsOpenDialogWidget);
	}
}