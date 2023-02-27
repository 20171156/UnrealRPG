// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"
#include "PlayerCharacterBase.h"
#include "NPC.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UInteractionComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UInteractionComponent::OnOverlapBegin);
	OnComponentEndOverlap.AddDynamic(this, &UInteractionComponent::OnOverlapEnd);
}

void UInteractionComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName(TEXT("Player"))))
	{
		//�÷��̾ GŰ �Է� ����
		//InteractionComp�� �����ϸ� �÷��̾�� Interaction������ Actor�� ���� ������ �Ѱ���
		Cast<APlayerCharacterBase>(OtherActor)->SetPossibleInteraction(true, GetOwner());
	}
}

void UInteractionComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag(FName(TEXT("Player"))))
	{
		//InteractionComp�� ����� Interaction ������ ������ ������ �ʱ�ȭ��Ŵ
		Cast<APlayerCharacterBase>(OtherActor)->SetPossibleInteraction(false);
	}
}