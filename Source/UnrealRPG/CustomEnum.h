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