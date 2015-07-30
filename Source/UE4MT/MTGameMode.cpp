// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4MT.h"
#include "MTGameMode.h"


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

    this->DefaultPawnClass = AMTPlayerPawn::StaticClass();
    this->PlayerControllerClass = AMTPlayerPawnController::StaticClass();
    this->GameStateClass = AMTGameState::StaticClass();
    this->PlayerStateClass = AMTPlayerState::StaticClass();
}

