// Fill out your copyright notice in the Description page of Project Settings.
#include "UE4MT.h"


void AMTPlayerState::BeginPlay()
{
    UMTSaveGame* LoadGameInstance = Cast<UMTSaveGame>(UGameplayStatics::CreateSaveGameObject(UMTSaveGame::StaticClass()));
    LoadGameInstance = Cast<UMTSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
    if (LoadGameInstance)
    {
        FString PlayerNameToDisplay = LoadGameInstance->PlayerName;
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, PlayerNameToDisplay);
        }
    }
}

void AMTPlayerState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    UMTSaveGame* SaveGameInstance = Cast<UMTSaveGame>(UGameplayStatics::CreateSaveGameObject(UMTSaveGame::StaticClass()));
    SaveGameInstance->PlayerName = this->PlayerName;
    UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
}


