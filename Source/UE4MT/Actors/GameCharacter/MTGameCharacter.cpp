// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4MT.h"
#include "MTGameCharacter.h"


// Sets default values
AMTGameCharacter::AMTGameCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    
    AIControllerClass = AGameCharacterAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    

    State = CharacterStateEnum::None;
    Team = EMTTeamEnum::None;
}

//// Called every frame
//void AMTGameCharacter::Tick( float DeltaTime )
//{
//	Super::Tick( DeltaTime );
//
//}


// Called when the game starts or when spawned
void AMTGameCharacter::BeginPlay()
{
    SpawnDefaultController();
    State = CharacterStateEnum::Idle;
	Super::BeginPlay();



}


void AMTGameCharacter::PostInitProperties()
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

void AMTGameCharacter::SpawnDefaultController()
{
    Super::SpawnDefaultController();
    Cast<AGameCharacterAIController>(Controller)->Holder = this;
}

float AMTGameCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
    float res = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    this->Health -= res;
    /*if (this->Health <= 0)
    {
        this->Destroy();
    }*/

    return res;
}