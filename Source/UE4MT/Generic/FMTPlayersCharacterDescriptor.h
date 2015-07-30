#pragma once


#include "UE4MT.h"
#include "Actors/GameCharacter/MTGameCharacter.h"

#include "FMTPlayersCharacterDescriptor.generated.h"


USTRUCT(BlueprintType, Atomic)
struct FMTPlayersCharacterDescriptor
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Character Class to be spawned."))
    TSubclassOf<AMTGameCharacter> CharacterClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Count of character spawned automatically."))
    int32 CountAvailable;
   
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Maximum count of characters of this Class Player can have."))
    int32 CountMax;

};
