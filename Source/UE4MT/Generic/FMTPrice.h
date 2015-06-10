#pragma once
#include "ObjectBase.h"
#include "FMTPrice.generated.h"


USTRUCT(BlueprintType, Atomic)
struct FMTPrice
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Coins;
   
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Gold;
};
