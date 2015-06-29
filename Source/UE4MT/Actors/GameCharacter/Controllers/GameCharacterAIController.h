// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "AIController.h"
#include "GameCharacterAIController.generated.h"

/**
 * 
 */
UCLASS()
class UE4MT_API AGameCharacterAIController : public AAIController
{
    GENERATED_BODY()
public:
        // Called every frame
        virtual void Tick(float DeltaSeconds) override;
	
	
	
};
