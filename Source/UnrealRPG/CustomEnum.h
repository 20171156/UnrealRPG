#pragma once

#include "CoreMinimal.h"
#include "CustomEnum.generated.h"

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	Player			UMETA(DisplayName = "Player"),
	NormalMonster	UMETA(DisplayName = "NormalMonster"),
	BossMonster		UMETA(DisplayName = "BossMonster"),
};

UENUM(BlueprintType)
enum class EMonsterAnimState : uint8
{
	PEACE			UMETA(DisplayName = "PEACE"),
	CHASE			UMETA(DisplayName = "CHASE"),
	ATTACKING		UMETA(DisplayName = "ATTACKING"),
	ATTACKED		UMETA(DisplayName = "ATTACKED"),//외부 이벤트 타입
	DEAD			UMETA(DisplayName = "DEAD"),
};

UENUM(BlueprintType)
enum class EPlayerAnimState : uint8
{
	PEACE			UMETA(DisplayName = "PEACE"),
	CHASE			UMETA(DisplayName = "CHASE"),
	ATTACKING		UMETA(DisplayName = "ATTACKING"),
	ATTACKED		UMETA(DisplayName = "ATTACKED"),//외부 이벤트 타입
	DEAD			UMETA(DisplayName = "DEAD"),
};

UENUM(BlueprintType)
enum class ECharacterStatType : uint8
{
	LEVEL			UMETA(DisplayName = "LEVEL"),
	HP				UMETA(DisplayName = "HP"),
	SP				UMETA(DisplayName = "SP"),
	MP				UMETA(DisplayName = "MP"),
	ATK				UMETA(DisplayName = "ATK"),
	EXP				UMETA(DisplayName = "EXP"),
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	CONSUMABLE		UMETA(DisplayName = "CONSUMABLE"),
	EQUIPMENT		UMETA(DisplayName = "EQUIPMENT"),
	NOTCOMSUMABLE	UMETA(DisplayName = "NOTCOMSUMABLE"),
};


UENUM(BlueprintType)
enum class EPlayerQuestState : uint8
{
	EMPTY			UMETA(DisplayName = "EMPTY"),
	ACCEPTED		UMETA(DisplayName = "ACCEPTED"),
	COMPLETE		UMETA(DisplayName = "COMPLETE"),
};