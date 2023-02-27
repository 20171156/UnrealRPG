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
		//플레이어가 G키 입력 가능
		//InteractionComp와 접촉하면 플레이어에게 Interaction가능한 Actor에 대한 정보를 넘겨줌
		Cast<APlayerCharacterBase>(OtherActor)->SetPossibleInteraction(true, GetOwner());
	}
}

void UInteractionComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag(FName(TEXT("Player"))))
	{
		//InteractionComp를 벗어나면 Interaction 가능한 데이터 정보를 초기화시킴
		Cast<APlayerCharacterBase>(OtherActor)->SetPossibleInteraction(false);
	}
}