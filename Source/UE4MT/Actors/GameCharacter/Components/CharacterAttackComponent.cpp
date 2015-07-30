// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4MT.h"


// Sets default values for this component's properties
UCharacterAttackComponent::UCharacterAttackComponent()
{
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = false;
    State = AttackStateEnum::None;
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

void UCharacterAttackComponent::SetState(AttackStateEnum newState)
{
    this->State = newState;
}

UCharacterAttackComponent::AttackStateEnum UCharacterAttackComponent::GetState() const
{
    return this->State;
}

void UCharacterAttackComponent::StartAttackProcess()
{
    this->State = AttackStateEnum::Reloading;
    GetWorld()->GetTimerManager().SetTimer(this->ReloadTimerHandle, this, &UCharacterAttackComponent::AttackReloadTimer, this->ReloadTimeout, true);
}

void UCharacterAttackComponent::AttackReloadTimer()
{
    if (this->State == AttackStateEnum::Reloading)
    {
        this->State = AttackStateEnum::Loaded;
    }
}

void UCharacterAttackComponent::StopAttackProcess()
{
    GetWorld()->GetTimerManager().ClearTimer(this->ReloadTimerHandle);
    this->State = AttackStateEnum::None;
}

void UCharacterAttackComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    StopAttackProcess();
    Super::EndPlay(EndPlayReason);
}
