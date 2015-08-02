// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "UE4MT.h"
#include "Generic/MTUtilDecls.h"
//#include "SStrategyButtonWidget.h"
//#include "StrategyCheatManager.h"
#include "Actors/PlayerPawn/Camera/MTCameraComponent.h"
#include "Generic/MTInput.h"
#include "Actors/PlayerPawn/MTSpectatorPawn.h"
//#include "StrategySelectionInterface.h"
//#include "StrategyInputInterface.h"


AMTSpectatorPlayerController::AMTSpectatorPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bIgnoreInput(false)
{
	//CheatClass = UStrategyCheatManager::StaticClass();
	PrimaryActorTick.bCanEverTick = true;
	bHidden = false;
	bShowMouseCursor = true;
    
}

void AMTSpectatorPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputHandler = NewObject<UMTInput>(this);

    BIND_1P_ACTION(InputHandler, GameKeyTypeEnum::Tap, IE_Pressed, &AMTSpectatorPlayerController::OnTapPressed);
    BIND_1P_ACTION(InputHandler, GameKeyTypeEnum::Hold, IE_Pressed, &AMTSpectatorPlayerController::OnHoldPressed);
    BIND_1P_ACTION(InputHandler, GameKeyTypeEnum::Hold, IE_Released, &AMTSpectatorPlayerController::OnHoldReleased);
    BIND_1P_ACTION(InputHandler, GameKeyTypeEnum::Swipe, IE_Pressed, &AMTSpectatorPlayerController::OnSwipeStarted);
    BIND_1P_ACTION(InputHandler, GameKeyTypeEnum::Swipe, IE_Repeat, &AMTSpectatorPlayerController::OnSwipeUpdate);
    BIND_1P_ACTION(InputHandler, GameKeyTypeEnum::Swipe, IE_Released, &AMTSpectatorPlayerController::OnSwipeReleased);
    BIND_2P_ACTION(InputHandler, GameKeyTypeEnum::SwipeTwoPoints, IE_Pressed, &AMTSpectatorPlayerController::OnSwipeTwoPointsStarted);
    BIND_2P_ACTION(InputHandler, GameKeyTypeEnum::SwipeTwoPoints, IE_Repeat, &AMTSpectatorPlayerController::OnSwipeTwoPointsUpdate);
    BIND_2P_ACTION(InputHandler, GameKeyTypeEnum::Pinch, IE_Pressed, &AMTSpectatorPlayerController::OnPinchStarted);
    BIND_2P_ACTION(InputHandler, GameKeyTypeEnum::Pinch, IE_Repeat, &AMTSpectatorPlayerController::OnPinchUpdate);

	FInputActionBinding& ToggleInGameMenuBinding = InputComponent->BindAction("InGameMenu", IE_Pressed, this, &AMTSpectatorPlayerController::OnToggleInGameMenu);
	ToggleInGameMenuBinding.bExecuteWhenPaused = true;

}

void AMTSpectatorPlayerController::GetAudioListenerPosition(FVector& OutLocation, FVector& OutFrontDir, FVector& OutRightDir)
{
	Super::GetAudioListenerPosition(OutLocation, OutFrontDir, OutRightDir);

	AMTGameState const* const MyGameState = GetWorld()->GetGameState<AMTGameState>();
	if (GEngine && GEngine->GameViewport && GEngine->GameViewport->ViewportFrame && MyGameState != NULL && MyGameState->MiniMapCamera.IsValid())
	{
		// Set Listener position to be the center of the viewport, projected into the game world.

		FViewport* const Viewport = GEngine->GameViewport->ViewportFrame->GetViewport();
		if (Viewport)
		{
			FVector2D const ScreenRes = Viewport->GetSizeXY();

            float GroundLevel = 0.0f;// MyGameState->MiniMapCamera->AudioListenerGroundLevel;
			const FPlane GroundPlane = FPlane(FVector(0,0,GroundLevel), FVector::UpVector);
			ULocalPlayer* const MyPlayer = Cast<ULocalPlayer>(Player);

			// @todo: once PlayerCamera is back in, we can just get the ray origin and dir from that instead of 
			// needing to deproject. will be much simpler.
			FVector RayOrigin, RayDirection;
			FVector2D const ScreenCenterPoint = ScreenRes * 0.5f;
			FMTHelpers::DeprojectScreenToWorld(ScreenCenterPoint, MyPlayer, RayOrigin, RayDirection);

			FVector const WorldPoint = FMTHelpers::IntersectRayWithPlane(RayOrigin, RayDirection, GroundPlane);
            FVector const AudioListenerOffset = MyGameState->MiniMapCamera->AudioListenerLocationOffset;
			OutLocation = WorldPoint.GetClampedToSize(MyGameState->WorldBounds.Min.GetMin(), MyGameState->WorldBounds.Max.GetMax()) + AudioListenerOffset;

            bool bUseCustomOrientation = MyGameState->MiniMapCamera->bUseAudioListenerOrientation;
			if (bUseCustomOrientation)
			{
				OutFrontDir = MyGameState->MiniMapCamera->AudioListenerFrontDir;
				OutRightDir = MyGameState->MiniMapCamera->AudioListenerRightDir;
			}
		}
	}
}

void AMTSpectatorPlayerController::OnToggleInGameMenu()
{
	//AStrategyHUD* const MyHUD = Cast<AStrategyHUD>(GetHUD());
	//if (MyHUD)
	//{
	//	MyHUD->TogglePauseMenu();
	//}
}

void AMTSpectatorPlayerController::UpdateRotation(float DeltaTime)
{
	FRotator ViewRotation(0, 0, 0);
	FRotator DeltaRot(0, 0, 0);

	if (PlayerCameraManager)
	{
		PlayerCameraManager->ProcessViewRotation(DeltaTime, ViewRotation, DeltaRot);
	}
	
	SetControlRotation(ViewRotation);
}

void AMTSpectatorPlayerController::ProcessPlayerInput(const float DeltaTime, const bool bGamePaused)
{
	if (!bGamePaused && PlayerInput && InputHandler && !bIgnoreInput)
	{
		InputHandler->UpdateDetection(DeltaTime);
	}

	Super::ProcessPlayerInput(DeltaTime, bGamePaused);
		
	if (!bIgnoreInput )
	{
		const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
		AMTSpectatorPawn* StrategyPawn = GetMtSpectatorPawn();		
		if(( StrategyPawn != NULL ) && ( LocalPlayer != NULL ))
		{
			// Create the bounds for the minimap so we can add it as a 'no scroll' zone.
			//AStrategyHUD* const HUD = Cast<AStrategyHUD>(GetHUD());
			AMTGameState const* const MyGameState = GetWorld()->GetGameState<AMTGameState>();
			if( (MyGameState != NULL ) && ( MyGameState->MiniMapCamera.IsValid() == true ) )
			{
				if( LocalPlayer->ViewportClient != NULL )
				{
					const FIntPoint ViewportSize = LocalPlayer->ViewportClient->Viewport->GetSizeXY();
					const uint32 ViewTop = FMath::TruncToInt(LocalPlayer->Origin.Y * ViewportSize.Y);
					const uint32 ViewBottom = ViewTop + FMath::TruncToInt(LocalPlayer->Size.Y * ViewportSize.Y);

					//FVector TopLeft( HUD->MiniMapMargin, ViewBottom - HUD->MiniMapMargin - MyGameState->MiniMapCamera->MiniMapHeight, 0 );
					//FVector BottomRight( (int32)MyGameState->MiniMapCamera->MiniMapWidth, MyGameState->MiniMapCamera->MiniMapHeight, 0 );
                    FBox MiniMapBounds(FVector::ZeroVector, FVector::ZeroVector);// = FBox(TopLeft, TopLeft + BottomRight);
					StrategyPawn->GetMtCameraComponent()->AddNoScrollZone( MiniMapBounds );
					StrategyPawn->GetMtCameraComponent()->UpdateCameraMovement( this );
				}
			}
		}		
	}
}

void AMTSpectatorPlayerController::SetCameraTarget(const FVector& CameraTarget)
{	
	if (GetCameraComponent() != NULL)
	{
		GetCameraComponent()->SetCameraTarget(CameraTarget);
	}
}

//AActor* AMTSpectatorPlayerController::GetFriendlyTarget(const FVector2D& ScreenPoint, FVector& WorldPoint) const
//{
//	FHitResult Hit;
//	if ( GetHitResultAtScreenPosition(ScreenPoint, COLLISION_WEAPON, true, Hit) )
//	{
//		if ( !AMtGameMode::OnEnemyTeam(Hit.GetActor(), this) )
//		{
//			WorldPoint = Hit.ImpactPoint;
//			return Hit.GetActor();
//		}
//	}
//
//	return NULL;
//}

void AMTSpectatorPlayerController::SetIgnoreInput(bool bIgnore)
{
	bIgnoreInput = bIgnore;
}
//
//
//void AMTSpectatorPlayerController::SetSelectedActor(AActor* NewSelectedActor, const FVector& NewPosition)
//{
//	if (SelectedActor != NewSelectedActor)
//	{
//		// attempt to unselect current selection
//		AActor* const OldSelection = SelectedActor.Get();
//		if ( OldSelection && OldSelection->GetClass()->ImplementsInterface(UStrategySelectionInterface::StaticClass()) )
//		{
//			if ( IStrategySelectionInterface::Execute_OnSelectionLost(OldSelection, NewPosition, NewSelectedActor) )
//			{
//				SelectedActor = NULL;
//			}
//		}
//		
//		if ( !SelectedActor.IsValid() )
//		{
//			// attempt to select new selection
//			if (NewSelectedActor && NewSelectedActor->GetClass()->ImplementsInterface(UStrategySelectionInterface::StaticClass()) )
//			{
//				if ( IStrategySelectionInterface::Execute_OnSelectionGained(NewSelectedActor) )
//				{
//					SelectedActor = NewSelectedActor;
//				}
//			}
//		}
//	}
//}

void AMTSpectatorPlayerController::OnTapPressed(const FVector2D& ScreenPosition, float DownTime)
{
	/*FVector WorldPosition(0.f);
	AActor* const HitActor = GetFriendlyTarget(ScreenPosition, WorldPosition);
	
	SetSelectedActor(HitActor, WorldPosition);

	if (HitActor && HitActor->GetClass()->ImplementsInterface(UStrategyInputInterface::StaticClass()) )
	{
		IStrategyInputInterface::Execute_OnInputTap(HitActor);
	}*/
}

void AMTSpectatorPlayerController::OnHoldPressed(const FVector2D& ScreenPosition, float DownTime)
{
	//FVector WorldPosition(0.0f);
	//AActor* const HitActor = GetFriendlyTarget(ScreenPosition, WorldPosition);

	//SetSelectedActor(HitActor, WorldPosition);

	//if ( HitActor && HitActor->GetClass()->ImplementsInterface(UStrategyInputInterface::StaticClass()) )
	//{
	//	IStrategyInputInterface::Execute_OnInputHold(HitActor);
	//}
}

void AMTSpectatorPlayerController::OnHoldReleased(const FVector2D& ScreenPosition, float DownTime)
{
	/*AActor* const Selected = SelectedActor.Get();
	if ( Selected && Selected->GetClass()->ImplementsInterface(UStrategyInputInterface::StaticClass()) )
	{
		IStrategyInputInterface::Execute_OnInputHoldReleased(Selected, DownTime);
	}*/
}

void AMTSpectatorPlayerController::OnSwipeStarted(const FVector2D& AnchorPosition, float DownTime)
{
	//if (GetCameraComponent() != NULL)
	//{
	//	GetCameraComponent()->OnSwipeStarted(AnchorPosition);
	//}

	//FVector WorldPosition(0.0f);
	//AActor* const HitActor = GetFriendlyTarget(AnchorPosition, WorldPosition);

	//SetSelectedActor(HitActor, WorldPosition);

	///** Get our position in 3d space */
	//if (SelectedActor.IsValid())
	//{
	//	SwipeAnchor3D = SelectedActor->GetActorLocation();
	//}

	PrevSwipeScreenPosition = AnchorPosition;
}

void AMTSpectatorPlayerController::OnSwipeUpdate(const FVector2D& ScreenPosition, float DownTime)
{
	/*AActor* const Selected = SelectedActor.Get();
	if ( Selected && Selected->GetClass()->ImplementsInterface(UStrategyInputInterface::StaticClass()) )
	{
		ULocalPlayer* const MyPlayer =  Cast<ULocalPlayer>(Player);
		const FPlane GroundPlane = FPlane(FVector(0, 0, SelectedActor->GetActorLocation().Z), FVector(0,0,1));

		FVector RayOrigin, RayDirection;
		FStrategyHelpers::DeprojectScreenToWorld(ScreenPosition, MyPlayer, RayOrigin, RayDirection);
		const FVector ScreenPosition3D = FStrategyHelpers::IntersectRayWithPlane(RayOrigin, RayDirection, GroundPlane);

		IStrategyInputInterface::Execute_OnInputSwipeUpdate(Selected, ScreenPosition3D - SwipeAnchor3D);
	}
	else
	{*/
		if (GetCameraComponent() != NULL)
		{
			GetCameraComponent()->OnSwipeUpdate(ScreenPosition);
		}
	//}

	PrevSwipeScreenPosition = ScreenPosition;
}

void AMTSpectatorPlayerController::OnSwipeReleased(const FVector2D& ScreenPosition, float DownTime)
{
	/*AActor* const Selected = SelectedActor.Get();
	if ( Selected && Selected->GetClass()->ImplementsInterface(UStrategyInputInterface::StaticClass()) )
	{
		ULocalPlayer* const MyPlayer =  Cast<ULocalPlayer>(this->Player);
		const FPlane GroundPlane = FPlane(FVector(0, 0, SelectedActor->GetActorLocation().Z), FVector(0,0,1));

		FVector RayOrigin, RayDirection;
		FStrategyHelpers::DeprojectScreenToWorld(ScreenPosition, MyPlayer, RayOrigin, RayDirection);
		const FVector ScreenPosition3D = FStrategyHelpers::IntersectRayWithPlane(RayOrigin, RayDirection, GroundPlane);

		IStrategyInputInterface::Execute_OnInputSwipeReleased(Selected, ScreenPosition3D - SwipeAnchor3D, DownTime);
	}
	else
	{*/
		if (GetCameraComponent() != NULL)
		{
			GetCameraComponent()->OnSwipeReleased(ScreenPosition);
		}
	//}
}

void AMTSpectatorPlayerController::OnSwipeTwoPointsStarted(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime)
{
	PrevSwipeMidPoint = (ScreenPosition1 + ScreenPosition2) * 0.5f;
}

void AMTSpectatorPlayerController::OnSwipeTwoPointsUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime)
{
	const FVector2D SwipeMidPoint = (ScreenPosition1 + ScreenPosition2) * 0.5f;
	const FVector MoveDir = FVector(SwipeMidPoint - PrevSwipeMidPoint, 0.0f).GetSafeNormal();
	const float SwipeSpeed = 10000.0f;

	const FRotationMatrix R(PlayerCameraManager->GetCameraRotation() + FRotator(0.0, 90.0, 0.0));
	const FVector WorldSpaceAccel = R.TransformVector(MoveDir) * SwipeSpeed;
	if (GetSpectatorPawn())
	{
		GetSpectatorPawn()->AddMovementInput(WorldSpaceAccel, 1.f);
	}	

	PrevSwipeMidPoint = SwipeMidPoint;
}

void AMTSpectatorPlayerController::OnPinchStarted(const FVector2D& AnchorPosition1, const FVector2D& AnchorPosition2, float DownTime)
{
	// Pass the pinch through to the camera component.
	if (GetCameraComponent() != NULL)
	{
		 GetCameraComponent()->OnPinchStarted( AnchorPosition1, AnchorPosition2, DownTime );
	}
}

void AMTSpectatorPlayerController::OnPinchUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime)
{
	// Pass the pinch through to the camera component.
	if (GetCameraComponent() != NULL)
	{
		GetCameraComponent()->OnPinchUpdate(InputHandler, ScreenPosition1, ScreenPosition2, DownTime);
	}
}

AMTSpectatorPawn* AMTSpectatorPlayerController::GetMtSpectatorPawn() const
{
	return Cast<AMTSpectatorPawn>( GetSpectatorPawn() );
}

UMTCameraComponent* AMTSpectatorPlayerController::GetCameraComponent() const
{
	UMTCameraComponent* CameraComponent = NULL;
	if (GetMtSpectatorPawn() != NULL)
	{
		CameraComponent = GetMtSpectatorPawn()->GetMtCameraComponent();
	}
	return CameraComponent;
}

void AMTSpectatorPlayerController::MouseLeftMinimap()
{
	if (GetCameraComponent() != NULL)
	{
		GetCameraComponent()->EndSwipeNow();
	}
}
void AMTSpectatorPlayerController::MousePressedOverMinimap()
{
	if (GetCameraComponent() != NULL)
	{
		GetCameraComponent()->EndSwipeNow();
	}
}

void AMTSpectatorPlayerController::MouseReleasedOverMinimap()
{
	if (GetCameraComponent() != NULL)
	{
		GetCameraComponent()->EndSwipeNow();
	}
}
