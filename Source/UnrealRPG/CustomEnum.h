#pragma once

#include "CoreMinimal.h"
#include "CustomEnum.generated.h"

UENUM()
enum class ECharacterType : uint8
{
	Player UMETA(DisplayName = "Player"),
	NormalMonster UMETA(DisplayName = "NormalMonster"),
	BossMonster UMETA(DisplayName = "BossMonster"),
};