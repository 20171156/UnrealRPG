// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "PlayableStatComponent.h"
#include "DrawDebugHelpers.h"//디버깅용 코드

// Sets default values
APlayableCharacter::APlayableCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//오브젝트 셋팅
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	Stat = CreateDefaultSubobject<UPlayableStatComponent>(TEXT("STAT"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 300.f;
	SpringArm->SetRelativeRotation(FRotator(-38.f, 0.f, 0.f));

	//일종의 국룰 위치, 메쉬가 정상적으로 등을 보이게 하려고 위치 다시 잡았음
	GetMesh()->SetRelativeLocationAndRotation(FVector{ 0.f, 0.f, -88.f }, FRotator{ 0.f, -90.f, 0.f });

	//Default Mesh Setting
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM_Player(TEXT("SkeletalMesh'/Game/ParagonAurora/Characters/Heroes/Aurora/Meshes/Aurora.Aurora'"));

	if (SM_Player.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM_Player.Object);
	}
}

// Called when the game starts or when spawned
void APlayableCharacter::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Level : %d"), Stat->GetLevel());
	UE_LOG(LogTemp, Warning, TEXT("Experience : %d"), Stat->GetExperience());
	UE_LOG(LogTemp, Warning, TEXT("Hp : %d"), Stat->GetHp());
	UE_LOG(LogTemp, Warning, TEXT("Stamina : %d"), Stat->GetStamina());
	UE_LOG(LogTemp, Warning, TEXT("Attack : %d"), Stat->GetAttack());
}

void APlayableCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called every frame
void APlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}