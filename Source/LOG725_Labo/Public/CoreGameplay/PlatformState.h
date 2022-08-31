#pragma once

#include "CoreMinimal.h"
#include "PlatformState.generated.h"

UENUM(BlueprintType)
enum class EPlatformState : uint8
{
    Default = 0 UMETA(DisplayName = "Default"),
    Ghost = 1 UMETA(DisplayName = "Ghost"),
    Ghost_Invalid = 2 UMETA(DisplayName = "Ghost Invalid")
};