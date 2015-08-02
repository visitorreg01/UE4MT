// Fill out your copyright notice in the Description page of Project Settings.

//#pragma once
#ifndef _UE4MT_H_INCLUDED_
#define _UE4MT_H_INCLUDED_

#include "Engine.h"


#include "Generic/MTUtilDecls.h"

#include "Generic/ActorRootComponent.h"
#include "Generic/EMTTeamEnum.h"
#include "Generic/FMTPlayersCharacterDescriptor.h"
#include "Generic/FMTPrice.h"
#include "Generic/FRangeFloat.h"
#include "Generic/FUnitPrice.h"

#include "Generic/MTInput.h"
#include "Generic/MTMiniMapCapture.h"

#include "Actors/GameCharacter/MTGameCharacter.h"
#include "Actors/GameCharacter/Components/CharacterAttackComponent.h"
#include "Actors/GameCharacter/Components/CharacterProtectionComponent.h"
#include "Actors/GameCharacter/Controllers/GameCharacterAIController.h"


#include "Actors/PlayerPawn/MTPlayerPawn.h"
#include "Actors/PlayerPawn/Controllers/MTPlayerPawnController.h"
#include "Actors/PlayerPawn/Controllers/MTSpectatorPlayerController.h"

#include "Actors/PlayerPawn/MTSpectatorPawn.h"
#include "Actors/PlayerPawn/MTSpectatorPawnMovement.h"
#include "Actors/PlayerPawn/Camera/MTCameraComponent.h"



#include "Player/MTPlayerState.h"

#include "MTGameMode.h"
#include "MTGameState.h"




/** when you modify this, please note that this information can be saved with instances
* also DefaultEngine.ini [/Script/Engine.CollisionProfile] should match with this list **/
#define COLLISION_WEAPON		ECC_GameTraceChannel1
#define COLLISION_PROJECTILE	ECC_GameTraceChannel2
#define COLLISION_PANCAMERA		ECC_GameTraceChannel3



#endif