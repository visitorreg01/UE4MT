// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4MT.h"
#include "CharacterProtectionComponent.h"


// Sets default values for this component's properties
UCharacterProtectionComponent::UCharacterProtectionComponent()
{
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UCharacterProtectionComponent::InitializeComponent()
{
	Super::InitializeComponent();
}


void UCharacterProtectionComponent::PostInitProperties()
{
    Super::PostInitProperties();
    this->ReductionK = 1.0f;
    this->ReductionAbs = 0.0f;
}