// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterCharacterBase.h"
#include "MonsterStatComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "MonsterHpWidget.h"
#include "MonsterAnimInstance.h"
#include "MonsterAIController.h"

// Sets default values
AMonsterCharacterBase::AMonsterCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//캐릭터 타입 기본 셋팅
	CharacterEnumType = ECharacterType::NormalMonster;

	//오브젝트 셋팅
	CurrentStat = CreateDefaultSubobject<UMonsterStatComponent>(TEXT("STAT"));
	
	RightWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RIGHTWEAPON"));
	BackWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BACKWEAPON"));
	RightWeaponCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RIGHTWEAPONCOLLISION"));
	BackWeaponCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BACKWEAPONCOLLISION"));
	
	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HP_WIDGET"));

	//Default Character Mesh Setting
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/SkeletonArmy/Characters/Warlord/SK_SkeletonWarlord.SK_SkeletonWarlord'"));
	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}

	FName WeaponRightSocketName {TEXT("WeaponRight_Socket")};
	FName WeaponBackSocketName {TEXT("WeapnBack_Socket")};

	RightWeapon->SetupAttachment(GetMesh(), WeaponRightSocketName);
	BackWeapon->SetupAttachment(GetMesh(), WeaponBackSocketName);
	RightWeaponCollision->SetupAttachment(GetMesh(), WeaponRightSocketName);
	BackWeaponCollision->SetupAttachment(GetMesh(), WeaponBackSocketName);
	HpBar->SetupAttachment(GetMesh());

	HpBar->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
	HpBar->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<UUserWidget> UW(TEXT("WidgetBlueprint'/Game/UI/WBP_MonsterHpWidget.WBP_MonsterHpWidget_C'"));

	if (UW.Succeeded())
	{
		HpBar->SetWidgetClass(UW.Class);
		HpBar->SetDrawSize(FVector2D(200.f, 50.f));
	}

	Tags.Add(FName("Monster"));

	//AI Class 셋팅
	AIControllerClass = AMonsterAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AMonsterCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	HpBar->InitWidget();
	auto HpWidget = Cast<UMonsterHpWidget>(HpBar->GetUserWidgetObject());
	if (HpWidget)
	{
		HpWidget->BindHp(CurrentStat);
	}

	MonsterAnimInstance = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	if (MonsterAnimInstance)
	{
		//MonsterAnimInstance->OnMontageEnded.AddDynamic(this, &AMonsterCharacterBase::OnPrimaryAttackMontageEnded);
		//MonsterAnimInstance->OnAttackHit.AddUObject(this, &APlayerCharacterBase::AttackCheck);
	}
}

// Called when the game starts or when spawned
void AMonsterCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("Monster Spawn Complete!"));
	UE_LOG(LogTemp, Log, TEXT("MonsterName : %s"), *CurrentStat->GetMonsterName().ToString());
	UE_LOG(LogTemp, Log, TEXT("MonsterLevel : %d"), CurrentStat->GetLevel());
	UE_LOG(LogTemp, Log, TEXT("MonsterAtk : %d"), CurrentStat->GetAtk());
	UE_LOG(LogTemp, Log, TEXT("MonsterExp : %d"), CurrentStat->GetExp());
	UE_LOG(LogTemp, Log, TEXT("MonsterHp : %d"), CurrentStat->GetHp());
	UE_LOG(LogTemp, Log, TEXT("MonsterSp : %d"), CurrentStat->GetSp());
	UE_LOG(LogTemp, Log, TEXT("MonsterMp : %d"), CurrentStat->GetMp());

}

// Called every frame
void AMonsterCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonsterCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}