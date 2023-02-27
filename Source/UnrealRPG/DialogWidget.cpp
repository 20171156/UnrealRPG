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
	//��ȭ ���۽ÿ� ȣ��� �Լ�
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
	//Dialog ��� ������Ʈ ������ ���� �ݱ�
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
	//NPCDialog ������ �ʱ�ȭ
	NPC->ResetDialogData();

	//NPC�� ����Ʈ �����͸� üũ�ؼ� �ѱ��
	FQuestData QuestData = NPC->GetQuestData();

	AUnrealRPGGameModeBase* GameMode = Cast<AUnrealRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	GameMode->CloseDialogWidget(QuestData);
}
