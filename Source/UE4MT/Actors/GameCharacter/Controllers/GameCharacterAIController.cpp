// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4MT.h"
#include "MTDecl.h"

#include "GameCharacterAIController.h"


void AGameCharacterAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    UpdateState();
}



AMTGameCharacter* AGameCharacterAIController::FindEnemy()
{
    AMTGameCharacter* res = nullptr;
    this->CurrentAttackComponent = nullptr;

    TArray<UCharacterAttackComponent*> AttackComponents;

    const TArray<UActorComponent*>& comps = this->Holder->GetComponents();
    for (UActorComponent* Component : comps)
    {
        UCharacterAttackComponent* AttackComp = Cast<UCharacterAttackComponent>(Component);
        if (AttackComp)
        {
            AttackComponents.Add(AttackComp);
        }
    }
    auto f = [](const UCharacterAttackComponent& a, const UCharacterAttackComponent& b){ return a.Priority < b.Priority; };
    AttackComponents.Sort(f);

    if (AttackComponents.Num() > 0)
    {
        UCharacterAttackComponent* SelectedAttack = AttackComponents[0];
        float CurrentMinDistanceSq = SelectedAttack->DistanceRange.To * SelectedAttack->DistanceRange.To;
        for (TActorIterator<AMTGameCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
        {
            if (ActorItr->Team != this->Holder->Team)
            {
                float CurrentTestingDistanceSq = (ActorItr->GetActorLocation() - this->Holder->GetActorLocation()).SizeSquared();
                if (CurrentTestingDistanceSq <= CurrentMinDistanceSq)
                {
                    CurrentMinDistanceSq = CurrentTestingDistanceSq;
                    res = *ActorItr;
                    this->CurrentAttackComponent = SelectedAttack;
                }
                //break;
            }
        }
    }
    return res;
}

bool AGameCharacterAIController::FindEnemyAndStartAttack()
{
    bool res = false;
    AMTGameCharacter* target = FindEnemy();
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
    case AMTGameCharacter::CharacterStateEnum::Idle:
    {
        if (FindEnemyAndStartAttack())
        {

            this->Holder->State = AMTGameCharacter::CharacterStateEnum::NavToEnemy;
        }
        break;
    }
    case AMTGameCharacter::CharacterStateEnum::NavToEnemy:
    {
        if (this->GetMoveStatus() == EPathFollowingStatus::Moving)
        {
            FVector fv = this->Holder->GetMovementVel();
            int i = 0;
        }
        else if (this->GetMoveStatus() == EPathFollowingStatus::Idle)
        {
            this->Holder->State = AMTGameCharacter::CharacterStateEnum::Idle;
            this->Holder->OnAttackComponentChanged(this->CurrentAttackComponent);
        }
        break;
    }
    }
}