// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacterBase.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitialLifeSpan = 10.f;//10초 후에는 사라짐

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
}

void AItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnOverlapBegin);
	MeshComponent->OnComponentEndOverlap.AddDynamic(this, &AItem::OnOverlapEnd);

	MeshComponent->SetCollisionProfileName("Item");
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetMassOverrideInKg(NAME_None, 100);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItem::InitializeItemName(FName ItemData)
{
	ItemName = ItemData;
}

void AItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName(TEXT("Player"))))
	{
		Cast<APlayerCharacterBase>(OtherActor)->PickUpItem(ItemName);

		Destroy();
	}
}

void AItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

