// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "UE4MT.h"
#include "Generic/FRangeFloat.h"
//#include "Actors/GameCharacter/Controllers/GameCharacterAIController.h"

#include "CharacterAttackComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4MT_API UCharacterAttackComponent : public UActorComponent
{
	GENERATED_BODY()
    
public:
    //Key of Localized display name
    //TODO: Add 'EditDefaultsOnly' flag
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
    FName DisplayNameKey;

    //
    //Priority used when there are few available attack components
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    int32 Priority;

    //Distance in world units
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    FRangeFloat DistanceRange;

    //Damage
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    FRangeFloat DamageRange;

    //Seconds
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    float ReloadTimeout;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    USceneComponent* Visuals;


    enum class AttackStateEnum
    {
        None,
        Reloading,
        Loaded,
    };

protected:
   

    FTimerHandle ReloadTimerHandle;
    AttackStateEnum State;

    float LastAttackTime;

public:	
	// Sets default values for this component's properties
	UCharacterAttackComponent();

	// Called when the game starts
	virtual void InitializeComponent() override;
	
    void PostInitProperties();

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
    void SetState(AttackStateEnum newState);
    AttackStateEnum GetState() const;
    void AttackReloadTimer();
    void StartAttackProcess();
    void StopAttackProcess();
};
