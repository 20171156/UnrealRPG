// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableStatComponent.h"
#include "DatatableInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UPlayableStatComponent::UPlayableStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	// ...
}

// Called when the game starts
void UPlayableStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UPlayableStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	UE_LOG(LogTemp, Warning, TEXT("PlayableStatComponent Loading Complete"));

	SetLevel(1);//Default Level
}

//Call this function LevelUp
void UPlayableStatComponent::SetLevel(int32 NewLevel)
{
	auto DataInstance = Cast<UDatatableInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (DataInstance)
	{
		auto StatData = DataInstance->GetPlayableStatData(NewLevel);
		if (StatData)
		{
			//NextLevel MaxStat Initialize
			this->Level = StatData->Level;
			this->MaxHp = StatData->Hp;
			this->MaxStamina = StatData->Stamina;
			this->Attack = StatData->Attack;
			this->MaxExperience = StatData->Experience;

			//CurrentStat Initialize
			SetCurrentHp(MaxHp);
			SetCurrentStamina(MaxStamina);
			SetCurrentExperience(0, true);
		}
	}
}

void UPlayableStatComponent::SetCurrentHp(int32 NewHp)
{
	CurrentHp += NewHp;

	if (CurrentHp <= 0)
	{
		//眠饶 Death贸府
		CurrentHp = 0;
	}
}

void UPlayableStatComponent::SetCurrentStamina(int32 NewStamina)
{
	CurrentStamina += NewStamina;

	if (CurrentStamina <= 0)
	{
		//眠饶 Death贸府
		CurrentStamina = 0;
	}
}

void UPlayableStatComponent::SetCurrentExperience(int32 NewExperience, bool isInit/* = false*/)
{
	if (isInit)
	{
		CurrentExperience = 0;
		return;
	}

	CurrentExperience += NewExperience;

	if (CurrentExperience <= 0)
	{
		CurrentExperience = 0;
	}
}

