
#pragma once


#include "AIController.h"
#include "GameCharacterAIController.generated.h"
class AMTGameCharacter;
/**
 * 
 */
UCLASS()
class UE4MT_API AGameCharacterAIController : public AAIController
{
    GENERATED_BODY()

private:
    struct FindEnemyResult
    {
    public:
        bool HasResult;
        AMTGameCharacter* Target;
        UCharacterAttackComponent* AttackComponent;
        bool ImmediateAttack;
    };


    FindEnemyResult FindEnemy();
    TArray<const AMTGameCharacter*> FindEnemiesInRange(const FVector& SourcePos, FRangeFloat Range, const TArray<const AMTGameCharacter*>& CachedCharacters);

    bool CanAttackCharacter(AMTGameCharacter* Character);


    //Component selected for current attack action (if applicable)
    UCharacterAttackComponent* CurrentAttackComponent;

    //Current attack target if any. Otherwise null.
    AMTGameCharacter* CurrentAttackTarget;

    void UpdateState();

    void TransitionState(AMTGameCharacter::CharacterStateEnum NewState);
public:
    AMTGameCharacter* Holder = nullptr;

    //// Called when the game starts or when spawned
    //virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaSeconds) override;
	
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	
};
