// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "CustomEnum.h"
#include "MonsterCharacterBase.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	//Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));

	RootComponent = SceneComponent;
	MeshComponent->SetupAttachment(RootComponent);
	ParticleComponent->SetupAttachment(RootComponent);

	ProjectileMovementComponent->SetUpdatedComponent(SceneComponent);
	ProjectileMovementComponent->InitialSpeed = 1000.f;
	ProjectileMovementComponent->MaxSpeed = 3000.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;

	InitialLifeSpan = 2.0f;

	MeshComponent->SetCollisionProfileName("Projectile");
}

void AProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
	MeshComponent->OnComponentEndOverlap.AddDynamic(this, &AProjectile::OnOverlapEnd);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName(TEXT("Player"))))
	{
		FDamageEvent DamageEvent;
		int32 Atk = Cast<AMonsterCharacterBase>(GetOwner())->GetCurrentStat(ECharacterStatType::ATK);
		OtherActor->TakeDamage(Atk, DamageEvent, Cast<AMonsterCharacterBase>(GetOwner())->GetController(), this);
		
		Destroy();
	}
}

void AProjectile::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AProjectile::SetSpeed(int32 Speed)
{
	ProjectileMovementComponent->InitialSpeed = Speed;
}

