// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4MT.h"
#include "GameCharacter.h"


// Sets default values
AGameCharacter::AGameCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    
    AIControllerClass = AGameCharacterAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    


    Team = EMTTeamEnum::None;
}

//// Called every frame
//void AMTGameCharacter::Tick( float DeltaTime )
//{
//	Super::Tick( DeltaTime );
//
//}


// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
    SpawnDefaultController();

	Super::BeginPlay();



}


void AGameCharacter::PostInitProperties()
{
    this->Speed = 1.0f;
    this->Health = 100.0f;
    this->Price = { 10.0f, { 10.0f, 1.0f } };
    Super::PostInitProperties();


}

//
//virtual void PostInitializeComponents() override
//{
//   
//}

void AGameCharacter::SpawnDefaultController()
{
    Super::SpawnDefaultController();
    //Cast<AGameCharacterAIController>(Controller)->Holder = this;
}

