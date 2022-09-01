#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CustomStruct.generated.h"

//USTRUCT()
//struct FCustomStruct : public FTableRowBase
//{
//	GENERATED_USTRUCT_BODY()
//};

USTRUCT()
struct FCharacterStatData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName CharacterName;

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
};