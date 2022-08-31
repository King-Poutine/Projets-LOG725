#pragma once

#include "CoreMinimal.h"
#include "HackathonPlayerControllerState.generated.h"

UENUM(BlueprintType)
enum class EHackathonPlayerControllerState : uint8
{
    Default = 0 UMETA(DisplayName = "Default"),
    Place_Platform = 1 UMETA(DisplayName = "Place Platform"),
    Delete_Platform = 2 UMETA(DisplayName = "Delete Platform")
};