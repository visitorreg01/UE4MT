#pragma once

#include "UE4MT.h"

#include "EMTTeamEnum.generated.h"

UENUM(BlueprintType)
enum class EMTTeamEnum : uint8
{
    None    UMETA(DisplayName = "None"),
    Red     UMETA(DisplayName = "Red"),
    Blue    UMETA(DisplayName = "Blue"),
};