// Fill out your copyright notice in the Description page of Project Settings.
#pragma once 


#include "UE4MT.h"
#include "GameFramework/SaveGame.h"
#include "MTSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class UE4MT_API UMTSaveGame : public USaveGame
{
	GENERATED_BODY()
public:

    
    UPROPERTY(VisibleAnywhere, Category = Basic)
        FString PlayerName;

    UPROPERTY(VisibleAnywhere, Category = Basic)
        FString SaveSlotName;

    UPROPERTY(VisibleAnywhere, Category = Basic)
        uint32 UserIndex;

    UMTSaveGame(const FObjectInitializer& ObjectInitializer);
};


