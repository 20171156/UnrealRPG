// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "StatComponent.h"
#include "MonsterCharacterBase.h"
#include "PlayableAnimInstance.h"
#include "DrawDebugHelpers.h"//디버깅용 코드

// Sets default values
APlayerCharacterBase::APlayerCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//캐릭터 타입 기본 셋팅
	CharacterEnumType = ECharacterType::Player;

	//오브젝트 셋팅
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	CurrentStat = CreateDefaultSubobject<UStatComponent>(TEXT("STAT"));

	RightWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RIGHTWEAPON"));
	LeftWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LEFTWEAPON"));
	RightWeaponCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RIGHTWEAPONCOLLISION"));
	LeftWeaponCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("LEFTWEAPONCOLLISION"));

	//SpringArm->bUsePawnControlRotation = true;
	SpringArm->TargetArmLength = 300.f;
	SpringArm->SetRelativeRotation(FRotator(-38.f, 0.f, 0.f));

	//일종의 국룰 위치, 메쉬가 정상적으로 등을 보이게 하려고 위치 다시 잡았음
	GetMesh()->SetRelativeLocationAndRotation(FVector{ 0.f, 0.f, -88.f }, FRotator{ 0.f, -90.f, 0.f });

	//Default Mesh Setting
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/ParagonAurora/Characters/Heroes/Aurora/Meshes/Aurora.Aurora'"));
	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}

	FName WeaponRightSocketName{ TEXT("weapon") };
	FName WeaponLeftSocketName{ TEXT("weapon_l") };

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	RightWeapon->SetupAttachment(GetMesh(), WeaponRightSocketName);
	LeftWeapon->SetupAttachment(GetMesh(), WeaponLeftSocketName);
	RightWeaponCollision->SetupAttachment(GetMesh(), WeaponRightSocketName);
	LeftWeaponCollision->SetupAttachment(GetMesh(), WeaponLeftSocketName);

	
	Tags.Add(FName("Player"));
}

void APlayerCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PlayerAnimInstance = Cast<UPlayableAnimInstance>(GetMesh()->GetAnimInstance());
	if (PlayerAnimInstance)
	{
		PlayerAnimInstance->OnMontageEnded.AddDynamic(this, &APlayerCharacterBase::OnPrimaryAttackMontageEnded);
		PlayerAnimInstance->OnAttackHit.AddUObject(this, &APlayerCharacterBase::AttackCheck);
	}
}

// Called when the game starts or when spawned
void APlayerCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("Player Spawn Complete!"));
	UE_LOG(LogTemp, Log, TEXT("PlayerName : %s"), *CurrentStat->GetName());
	UE_LOG(LogTemp, Log, TEXT("PlayerLevel : %d"), CurrentStat->GetLevel());
	UE_LOG(LogTemp, Log, TEXT("PlayerAtk : %d"), CurrentStat->GetAtk());
	UE_LOG(LogTemp, Log, TEXT("PlayerExp : %d"), CurrentStat->GetExp());
	UE_LOG(LogTemp, Log, TEXT("PlayerHp : %d"), CurrentStat->GetHp());
	UE_LOG(LogTemp, Log, TEXT("PlayerSp : %d"), CurrentStat->GetSp());
	UE_LOG(LogTemp, Log, TEXT("PlayerMp : %d"), CurrentStat->GetMp());
}

// Called every frame
void APlayerCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacterBase::PrimaryAttack()
{
	if (GetAttacking())
	{
		return;//공격중이면 더 공격하지 않고 취소함
	}

	PlayerAnimInstance->PlayPrimaryAttackMontage();
	PlayerAnimInstance->JumpToSection(AttackIndex);
	AttackIndex = (AttackIndex + 1) % 3;

	SetAttacking(true);
}

void APlayerCharacterBase::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);

	float AttackRange = 100.f;
	float AttackRadius = 50.f;

	bool bResult = GetWorld()->SweepSingleByChannel(
		OUT HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_Pawn,
		FCollisionShape::MakeSphere(AttackRadius),
		Params);

	//FVector Vec = GetActorForwardVector() * AttackRange;
	//FVector Center = GetActorLocation() + Vec * 0.5f;
	//float HalfHeight = AttackRange * 0.5f + AttackRadius;
	//FQuat Rotation = FRotationMatrix::MakeFromZ(Vec).ToQuat();
	//FColor DrawColor;

	//if (bResult)
	//	DrawColor = FColor::Green;
	//else
	//	DrawColor = FColor::Red;

	//DrawDebugCapsule(GetWorld(), Center, HalfHeight, AttackRadius, Rotation, DrawColor, false, 2.f);

	if (bResult && HitResult.Actor.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("HitActor : %s"), *HitResult.Actor->GetName());

		FDamageEvent DamageEvent;
		HitResult.Actor->TakeDamage(CurrentStat->GetAtk(), DamageEvent, GetController(), this);
	}
}

void APlayerCharacterBase::OnPrimaryAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	SetAttacking(false);

	OnPlayerAttackEnd.Broadcast();
}
