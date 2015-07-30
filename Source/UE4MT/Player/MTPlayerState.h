// Fill out your copyright notice in the Description page of Project Settings.
#pragma once 


#include "UE4MT.h"
#include "GameFramework/PlayerState.h"
#include "MTPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class UE4MT_API AMTPlayerState : public APlayerState
{
	GENERATED_BODY()
public:

    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Player's Name"), Category = "Player Data")
    FString DisplayName;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Player's Level"), Category = "Player Data")
    int32 Level;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Player's eXPerience"), Category = "Player Data")
    int32 Xp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Player's Mana"), Category = "Player Data")
    int32 Mana;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Available characters"), Category = "Player Data")
    TArray<FMTPlayersCharacterDescriptor> Characters;
};


