// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "MTGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UE4MT_API AMTGameMode : public AGameMode
{
    GENERATED_BODY()
public:

    AMTGameMode(const class FObjectInitializer& init);


    virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const TSharedPtr<FUniqueNetId>& UniqueId, FString& ErrorMessage) override;
 
    /**
    * handles all player initialization that is shared between the travel methods
    * (i.e. called from both PostLogin() and HandleSeamlessTravelPlayer())
    */
    virtual void GenericPlayerInitialization(AController* C) override;

    /** start match, or let player enter, immediately */
    virtual void StartNewPlayer(APlayerController* NewPlayer) override;


protected:

    
	
};
