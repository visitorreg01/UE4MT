// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4MT.h"
#include "GameCharacter.h"


// Sets default values
AGameCharacter::AGameCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

//// Called every frame
//void AGameCharacter::Tick( float DeltaTime )
//{
//	Super::Tick( DeltaTime );
//
//}


// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


void AGameCharacter::PostInitProperties()
{
    Super::PostInitProperties();
    this->Speed = 1.0f;
    this->Health = 100.0f;
    this->Price = { 10.0f, { 10.0f, 1.0f } };
}