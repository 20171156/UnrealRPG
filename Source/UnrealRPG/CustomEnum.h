#pragma once

#include "CoreMinimal.h"
#include "CustomEnum.generated.h"

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	Player UMETA(DisplayName = "Player"),
	NormalMonster UMETA(DisplayName = "NormalMonster"),
	BossMonster UMETA(DisplayName = "BossMonster"),
};

UENUM()//몬스터 상태 확인
enum class EMonsterState : uint8
{
	IDLE UMETA(DisplayName = "IDLE"),
	AROUND UMETA(DisplayName = "WALK"),
	FOLLOWPLAYER UMETA(DisplayName = "FOLLOWCHAR"),
	ATTACKING UMETA(DisplayName = "ATTACKING"),
	ATTACKED UMETA(DisplayName = "ATTACKED"),
	DEAD UMETA(DisplayName = "DEAD"),
};