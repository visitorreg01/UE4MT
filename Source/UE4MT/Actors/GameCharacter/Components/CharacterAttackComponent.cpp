// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4MT.h"
#include "CharacterAttackComponent.h"


// Sets default values for this component's properties
UCharacterAttackComponent::UCharacterAttackComponent()
{
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UCharacterAttackComponent::InitializeComponent()
{
	Super::InitializeComponent();
	// ...
	
}
void UCharacterAttackComponent::PostInitProperties()
{
    Super::PostInitProperties();
    this->DistanceRange = { 0.0f, 100.0f };
    this->DamageRange = { 0.5f, 1.0f };
    this->ReloadTimeout = 1.0f;
}