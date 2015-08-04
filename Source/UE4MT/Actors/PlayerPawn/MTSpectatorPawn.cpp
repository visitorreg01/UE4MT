// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.


#include "UE4MT.h"

AMTSpectatorPawn::AMTSpectatorPawn(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UMTSpectatorPawnMovement>(Super::MovementComponentName))
{
	GetCollisionComponent()->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	bAddDefaultMovementBindings = false;
	MtCameraComponent = CreateDefaultSubobject<UMTCameraComponent>(TEXT("MtCameraComponent"));

    this->bReplicateMovement = true;
    this->bReplicates = true;
    this->bUseControllerRotationPitch = true;
    this->bUseControllerRotationRoll = true;
    this->bUseControllerRotationYaw = true;
    
    this->bFindCameraComponentWhenViewTarget = true;
    //this->bTakeCameraControlWhenPossessed = true;
    //this->PlayerState
}

void AMTSpectatorPawn::OnMouseScrollUp()
{
    MtCameraComponent->OnZoomIn();
}

void AMTSpectatorPawn::OnMouseScrollDown()
{
    MtCameraComponent->OnZoomOut();
}


void AMTSpectatorPawn::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	check(InputComponent);
	
    InputComponent->BindAction("ZoomOut", IE_Pressed, this, &AMTSpectatorPawn::OnMouseScrollUp);
    InputComponent->BindAction("ZoomIn", IE_Pressed, this, &AMTSpectatorPawn::OnMouseScrollDown);

    InputComponent->BindAxis("MoveForward", this, &AMTSpectatorPawn::MoveForward);
    InputComponent->BindAxis("MoveRight", this, &AMTSpectatorPawn::MoveRight);
}


void AMTSpectatorPawn::MoveForward(float Val)
{
    MtCameraComponent->MoveForward(Val);
}


void AMTSpectatorPawn::MoveRight(float Val)
{
    MtCameraComponent->MoveRight(Val);
}

UMTCameraComponent* AMTSpectatorPawn::GetMtCameraComponent()
{
    check(MtCameraComponent != NULL);
    return MtCameraComponent;
}

