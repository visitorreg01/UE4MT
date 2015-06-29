// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "Generic/FRangeFloat.h"
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
    int32 Proprity;

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

public:	
	// Sets default values for this component's properties
	UCharacterAttackComponent();

	// Called when the game starts
	virtual void InitializeComponent() override;
	
    void PostInitProperties();
	
};
