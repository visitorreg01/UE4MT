// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4MT.h"
#include "MTPlayerPawn.h"


// Sets default values
AMTPlayerPawn::AMTPlayerPawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    
    
    Team = EMTTeamEnum::None;
}

//// Called every frame
//void AGameCharacter::Tick( float DeltaTime )
//{
//	Super::Tick( DeltaTime );
//
//}


//// Called when the game starts or when spawned
//void AMTPlayerPawn::BeginPlay()
//{
//    //SpawnDefaultController();
//	Super::BeginPlay();
//}


//void AMTPlayerPawn::PostInitProperties()
//{
//    Super::PostInitProperties();
//}

//
//virtual void PostInitializeComponents() override
//{
//   
//}
//
//void AMTPlayerPawn::SpawnDefaultController()
//{
//    Super::SpawnDefaultController();
//    Cast<AGameCharacterAIController>(Controller)->Holder = this;
//}

