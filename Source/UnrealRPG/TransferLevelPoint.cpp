// Fill out your copyright notice in the Description page of Project Settings.


#include "TransferLevelPoint.h"
#include "PlayerCharacterBase.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"

// Sets default values
ATransferLevelPoint::ATransferLevelPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BOXCOLLISION"));
	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	
	BoxCollision->SetupAttachment(RootComponent);
	ParticleComponent->SetupAttachment(BoxCollision);
	
	BoxCollision->SetRelativeLocation(FVector(0.f, 0.f, 90.f));
	BoxCollision->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	BoxCollision->SetCollisionProfileName("Interaction");

}

void ATransferLevelPoint::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (BoxCollision)
	{
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ATransferLevelPoint::OnOverlapBegin);
		BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ATransferLevelPoint::OnOverlapEnd);
	}
}

// Called when the game starts or when spawned
void ATransferLevelPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATransferLevelPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATransferLevelPoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacterBase* Player = Cast<APlayerCharacterBase>(OtherActor);
	if (IsValid(Player))
	{
		if (MapName != FName{})
		{
			auto DataInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
			DataInstance->SavePlayerData(Player);
			UGameplayStatics::OpenLevel(this, MapName);
		}
	}
}

void ATransferLevelPoint::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}
