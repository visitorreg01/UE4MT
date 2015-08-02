// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UE4MT.h"
#include "GameFramework/GameState.h"
#include "MTGameState.generated.h"

/**
 * 
 */
UCLASS()
class UE4MT_API AMTGameState : public AGameState
{
	GENERATED_BODY()

public:
    /** World bounds for mini map & camera movement. */
    FBox WorldBounds;

    /** Mini map camera component. */
    TWeakObjectPtr<AMTMiniMapCapture> MiniMapCamera;
};
