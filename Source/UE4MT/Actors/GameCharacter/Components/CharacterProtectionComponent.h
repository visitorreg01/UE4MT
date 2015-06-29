// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"

#include "CharacterProtectionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4MT_API UCharacterProtectionComponent : public UActorComponent
{
	GENERATED_BODY()
public:

    //Key of Localized display name
    //TODO: Add 'EditDefaultsOnly' flag
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Localized, Category = "Protection")
    FName DisplayNameKey;

    //Multiplier. Reduces incoming damage
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Protection")
    float ReductionK;

    //Absolute reduction. Will be subtracted from incoming damage
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Protection")
    float ReductionAbs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Protection")
    USceneComponent* Visuals;


public:	
	// Sets default values for this component's properties
	UCharacterProtectionComponent();

	// Called when the game starts
	virtual void InitializeComponent() override;

    void PostInitProperties();
};
