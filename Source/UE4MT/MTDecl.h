#pragma once
#include "UE4MT.h"

class MTUtils
{
public:
    static float GetMoveToAcceptanceRadiusSquared(AMTGameCharacter* charA, AMTGameCharacter* charB)
    {
        float r1 = charA->GetCapsuleComponent()->GetScaledCapsuleRadius();
        float r2 = charB->GetCapsuleComponent()->GetScaledCapsuleRadius();
        float r = r1 + r2;
        return r * r;
    }
    static float GetMoveToAcceptanceRadius(AMTGameCharacter* charA, AMTGameCharacter* charB)
    {
        float r1 = charA->GetCapsuleComponent()->GetScaledCapsuleRadius();
        float r2 = charB->GetCapsuleComponent()->GetScaledCapsuleRadius();
        return r1 + r2;
    }

};