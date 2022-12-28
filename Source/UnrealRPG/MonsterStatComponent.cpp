// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterStatComponent.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UMonsterStatComponent::UMonsterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	// ...
}

void UMonsterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	//���� �̸� �������� ������ ��
	//InitializeStatData(FName(TEXT("SkeletonWarlord")));
}

// Called when the game starts
void UMonsterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UMonsterStatComponent::InitializeStatData(const FName& MonsterName)
{
	//���Ͱ� ������ �� �� �Լ��� ȣ���ϰ� ���ȵ����� �ʱ�ȭ
	auto DataInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (DataInstance)
	{
		auto MonsterStat = DataInstance->GetMonsterData(MonsterName);

		if (MonsterStat)
		{
			this->CharacterName = MonsterStat->CharacterName;
			this->Level = MonsterStat->Level;
			this->Atk = MonsterStat->Atk;
			this->Exp = MonsterStat->Exp;
			this->MaxHp = MonsterStat->Hp;
			this->MaxSp = MonsterStat->Sp;
			this->MaxMp = MonsterStat->Mp;
			
			SetCurrentHp(MaxHp);
			SetCurrentSp(MaxSp);
			SetCurrentMp(MaxMp);
		}
	}
}

void UMonsterStatComponent::SetCurrentHp(const int32& NewHp)
{
	CurrentHp = NewHp;

	if (CurrentHp <= 0)//Deathó��
	{
		CurrentHp = 0;
		MonsterHpZero.Broadcast();
	}

	MonsterHpChanged.Broadcast();
}

void UMonsterStatComponent::SetCurrentSp(const int32& NewStamina)
{
	CurrentSp = NewStamina;

	if (CurrentSp <= 0)
	{
		CurrentSp = 0;
	}
}

void UMonsterStatComponent::SetCurrentMp(const int32& NewMana)
{
	CurrentMp = NewMana;

	if (CurrentMp <= 0)
	{
		CurrentMp = 0;
	}
}

void UMonsterStatComponent::OnAttacked(const int32& DamageAmount)
{
	SetCurrentHp(CurrentHp - DamageAmount);
}