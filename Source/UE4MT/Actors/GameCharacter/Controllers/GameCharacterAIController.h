
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
  

    AMTGameCharacter* FindEnemy();
    bool FindEnemyAndStartAttack();

    //Component selected for current attack action (if applicable)
    UCharacterAttackComponent* CurrentAttackComponent;


    void UpdateState();

public:
    AMTGameCharacter* Holder = nullptr;

    //// Called when the game starts or when spawned
    //virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaSeconds) override;
	
	
	
};
