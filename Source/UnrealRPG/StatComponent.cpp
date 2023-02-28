// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UStatComponent::UStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	// ...
}

void UStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	//SetLevel(1);//초기 레벨 1로 셋팅(추후 저장기능 만들면 수정)
	PlayerLevelChanged.Broadcast();
	PlayerHpChanged.Broadcast();
	PlayerMpChanged.Broadcast();
	PlayerSpChanged.Broadcast();
	PlayerExpChanged.Broadcast();

	UE_LOG(LogTemp, Warning, TEXT("PlayableStatComponent Loading Complete"));
}

// Called when the game starts
void UStatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UStatComponent::SetLevel(const int32& NewLevel)
{
	auto DataInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (DataInstance)
	{
		auto PlayerStat = DataInstance->GetPlayerData(NewLevel);

		if (PlayerStat)
		{
			this->Level = PlayerStat->Level;
			this->Atk = PlayerStat->Atk;

			this->MaxExp = PlayerStat->Exp;
			this->CurrentHp = this->MaxHp = PlayerStat->Hp;
			this->CurrentSp = this->MaxSp = PlayerStat->Sp;
			this->CurrentMp = this->MaxMp = PlayerStat->Mp;
		}
	}
}

FPlayerStatData UStatComponent::GetPlayerStat()
{
	//Level로 로드해서 Max데이터를 계산, 나머지 Current 데이터만 저장
	FPlayerStatData PlayerStat;
	PlayerStat.Level = Level;
	PlayerStat.Atk = Atk;
	PlayerStat.Hp = CurrentHp;
	PlayerStat.Sp = CurrentSp;
	PlayerStat.Mp = CurrentMp;
	PlayerStat.Exp = CurrentExp;

	return PlayerStat;
}

void UStatComponent::InputPlayerStat(FPlayerStatData CurrentPlayerStat)
{
	SetLevel(CurrentPlayerStat.Level);//레벨 대입해서 Max데이터를 초기화

	CurrentHp = CurrentPlayerStat.Hp;
	CurrentSp = CurrentPlayerStat.Sp;
	CurrentMp = CurrentPlayerStat.Mp;
	CurrentExp = CurrentPlayerStat.Exp;

	PlayerLevelChanged.Broadcast();
	PlayerHpChanged.Broadcast();
	PlayerMpChanged.Broadcast();
	PlayerSpChanged.Broadcast();
	PlayerExpChanged.Broadcast();
}

void UStatComponent::SetName(const FString& NewName)
{
	this->CharacterName = NewName;
}

void UStatComponent::SetCurrentHp(const int32& NewHp)
{
	CurrentHp += NewHp;

	if (CurrentHp <= 0)
	{
		CurrentHp = 0;
		PlayerHpZero.Broadcast();
	}

	PlayerHpChanged.Broadcast();
}

void UStatComponent::SetCurrentSp(const int32& NewStamina)
{
	CurrentSp += NewStamina;

	if (CurrentSp <= 0)
	{
		CurrentSp = 0;
	}

	PlayerSpChanged.Broadcast();
}

void UStatComponent::SetCurrentMp(const int32& NewMana)
{
	CurrentMp += NewMana;

	if (CurrentMp <= 0)
	{
		CurrentMp = 0;
	}

	PlayerMpChanged.Broadcast();
}

void UStatComponent::SetCurrentExp(const int32& NewExperience)
{
	CurrentExp += NewExperience;

	if (CurrentExp <= 0)
	{
		CurrentExp = 0;
	}

	if (CurrentExp >= MaxExp)
	{
		CurrentExp -= MaxExp;
		SetLevel(++Level);//오로지 레벨1만 오를때 처리가능

		PlayerLevelChanged.Broadcast();
	}

	PlayerExpChanged.Broadcast();
}

void UStatComponent::OnAttacked(const int32& DamageAmount)
{
	//SetCurrentHp(CurrentHp - DamageAmount);
	SetCurrentHp(-DamageAmount);
}
