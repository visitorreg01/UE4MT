// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.


#include "UE4MT.h"


UMTSpectatorPawnMovement::UMTSpectatorPawnMovement(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), bInitialLocationSet(false)
{
	MaxSpeed  = 16000.f;
	Acceleration = 5000.f;
	Deceleration = 4000.f;
    
}


void UMTSpectatorPawnMovement::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent)
	{
		return;
	}

    AMTPlayerPawnController* PlayerController = Cast<AMTPlayerPawnController>(PawnOwner->GetController());
	if (PlayerController && PlayerController->IsLocalController())
	{
		if (!bInitialLocationSet)
		{

            PawnOwner->SetActorRotation(PlayerController->GetControlRotation());
			PawnOwner->SetActorLocation(PlayerController->GetSpawnLocation());

           
			bInitialLocationSet = true;
		}

		FVector MyLocation = UpdatedComponent->GetComponentLocation();
        AMTSpectatorPawn* SpectatorPawn = Cast<AMTSpectatorPawn>(PlayerController->GetSpectatorPawn());
		if( ( SpectatorPawn != NULL ) && ( SpectatorPawn->GetMtCameraComponent() != NULL) )
		{
			SpectatorPawn->GetMtCameraComponent()->ClampCameraLocation(PlayerController, MyLocation);
		}
		UpdatedComponent->SetWorldLocation(MyLocation, false);
	}
}

