
#pragma once 

#include "GameFramework/Character.h"
#include "UE4MT.h"
#include "Generic/FUnitPrice.h"
#include "Generic/EMTTeamEnum.h"

#include "GameCharacter.generated.h"



UCLASS()
class UE4MT_API AGameCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:



    


    //Key of Localized display name
    //TODO: Add 'EditDefaultsOnly' flag
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
    FName DisplyNameKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    float Speed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    int32 Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    FUnitPrice Price;

    

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    EMTTeamEnum Team;


    UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Attack Component Changed"))
    void OnAttackComponentChanged(const UCharacterAttackComponent* newComponent);

protected:
  /*  TArray<class UCharacterAttackComponent*> AttackComponents;
    TArray<class UCharacterProtectionComponent*> ProtectionComponents;*/
public:	



	// Sets default values for this actor's properties
	AGameCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	//virtual void Tick( float DeltaSeconds ) override;

    void PostInitProperties();

    //virtual void PostInitializeComponents() override;

    virtual void SpawnDefaultController() override;

    inline FVector GetMovementVel()
    {
        return this->RootComponent->ComponentVelocity;
    }
};
