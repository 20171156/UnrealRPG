// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
//#include "PlayableStatComponent.h"
#include "DrawDebugHelpers.h"//������ �ڵ�

// Sets default values
APlayableCharacter::APlayableCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//�����ڴ� ���尡 ������ �����Ǳ� ���� ȣ��ȴ�.
	//�׷��Ƿ� �� ������Ʈ���� ������ �� �� �ִ� �ൿ�� ����. �ٸ� ������Ʈ�� ���͸� �����ϰų�, ��������� �ҷ����� ����.

	//������Ʈ ����
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("PlayableSpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayableCamera"));
	//PlayerStat = CreateDefaultSubobject<UPlayableStatComponent>(TEXT("PlayableSTAT"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 300.f;
	SpringArm->SetRelativeRotation(FRotator(-38.f, 0.f, 0.f));

	//������ ���� ��ġ, �޽��� ���������� ���� ���̰� �Ϸ��� ��ġ �ٽ� �����
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