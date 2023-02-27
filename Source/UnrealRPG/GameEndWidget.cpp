// Fill out your copyright notice in the Description page of Project Settings.


#include "GameEndWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

UGameEndWidget::UGameEndWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UGameEndWidget::NativeConstruct()
{
	//AddToViewport�� ȣ��, Add�� ������ �Ҹ�
	Super::NativeConstruct();

	if (IsValid(QuitButton))
	{
		QuitButton->OnClicked.AddDynamic(this, &UGameEndWidget::OnClickedButton);
	}
}

void UGameEndWidget::NativeOnInitialized()
{
	//���� ���� �� �ѹ� ȣ��, ������ �������� ȣ��
	Super::NativeOnInitialized();
}

void UGameEndWidget::OnClickedButton()
{
	UKismetSystemLibrary::QuitGame(this, 0, EQuitPreference::Quit, false);
}
