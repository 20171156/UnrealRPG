#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CustomStruct.generated.h"


USTRUCT()
struct FPlayerStatData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Hp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Sp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Mp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Atk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Path;
};

USTRUCT()
struct FMonsterStatData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Hp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Sp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Mp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Atk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Path;
};