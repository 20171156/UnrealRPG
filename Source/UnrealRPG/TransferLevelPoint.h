// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TransferLevelPoint.generated.h"

UCLASS()
class UNREALRPG_API ATransferLevelPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATransferLevelPoint();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* ParticleComponent;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere)
	FName MapName;
};
