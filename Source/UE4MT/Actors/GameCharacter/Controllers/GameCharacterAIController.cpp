// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4MT.h"
#include "MTDecl.h"

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

bool AGameCharacterAIController::FindEnemyAndStartAttack()
{
    bool res = false;
    AGameCharacter* target = FindEnemy();
    if (target != nullptr)
    {
        float AcceptanceRadius = MTUtils::GetMoveToAcceptanceRadius(this->Holder, target);
        FVector dist = this->Holder->GetActorLocation() - target->GetActorLocation();
        float Distance = dist.Size();


        if (Distance > AcceptanceRadius * 1.1f)
        {
            this->MoveToActor(target, AcceptanceRadius, false, true);
            res = true;
        }
    }
    return res;
}


void AGameCharacterAIController::UpdateState()
{
    
    switch (this->Holder->State)
    {
        case AGameCharacter::CharacterStateEnum::Idle:
        {
            if (FindEnemyAndStartAttack())
            {
                this->Holder->State = AGameCharacter::CharacterStateEnum::NavToEnemy;
            }
            break;
        }
        case AGameCharacter::CharacterStateEnum::NavToEnemy:
        {
            if (this->GetMoveStatus() == EPathFollowingStatus::Moving)
            {
                FVector fv = this->Holder->GetMovementVel();
                int i = 0;
            }
            else if (this->GetMoveStatus() == EPathFollowingStatus::Idle)
            {
                this->Holder->State = AGameCharacter::CharacterStateEnum::Idle;
            }
            break;
        }
    }
}