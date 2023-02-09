// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletonCharacterBase.h"
#include "MonsterAnimInstance.h"
#include "MonsterStatComponent.h"
#include "MonsterAIController.h"
#include "Projectile.h"

ASkeletonCharacterBase::ASkeletonCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	//AI Class Setting
	AIControllerClass = AMonsterAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ASkeletonCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//if (ActorHasTag(TEXT("SkeletonArcher")))
	//{
	//	FActorSpawnParameters SpawnParams;
	//	FRotator Rotator = GetMesh()->GetSocketRotation(TEXT("WeaponRight_Socket"));
	//	FVector Location = GetMesh()->GetSocketLocation(TEXT("WeaponRight_Socket"));
	//	SpawnParams.Owner = this;
	//	Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotator, SpawnParams);
	//	if (Projectile)
	//	{
	//		//Projectile->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), "WeaponRight_Socket");
	//		
	//		Projectile->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "WeaponRight_Socket");

	//	}
	//}
}

void ASkeletonCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentStat->InitializeStatData(Tags[1]);//무조건 추후 수정해야함

	UE_LOG(LogTemp, Log, TEXT("Monster Spawn Complete!"));
	UE_LOG(LogTemp, Log, TEXT("MonsterName : %s"), *CurrentStat->GetMonsterName());
	UE_LOG(LogTemp, Log, TEXT("MonsterLevel : %d"), CurrentStat->GetLevel());
	UE_LOG(LogTemp, Log, TEXT("MonsterAtk : %d"), CurrentStat->GetAtk());
	UE_LOG(LogTemp, Log, TEXT("MonsterExp : %d"), CurrentStat->GetExp());
	UE_LOG(LogTemp, Log, TEXT("MonsterHp : %d"), CurrentStat->GetHp());
	UE_LOG(LogTemp, Log, TEXT("MonsterSp : %d"), CurrentStat->GetSp());
	UE_LOG(LogTemp, Log, TEXT("MonsterMp : %d"), CurrentStat->GetMp());
}

void ASkeletonCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASkeletonCharacterBase::SpawnArrow()
{
	if (ActorHasTag(TEXT("SkeletonArcher")))
	{
		//auto test = StaticLoadClass(AActor::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Weapon/Monster/test.test_c'"));

		FActorSpawnParameters SpawnParams;
		FRotator Rotator = GetMesh()->GetSocketRotation(TEXT("WeaponRight_Socket"));
		FVector Location = GetMesh()->GetSocketLocation(TEXT("WeaponRight_Socket"));
		SpawnParams.Owner = this;
		//auto test1 = GetWorld()->SpawnActor<AActor>(test, Location, Rotator, SpawnParams);
		//if (test1)
		//{
		//	test1->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "WeaponRight_Socket");
		//	test1->SetActorRelativeLocation(FVector{ -5.1f, 5.39f, 1.07f });
		//	test1->SetActorRelativeRotation(FRotator{ -137.789f, -22.12f, 163.889f });
		//	test1->SetRelativeLocationAndRotation(FVector{ 0.f, 0.f, -88.f }, FRotator{ 0.f, -90.f, 0.f });
		//}
		
		Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotator, SpawnParams);
		if (Projectile)
		{
			Projectile->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "WeaponRight_Socket");
			Projectile->SetActorRelativeLocation(FVector{ -5.1f, 5.39f, 1.07f });
			Projectile->SetActorRelativeRotation(FRotator{ -137.789f, -22.12f, 163.889f });
			//baserotation을 무시하고 함?
		}
	}
}

void ASkeletonCharacterBase::FireMagic()
{
	auto FireOffset = GetComponentsByTag(UStaticMeshComponent::StaticClass(), FName{ TEXT("ProjectileType") });

	for (const auto& actor : FireOffset)
	{
		if (!IsValid(actor))
		{
			return;
		}
		
		FActorSpawnParameters SpawnParams;
		FRotator Rotator = Cast<UStaticMeshComponent>(actor)->GetSocketRotation(TEXT("FireProjectileSocket"));
		FVector Location = Cast<UStaticMeshComponent>(actor)->GetSocketLocation(TEXT("FireProjectileSocket"));
		SpawnParams.Owner = this;
		Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotator, SpawnParams);
		if (Projectile)
		{
			FVector FireDirection = GetActorRotation().Vector();
			Projectile->FireInDirection(FireDirection);
		}

		break;
	}
}

void ASkeletonCharacterBase::FireArrow()
{
	FVector FireDirection = GetActorRotation().Vector();
	//Projectile->FireInDirection(FireDirection);
}

//FString ASkeletonCharacterBase::GetEStateAsString(EMonsterState EnumValue)
//{
//	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EMonsterState"), true);
//	if (!enumPtr)
//	{
//		return FString("Invalid");
//	}
//	return enumPtr->GetNameStringByIndex((int32)EnumValue);
//}