// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

//#include "StrategyTypes.h"
#include "MTSpectatorPawnMovement.generated.h"

UCLASS()
class UMTSpectatorPawnMovement : public USpectatorPawnMovement
{
	GENERATED_UCLASS_BODY()

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:
	bool bInitialLocationSet;
};

