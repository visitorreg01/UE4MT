#pragma once

#include "GameFramework/Character.h"
#include "Generic/FUnitPrice.h"

#include "GameCharacter.generated.h"



UCLASS()
class UE4MT_API AGameCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:

    UENUM(BlueprintType)
    enum class CharacterStateEnum : uint8
    {
        None            UMETA(DisplayName = "None"), //Exist only for non-initialized character and will not be processed by BP
        Idle            UMETA(DisplayName = "Idle"),
        NavToEnemyBase  UMETA(DisplayName = "NavTo EnemyBase"),
        NavToEnemy      UMETA(DisplayName = "NavTo Enemy"),
        Fighting        UMETA(DisplayName = "Fighting"),
        Dying           UMETA(DisplayName = "Dying"),
        Dead            UMETA(DisplayName = "Dead"),
    };

    UENUM(BlueprintType)
    enum class CharacterTeamEnum : uint8
    {
        None    UMETA(DisplayName = "None"),
        Red     UMETA(DisplayName = "Red"), 
        Blue    UMETA(DisplayName = "Blue"),
    };


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

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
    CharacterStateEnum State;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    CharacterTeamEnum Team;
public:	



	// Sets default values for this actor's properties
	AGameCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	//virtual void Tick( float DeltaSeconds ) override;

    void PostInitProperties();

    virtual void SpawnDefaultController() override;

    inline FVector GetMovementVel()
    {
        return this->RootComponent->ComponentVelocity;
    }
};
