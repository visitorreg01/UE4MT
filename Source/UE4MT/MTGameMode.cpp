// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4MT.h"


AMTGameMode::AMTGameMode(const class FObjectInitializer& init)
    : Super(init)
{
    /*Copied from Super
    bStartPlayersAsSpectators = false;
    bDelayedStart = false;
    bNetLoadOnClient = false;

    // One-time initialization
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickGroup = TG_PrePhysics;
    HUDClass = AHUD::StaticClass();
    MatchState = MatchState::EnteringMap;
    bPauseable = true;
    DefaultPawnClass = ADefaultPawn::StaticClass();
    PlayerControllerClass = APlayerController::StaticClass();
    SpectatorClass = ASpectatorPawn::StaticClass();
    ReplaySpectatorPlayerControllerClass = APlayerController::StaticClass();
    EngineMessageClass = UEngineMessage::StaticClass();
    GameStateClass = AGameState::StaticClass();
    CurrentID = 1;
    PlayerStateClass = APlayerState::StaticClass();
    MinRespawnDelay = 1.0f;
    InactivePlayerStateLifeSpan = 300.f;
    */

    this->DefaultPawnClass = AMTSpectatorPawn::StaticClass();
    this->PlayerControllerClass = AMTSpectatorPlayerController::StaticClass();
    this->GameStateClass = AMTGameState::StaticClass();
    this->PlayerStateClass = AMTPlayerState::StaticClass();
}




APlayerController* AMTGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const TSharedPtr<FUniqueNetId>& UniqueId, FString& ErrorMessage)
{
    APlayerController* res = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
    return res;
}

void AMTGameMode::GenericPlayerInitialization(AController* C)
{
    Super::GenericPlayerInitialization(C);

    AActor* const StartSpot = FindPlayerStart(C);
    if (StartSpot != nullptr)
    {
        // initialize and start it up
        InitStartSpot(StartSpot, C);

        AMTSpectatorPlayerController* const NewPC = Cast<AMTSpectatorPlayerController>(C);
        if (NewPC != nullptr)
        {
            NewPC->SetInitialLocationAndRotation(StartSpot->GetActorLocation(), StartSpot->GetActorRotation());
        }
    }
}


void AMTGameMode::StartNewPlayer(APlayerController* NewPlayer)
{
    Super::StartNewPlayer(NewPlayer);
}

void AMTGameMode::RestartPlayer(AController* NewPlayer)
{
    AActor* const StartSpot = FindPlayerStart(NewPlayer);
    if (StartSpot != nullptr)
    {
        // initialize and start it up
        InitStartSpot(StartSpot, NewPlayer);

        AMTSpectatorPlayerController* const NewPC = Cast<AMTSpectatorPlayerController>(NewPlayer);
        if (NewPC != nullptr)
        {
            NewPC->SetInitialLocationAndRotation(StartSpot->GetActorLocation(), StartSpot->GetActorRotation());
        }
    }
    else
    {
        //UE_LOG(LogGame, Warning, TEXT("Player start not found, failed to restart player"));
    }
}