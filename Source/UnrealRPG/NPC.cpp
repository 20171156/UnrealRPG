// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"
#include "NPCDialog.h"
#include "InteractionComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "PlayerCharacterBase.h"
#include "UnrealRPGGameModeBase.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(FName("NPC"));

	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("INTERACTION"));
	InteractionComponent->SetupAttachment(GetMesh());
	InteractionComponent->SetRelativeLocation(FVector(0.f, 0.f, 90.f));
	InteractionComponent->SetBoxExtent(FVector(200.f, 200.f, 150.f));
	InteractionComponent->SetCollisionProfileName("Interaction");

	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("INTERACTION_WIDGET"));
	InteractionWidget->SetupAttachment(GetMesh());
	InteractionWidget->SetDrawSize(FVector2D(130, 30.f));
	InteractionWidget->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
	InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
	InteractionWidget->SetCollisionProfileName("NoCollision");
}

void ANPC::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	InteractionWidget->InitWidget();
	auto HpWidget = Cast<UWidgetComponent>(InteractionWidget->GetUserWidgetObject());
	
	InteractionWidget->SetVisibility(false);
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
	//DialogText �����ϱ�
	NPCDialog = NewObject<UNPCDialog>(this, UNPCDialog::StaticClass());

	InteractionComponent->OnComponentBeginOverlap.AddDynamic(this, &ANPC::OnOverlapBegin);
	InteractionComponent->OnComponentEndOverlap.AddDynamic(this, &ANPC::OnOverlapEnd);
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANPC::ResetDialogData()
{
	NPCDialog->ResetDialogAndQuestData();
}

void ANPC::ExecuteInteraction(APlayerCharacterBase* Player)
{
	//gŰ�� ������...
	//1. Dialog Widget ���� �ű⿡ ��ȭ ������ �ѱ��
	//2. Dialog�� ��� ������ Player���� ����Ʈ ������ �ѱ��

	AUnrealRPGGameModeBase* GameMode = Cast<AUnrealRPGGameModeBase>(GetWorld()->GetAuthGameMode());

	//��Ȳ�� �´� Dialog�� Quest �����
	EPlayerQuestState State = Player->GetQuestState();
	NPCDialog->CreateNPCDialog(State);

	NPCDialogArray = NPCDialog->GetDialogData();//��Ȳ�� �°� Dialog ����
	switch (State)//����Ʈ�� ó�� ���� ���� �ޱ�
	{
	case EPlayerQuestState::EMPTY:
	{
		CombineQuest = NPCDialog->GetCombineQuestData();
		break;
	}
	case EPlayerQuestState::ACCEPTED://���� ����Ʈ�� ������
	{
		break;
	}
	case EPlayerQuestState::COMPLETE:
	{
		break;
	}
	}

	//���� Dialog�� Quest�� �����ϱ�
	GameMode->OpenDialogWidget(this);
}

void ANPC::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	InteractionWidget->SetVisibility(true);
}

void ANPC::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	InteractionWidget->SetVisibility(false);
}