
#pragma once 

#include "GameFramework/Character.h"
#include "UE4MT.h"
#include "Generic/FUnitPrice.h"
#include "Generic/EMTTeamEnum.h"

#include "MTGameCharacter.generated.h"



UCLASS()
class UE4MT_API AMTGameCharacter : public ACharacter
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
    EMTTeamEnum Team;

    //Characher selected new attack component. Or Null in case attack is finished.
    UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Attack Component Changed"))
    void OnAttackComponentChanged(const UCharacterAttackComponent* newComponent);

    //Used to play hit animation. Sets to True in single tick. Temporary.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (DisplayName = "AttackHitThisTick"))
    bool AttackHitThisTick;
protected:
  /*  TArray<class UCharacterAttackComponent*> AttackComponents;
    TArray<class UCharacterProtectionComponent*> ProtectionComponents;*/
public:	
    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;


	// Sets default values for this actor's properties
	AMTGameCharacter();

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
