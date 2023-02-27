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
	
	//DialogText 생성하기
	NPCDialog = NewObject<UNPCDialog>(this, UNPCDialog::StaticClass());

	if (Tags.IsValidIndex(1))
	{
		NPCName = Tags[1];
	}

	InteractionComponent->OnComponentBeginOverlap.AddDynamic(this, &ANPC::OnOverlapBegin);
	InteractionComponent->OnComponentEndOverlap.AddDynamic(this, &ANPC::OnOverlapEnd);
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANPC::ExecuteInteraction(APlayerCharacterBase* Player)
{
	//g키를 누르면...
	//1. Dialog Widget 열고 거기에 대화 데이터 넘기기
	//2. Dialog가 모두 끝나면 Player에게 퀘스트 데이터 넘기기

	AUnrealRPGGameModeBase* GameMode = Cast<AUnrealRPGGameModeBase>(GetWorld()->GetAuthGameMode());

	//상황에 맞는 Dialog와 Quest 만들기
	EPlayerQuestState State = Player->GetQuestState();
	NPCDialog->CreateNPCDialog(State, Tags[1]);

	//만든 Dialog를 DialogWidget에 전달
	TArray<FString> NPCDialogArray = NPCDialog->GetDialogData();
	if (Tags.IsValidIndex(1))
	{
		GameMode->OpenDialogWidget(Tags[1].ToString(), NPCDialogArray);
	}

	//QuestData는 Player에 전달(단, 이미 퀘스트를 받은 상태라면 전달할 필요 없음)
	if (Player->GetQuestState() == EPlayerQuestState::EMPTY)
	{
		FQuestData CombineQuest = NPCDialog->GetCombineQuestData();
		Player->SetQuestData(CombineQuest);
		Player->SetQuestState(EPlayerQuestState::ACCEPTED);
	}

	//그리고 Dialog 데이터는 초기화
	NPCDialog->ResetDialogAndQuestData();
}

void ANPC::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	InteractionWidget->SetVisibility(true);
}

void ANPC::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	InteractionWidget->SetVisibility(false);
}