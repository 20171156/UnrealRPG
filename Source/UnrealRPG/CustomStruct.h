#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CustomEnum.h"
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

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//ETestEnum test;
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//class AMonsterSpawnPoint* testPoint;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TSoftObjectPtr<class AMonsterSpawnPoint> testSoftPtr;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TSoftClassPtr<class AMonsterSpawnPoint> testClassSoftPtr;
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

USTRUCT()
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPlayerStatData ItemValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* InventoryIconTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<class AItem> ItemClass;
};

USTRUCT()
struct FDialogData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString NPCDialog;

};

USTRUCT()
struct FQuestData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString QuestDialog;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MINCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MAXCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString QuestItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 QuestRequireCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 GainExp;
};
