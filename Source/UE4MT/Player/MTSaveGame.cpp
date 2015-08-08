// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4MT.h"
#include "Player/MTSaveGame.h"


UMTSaveGame::UMTSaveGame(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    SaveSlotName = TEXT("TestSaveSlot");
    UserIndex = 0;
}

