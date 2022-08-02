// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "DatatableInstance.generated.h"

USTRUCT()
struct FPlayableCharacterStatData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Hp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Experience;
};

/**
 * 
 */
UCLASS()
class UNREALRPG_API UDatatableInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UDatatableInstance();

	UFUNCTION()
	const FPlayableCharacterStatData& GetPlayableStatData(int32 Level);

private:
	UPROPERTY()
	class UDataTable* PlayableStat;

	
	
};
