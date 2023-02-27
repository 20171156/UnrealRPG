// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogWidget.h"
#include "Components/TextBlock.h"
#include "UnrealRPGGameModeBase.h"

UDialogWidget::UDialogWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UDialogWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UDialogWidget::BindWidget(FString NPCName, TArray<FString> NPCDialogArray)
{
	if (NPCDialogArray.Num() == 0)
	{
		return;
	}

	DialogArray = NPCDialogArray;

	if (nullptr != NPCNameText)
	{
		NPCNameText->SetText(FText::FromString(NPCName));
	}

	DialogCount = 0;

	UpdateDialog();
}

void UDialogWidget::UpdateDialog()
{	
	//Dialog 모두 업데이트 했으면 위젯 닫기
	if (DialogCount == DialogArray.Num())
	{
		CloseDialog();

		return;
	}

	if (DialogArray.IsValidIndex(DialogCount))
	{
		NPCDialogText->SetText(FText::FromString(DialogArray[DialogCount]));
		++DialogCount;
	}
}

void UDialogWidget::CloseDialog()
{
	AUnrealRPGGameModeBase* GameMode = Cast<AUnrealRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	GameMode->CloseDialogWidget();
}
