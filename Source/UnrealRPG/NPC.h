// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CustomStruct.h"
#include "InteractionInterface.h"
#include "NPC.generated.h"

UCLASS()
class UNREALRPG_API ANPC : public ACharacter, public IInteractionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void ExecuteInteraction(class APlayerCharacterBase* Player) override;

public:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	FName NPCName;

	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	class UWidgetComponent* InteractionWidget;
	
	UPROPERTY(EditDefaultsOnly)
	class UInteractionComponent* InteractionComponent;

	UPROPERTY()
	class UNPCDialog* NPCDialog;
};
