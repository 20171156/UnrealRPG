// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletonCharacterBase.h"
#include "MonsterStatComponent.h"
#include "MonsterAIController.h"

ASkeletonCharacterBase::ASkeletonCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(FName("Skeleton"));

	CurrentState = EMonsterState::IDLE;

	RightWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RIGHTWEAPON"));
	LeftWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LEFTWEAPON"));
	BackWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BACKWEAPON"));
	ShieldWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SHIELDWEAPON"));

	FName RightWeaponSocket {TEXT("WeaponRight_Socket")};
	FName LeftWeaponSocket {TEXT("WeaponLeft_Socket")};
	FName BackWeaponSocket {TEXT("WeaponBack_Socket")};
	FName ShieldWeaponSocket {TEXT("Shield_Socket")};

	RightWeapon->SetupAttachment(GetMesh(), RightWeaponSocket);
	LeftWeapon->SetupAttachment(GetMesh(), LeftWeaponSocket);
	BackWeapon->SetupAttachment(GetMesh(), BackWeaponSocket);
	ShieldWeapon->SetupAttachment(GetMesh(), ShieldWeaponSocket);

	RightWeapon->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	LeftWeapon->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	BackWeapon->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	ShieldWeapon->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	
	//AI Class 셋팅
	AIControllerClass = AMonsterAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ASkeletonCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ASkeletonCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentStat->InitializeStatData(Tags[2]);//일단 추후 테스트
}

void ASkeletonCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, GetEStateAsString(CurrentState));
}

FString ASkeletonCharacterBase::GetEStateAsString(EMonsterState EnumValue)
{
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EMonsterState"), true);
	if (!enumPtr)
	{
		return FString("Invalid");
	}
	return enumPtr->GetNameStringByIndex((int32)EnumValue);
}