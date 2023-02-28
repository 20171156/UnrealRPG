// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CustomEnum.h"
#include "CustomStruct.h"
#include "PlayerCharacterBase.generated.h"

//DECLARE_MULTICAST_DELEGATE(FPlayerOnAttackEnd);

UCLASS()
class UNREALRPG_API APlayerCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacterBase();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void CharacterDestroy();

	UFUNCTION()
	class UStatComponent* GetStatComponent() { return CurrentStat; }
	
	UFUNCTION()
	class UInventory* GetInventory() { return Inventory; }

	UFUNCTION()
	class UPlayerQuestSystem* GetQuestSystem() { return QuestSystem; }

	bool GetDead() { return bIsDead; }
	
	void SetInventoryState(bool OpenInventory) { IsOpenInventory = OpenInventory; }
	bool GetInventoryState() { return IsOpenInventory; }

	UFUNCTION()
	void SetPossibleInteraction(bool PossibleInteraction, AActor* OverlapActor = nullptr);
	bool GetPossibleInteraction() { return IsPossibleInteraction; }

	void SetInteracting(bool Interacting) { IsInteracting = Interacting; }
	bool GetInteracting() { return IsInteracting; }

	UFUNCTION()
	void InteractActor();

	void SetQuestData(FQuestData QuestData);
	FQuestData GetQuestData();
	void ClearQuest();

	void SetQuestState(EPlayerQuestState State) { QuestState = State; }
	EPlayerQuestState GetQuestState() { return QuestState; }

	void SetPlayerStat(FPlayerStatData PlayerStat);
	FPlayerStatData GetPlayerStat();

	void SetInventoryItemList(TMap<FName, int32> InventoryItems);
	TMap<FName, int32> GetInventoryItemList();

public:
	UFUNCTION()
	void ChangeCollisionProfile(bool bAbleOverlap);

	UFUNCTION()
	void OnWeaponOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnWeaponOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void ExecuteAnimMontage(const EPlayerAnimState AnimState);

	UFUNCTION()
	void OnAnimMontageStarted(UAnimMontage* Montage);

	UFUNCTION()
	void OnAnimMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void PickUpItem(FName ItemName);

	UFUNCTION()
	void UseItem(FName ItemName);

private:
	UFUNCTION()
	void PlayerHpZero();

public:
	//Delgate variable
	//FPlayerOnAttackEnd OnPlayerAttackEnd;

private:
	UPROPERTY(EditDefaultsOnly)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* Camera;

	UPROPERTY()
	class UStatComponent* CurrentStat;//저장필요

	UPROPERTY()
	class UPlayableAnimInstance* PlayerAnimInstance;

	UPROPERTY()
	class UCapsuleComponent* WeaponCollisionComponent;

	UPROPERTY()
	class UInventory* Inventory;//저장필요

	UPROPERTY()
	class UPlayerQuestSystem* QuestSystem;//저장필요

	UPROPERTY()
	bool bIsAttacking = false;

	UPROPERTY()
	bool bIsAttacked = false;

	UPROPERTY()
	bool bIsDead = false;

	UPROPERTY()
	bool IsOpenInventory = false;

	//Interaction 관련 Property
	UPROPERTY()
	bool IsPossibleInteraction = false;

	UPROPERTY()
	AActor* InteractionActor;

	UPROPERTY()
	bool IsInteracting = false;

	//Quest 관련 Property
	UPROPERTY()
	EPlayerQuestState QuestState = EPlayerQuestState::EMPTY;//저장필요

	UPROPERTY()
	int32 TestAttackCount = 0;
};