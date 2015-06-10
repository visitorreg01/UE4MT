#pragma once

#include "GameFramework/Actor.h"
#include "Generic/FUnitPrice.h"

#include "GameCharacter.generated.h"

UCLASS()
class UE4MT_API AGameCharacter : public AActor
{
	GENERATED_BODY()
	
public:
    //Key of Localized display name
    //TODO: Add 'EditDefaultsOnly' flag
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Localized, Category = "Character")
    FName DisplyNameKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    float Speed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    int32 Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    FUnitPrice Price;



public:	



	// Sets default values for this actor's properties
	AGameCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	//virtual void Tick( float DeltaSeconds ) override;

    void PostInitProperties();
	
};
