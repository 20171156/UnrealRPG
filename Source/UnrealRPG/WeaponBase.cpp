// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollision"));
	Root = CreateDefaultSubobject<USphereComponent>(TEXT("Root"));
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	RootComponent = Root;
	SkeletalMesh->SetupAttachment(Root);
	StaticMesh->SetupAttachment(Root);

	Root->SetCollisionProfileName(TEXT("NoCollision"));
}

void AWeaponBase::PostInitializeComponents()
{
 	Super::PostInitializeComponents();
	
	if (nullptr != StaticMesh)
	{
		StaticMesh->BodyInstance.bNotifyRigidBodyCollision = true;//Weapon은 HitEvent가 발동해야 한다
		StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBase::OnOverlapBegin);
		StaticMesh->OnComponentEndOverlap.AddDynamic(this, &AWeaponBase::OnOverlapEnd);
	}
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this || OtherActor->ActorHasTag(FName(TEXT("Monster"))))
	{
		return;
	}

	int32 a = 0;
	int32 b = a;
}

void AWeaponBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == this || OtherActor->ActorHasTag(FName(TEXT("Monster"))))
	{
		return;
	}

	int32 a = 0;
	int32 b = a;
}

