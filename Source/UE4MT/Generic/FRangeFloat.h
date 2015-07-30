#pragma once

#include "ObjectBase.h"
#include "FRangeFloat.generated.h"


USTRUCT(BlueprintType, Atomic)
struct FRangeFloat
{
public:
    GENERATED_USTRUCT_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float From;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float To;
};
