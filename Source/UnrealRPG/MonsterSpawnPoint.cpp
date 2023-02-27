// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawnPoint.h"
#include "Particles/ParticleSystemComponent.h"
//#include "Kismet/GameplayStatics.h"

AMonsterSpawnPoint::AMonsterSpawnPoint()
{
	PrimaryActorTick.bCanEverTick = true;

	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));

	ParticleComponent->SetupAttachment(RootComponent);
	//ParticleComponent->bAutoActivate = true;
}

void AMonsterSpawnPoint::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMonsterSpawnPoint::BeginPlay()
{
	Super::BeginPlay();

}

void AMonsterSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonsterSpawnPoint::PlayParticleComponent()
{
	ParticleComponent->Activate(true);

	FTimerHandle DestroyHandle;
	float WaitTime = 2.f;
	GetWorld()->GetTimerManager().SetTimer(DestroyHandle, FTimerDelegate::CreateLambda([&]()
		{
			ParticleComponent->Deactivate();
			GetWorldTimerManager().ClearTimer(DestroyHandle);
		}), WaitTime, false);
}
