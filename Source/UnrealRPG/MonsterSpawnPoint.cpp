// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawnPoint.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BillboardComponent.h"
#include "Kismet/GameplayStatics.h"

AMonsterSpawnPoint::AMonsterSpawnPoint()
{
	PrimaryActorTick.bCanEverTick = true;

	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));

	ParticleComponent->SetupAttachment(Cast<USceneComponent>(GetSpriteComponent()));
	ParticleComponent->bAutoActivate = false;
	//ParticleComponent->ActivateSystem(true);
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
	auto test = UGameplayStatics::SpawnEmitterAttached(Particle, GetSpriteComponent(), TEXT("None"), GetActorLocation(), FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, true);

}
