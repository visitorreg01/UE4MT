#pragma once

#include "UE4MT.h"
#include "Generic/FMTPrice.h"
#include "FUnitPrice.generated.h"


USTRUCT(BlueprintType, Atomic)
struct FUnitPrice
{
    GENERATED_USTRUCT_BODY()

    //Seconds
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Time;
    
    //Game money
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FMTPrice Cost;
};
