// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "AIController.h"
#include "GameCharacterAIController.generated.h"
class AGameCharacter;
/**
 * 
 */
UCLASS()
class UE4MT_API AGameCharacterAIController : public AAIController
{
    GENERATED_BODY()

private:
  

    AGameCharacter* FindEnemy();
    void UpdateState();
public:
    AGameCharacter* Holder = nullptr;

    //// Called when the game starts or when spawned
    //virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaSeconds) override;
	
	
	
};
