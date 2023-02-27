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
	//AddToViewport에 호출, Add될 때마다 불림
	Super::NativeConstruct();

	if (IsValid(QuitButton))
	{
		QuitButton->OnClicked.AddDynamic(this, &UGameEndWidget::OnClickedButton);
	}
}

void UGameEndWidget::NativeOnInitialized()
{
	//위젯 생성 시 한번 호출, 에디터 편집에도 호출
	Super::NativeOnInitialized();
}

void UGameEndWidget::OnClickedButton()
{
	UKismetSystemLibrary::QuitGame(this, 0, EQuitPreference::Quit, false);
}
