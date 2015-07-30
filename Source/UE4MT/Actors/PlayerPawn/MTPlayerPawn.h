#pragma once

#include "GameFramework/Pawn.h"
#include "UE4MT.h"

#include "MTPlayerPawn.generated.h"



UCLASS()
class UE4MT_API AMTPlayerPawn : public APawn
{
	GENERATED_BODY()
	
public:

    EMTTeamEnum Team;

    
public:	



	// Sets default values for this actor's properties
    AMTPlayerPawn();

	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;
	
	// Called every frame
	//virtual void Tick( float DeltaSeconds ) override;

    //void PostInitProperties();

    //virtual void PostInitializeComponents() override;

    //virtual void SpawnDefaultController() override;

};
