// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4MT.h"
#include "MTDecl.h"

void AGameCharacterAIController::Tick(float DeltaSeconds)
{
    
    Super::Tick(DeltaSeconds);

    if (this->Holder->Health <= 0)
    {
        TransitionState(AMTGameCharacter::CharacterStateEnum::Dying);
    }

    UpdateState();
}


TArray<const AMTGameCharacter*> AGameCharacterAIController::FindEnemiesInRange(const FVector& SourcePos, FRangeFloat Range, const TArray<const AMTGameCharacter*>& CachedCharacters )
{
    TArray<const AMTGameCharacter*> res;
    res.Reserve(CachedCharacters.Num());

    float minSq = Range.From * Range.From;
    float maxSq = Range.To * Range.To;
    
    for (auto e : CachedCharacters)
    {
        const FVector& pos = e->GetActorLocation();
        float distSq = (pos - SourcePos).SizeSquared();
        if ((distSq >= minSq) && (distSq <= maxSq))
        {
            res.Add(e);
        }
    }

    return res;
}

bool AGameCharacterAIController::CanAttackCharacter(AMTGameCharacter* Character)
{
    bool res = Character->Team != this->Holder->Team;

    res = res && ((Character->State == AMTGameCharacter::CharacterStateEnum::Idle)
        || (Character->State == AMTGameCharacter::CharacterStateEnum::NavToEnemy)
        || (Character->State == AMTGameCharacter::CharacterStateEnum::Fighting)
        || (Character->State == AMTGameCharacter::CharacterStateEnum::NavToEnemyBase)
        );
    return res;

}

AGameCharacterAIController::FindEnemyResult AGameCharacterAIController::FindEnemy()
{
    FindEnemyResult res{ false, nullptr, nullptr, false };

    typedef TMap<UCharacterAttackComponent*, TArray<const AMTGameCharacter*>> AttackToTargetMap;

    // Damage - can attack immediately
    // Attack - needs to follow enemy then attack

    this->CurrentAttackComponent = nullptr;
    TArray<const UCharacterAttackComponent*> AttackComponents;
    TArray<const AMTGameCharacter*> CachedEnemyCharacters;

    AttackToTargetMap DamageMap;
    AttackToTargetMap DistanceMap;

    const FVector& MyLocation = this->Holder->GetActorLocation();

    //fill enemy team characters
    for (TActorIterator<AMTGameCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    {
        if (CanAttackCharacter(*ActorItr))
        {
            CachedEnemyCharacters.Add(*ActorItr);
        }
    }

    const TArray<UActorComponent*>& comps = this->Holder->GetComponents();
    for (UActorComponent* Component : comps)
    {
        UCharacterAttackComponent* AttackComp = Cast<UCharacterAttackComponent>(Component);
        if (AttackComp)
        {
            AttackComponents.Add(AttackComp);
            TArray<const AMTGameCharacter*> arrDamage = FindEnemiesInRange(MyLocation, AttackComp->DamageRange, CachedEnemyCharacters);
            if (arrDamage.Num() > 0)
            {
                DamageMap.Add(AttackComp, arrDamage);
            }

            TArray<const AMTGameCharacter*> arrAttack = FindEnemiesInRange(MyLocation, AttackComp->DistanceRange, CachedEnemyCharacters);
            if (arrAttack.Num())
            {
                DistanceMap.Add(AttackComp, arrAttack);
            }
        }
    }

    auto fnDamageMapSort = [](const UCharacterAttackComponent& a, const UCharacterAttackComponent& b) { return (a.DamageRange.To > b.DamageRange.To); };
    DamageMap.KeySort(fnDamageMapSort);

    auto fnAttackMapSort = [](const UCharacterAttackComponent& a, const UCharacterAttackComponent& b) { return (a.DamageRange.To > b.DamageRange.To); };
    DistanceMap.KeySort(fnAttackMapSort);


    auto fnCharactersArrSort = [&](const AMTGameCharacter& a, const AMTGameCharacter& b) { return (MyLocation - a.GetActorLocation()).SizeSquared() <= (MyLocation - b.GetActorLocation()).SizeSquared(); };

    if (DamageMap.Num() > 0)
    {
        AttackToTargetMap::TConstIterator it = DamageMap.CreateConstIterator();
        TArray<const AMTGameCharacter*> arr = it->Value;
        arr.Sort(fnCharactersArrSort);
        this->CurrentAttackComponent = it->Key;
        res.HasResult = true;
        res.Target = const_cast<AMTGameCharacter*>(arr[0]);
        res.AttackComponent = it->Key;
        res.ImmediateAttack = true;
    }
    else if (DistanceMap.Num() > 0)
    {
        AttackToTargetMap::TConstIterator it = DistanceMap.CreateConstIterator();
        TArray<const AMTGameCharacter*> arr = it->Value;
        arr.Sort(fnCharactersArrSort);

        this->CurrentAttackComponent = it->Key;
        res.HasResult = true;
        res.Target = const_cast<AMTGameCharacter*>(arr[0]);
        res.AttackComponent = it->Key;
        res.ImmediateAttack = false;
    }

    return res;
}


void AGameCharacterAIController::TransitionState(AMTGameCharacter::CharacterStateEnum NewState)
{
    switch (this->Holder->State)
    {
    case AMTGameCharacter::CharacterStateEnum::Fighting:
    {
        this->CurrentAttackTarget = nullptr;
        this->CurrentAttackComponent->StopAttackProcess();
        this->CurrentAttackComponent = nullptr;
        break;
    }
    default:
        break;
    }
    this->Holder->State = NewState;

}


void AGameCharacterAIController::UpdateState()
{

    switch (this->Holder->State)
    {
    case AMTGameCharacter::CharacterStateEnum::Idle:
    {
        bool res = false;
        FindEnemyResult findEnemyResult = FindEnemy();
        if (findEnemyResult.HasResult)
        {
            if (findEnemyResult.ImmediateAttack)
            {
                TransitionState(AMTGameCharacter::CharacterStateEnum::Fighting);
                this->CurrentAttackComponent = findEnemyResult.AttackComponent;
                this->CurrentAttackTarget = findEnemyResult.Target;
                this->Holder->OnAttackComponentChanged(this->CurrentAttackComponent);
            }
            else
            {
                float AcceptanceRadius = findEnemyResult.AttackComponent->DamageRange.To + MTUtils::GetMoveToAcceptanceRadius(this->Holder, findEnemyResult.Target);
                FVector dist = (this->Holder->GetActorLocation() - findEnemyResult.Target->GetActorLocation()) - AcceptanceRadius;
                float Distance = dist.Size();
                this->MoveToActor(findEnemyResult.Target, AcceptanceRadius, false, true);

                TransitionState(AMTGameCharacter::CharacterStateEnum::NavToEnemy);

                this->CurrentAttackComponent = findEnemyResult.AttackComponent;
                this->CurrentAttackTarget = findEnemyResult.Target;
                this->Holder->OnAttackComponentChanged(this->CurrentAttackComponent);
            }

        }
        break;
    }
    case AMTGameCharacter::CharacterStateEnum::NavToEnemy:
    {
        if (this->GetMoveStatus() == EPathFollowingStatus::Moving) //processing movement
        {
            FVector fv = this->Holder->GetMovementVel();
            int i = 0;
        }
        else if (this->GetMoveStatus() == EPathFollowingStatus::Idle) //navigation finished. start attack
        {
            TransitionState(AMTGameCharacter::CharacterStateEnum::Fighting);
            this->CurrentAttackComponent->StartAttackProcess();

            //Same AttackComponnt stays
            /*
            this->Holder->OnAttackComponentChanged(this->CurrentAttackComponent); 
            */
        }
        break;
    }
    case AMTGameCharacter::CharacterStateEnum::Fighting:
    {
        if (this->CurrentAttackTarget != nullptr) //fight processing
        {

            if (this->CurrentAttackComponent->GetState() == UCharacterAttackComponent::AttackStateEnum::Loaded)
            {
                this->Holder->AttackHitThisTick = true;
                int32 damage = FMath::RandRange(this->CurrentAttackComponent->DamageRange.From, this->CurrentAttackComponent->DamageRange.To);
                this->CurrentAttackTarget->TakeDamage(damage, FDamageEvent(), this, this->Holder);
                this->CurrentAttackComponent->SetState(UCharacterAttackComponent::AttackStateEnum::Reloading);
            }
            else
            {
                this->Holder->AttackHitThisTick = false;
            }


            if (this->CurrentAttackTarget->IsPendingKill() || (this->CurrentAttackTarget->Health <= 0))// fight finished. Target is dead. Stop attacking
            {   
                TransitionState(AMTGameCharacter::CharacterStateEnum::Idle);
            }
        }

        break;
    }

    }
}

void AGameCharacterAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (this->CurrentAttackComponent != nullptr)
    {
        this->CurrentAttackComponent->StopAttackProcess();
    }
    
    Super::EndPlay(EndPlayReason);
}

