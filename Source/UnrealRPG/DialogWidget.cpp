// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogWidget.h"
#include "NPC.h"
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

void UDialogWidget::BindWidget(ACharacter* NPCClass/*ANPC* NPCClass*/)
{
	//대화 시작시에 호출될 함수
	if (IsValid(NPCClass))
	{
		NPC = Cast<ANPC>(NPCClass);

		if (nullptr != NPCName)
		{
			NPCName->SetText(FText::FromName(NPC->Tags[1]));
		}

		DialogArray = NPC->GetNPCDialog();
		if (DialogArray.Num() == 0)
		{
			return;
		}

		DialogCount = 0;
		UpdateDialog();
	}
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
		NPCDialog->SetText(FText::FromString(DialogArray[DialogCount]));
		++DialogCount;
	}
}

void UDialogWidget::CloseDialog()
{
	//NPCDialog 데이터 초기화
	NPC->ResetDialogData();

	//NPC의 퀘스트 데이터를 체크해서 넘기기
	FQuestData QuestData = NPC->GetQuestData();

	AUnrealRPGGameModeBase* GameMode = Cast<AUnrealRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	GameMode->CloseDialogWidget(QuestData);
}
