#pragma once

//#include "StrategyTypes.h"
#include "UE4MT.h"
#include "MTSpectatorPawn.generated.h"

//@TODO: Write a comment here
UCLASS(Blueprintable, BlueprintType)
class AMTSpectatorPawn : public ASpectatorPawn
{
	GENERATED_UCLASS_BODY()

	// Begin ADefaultPawn interface

	/** event call on move forward input */
	virtual void MoveForward(float Val) override;

	/** event call on strafe right input */
	virtual void MoveRight(float Val) override;

	/** Add custom key bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// End ADefaultPawn interface

	// The camera component for this camera
private:
	UPROPERTY(Category = CameraActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMTCameraComponent* MtCameraComponent;
public:

	/** Handles the mouse scrolling down. */
	void OnMouseScrollUp();

	/** Handles the mouse scrolling up. */
	void OnMouseScrollDown();
	
	/* Returns a pointer to the strategy camera component the pawn has. */
	UMTCameraComponent* GetMtCameraComponent();
};


