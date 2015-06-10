// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "ActorRootComponent.generated.h"


UCLASS( ClassGroup=(Utility), meta=(BlueprintSpawnableComponent) )
class UE4MT_API UActorRootComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorRootComponent();
};
