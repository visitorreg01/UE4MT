// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4MT.h"
#include "GameCharacterAIController.h"

void AGameCharacterAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    UpdateState();
}



AGameCharacter* AGameCharacterAIController::FindEnemy()
{
    AGameCharacter* res = nullptr;
    for (TActorIterator<AGameCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    {
        if (ActorItr->Team != this->Holder->Team)
        {
            res = *ActorItr;
            break;
        }
    }


    return res;
}


void AGameCharacterAIController::UpdateState()
{
    switch (this->Holder->State)
    {
    case AGameCharacter::CharacterStateEnum::Idle:
        AGameCharacter* target = FindEnemy();
        if (target != nullptr)
        {
            this->Holder->State = AGameCharacter::CharacterStateEnum::NavToEnemy;
            //this->MoveToActor(target, 10, false, true);
            this->MoveToLocation(target->GetActorLocation(), 50, false, false);
        }
        break;
    }
}