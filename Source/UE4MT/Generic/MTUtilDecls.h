#pragma once

#include "UE4MT.h"



DECLARE_DELEGATE_TwoParams(FOnePointActionSignature, const FVector2D&, float);
DECLARE_DELEGATE_ThreeParams(FTwoPointsActionSignature, const FVector2D&, const FVector2D&, float);

DECLARE_DELEGATE_RetVal(bool, FActionButtonDelegate);
DECLARE_DELEGATE_RetVal(FText, FGetQueueLength)


struct FActionButtonData
{
	FText StrButtonText;
	FText StrTooltip;
	EVisibility Visibility;
	bool bIsEnabled;
	int32 ActionCost;
	UTexture2D*	ActionIcon;
	FActionButtonDelegate TriggerDelegate;
	FGetQueueLength GetQueueLengthDelegate;

	FActionButtonData()
	{
		StrButtonText = FText::GetEmpty();
		StrTooltip = FText::GetEmpty();
		bIsEnabled = true;
		ActionCost = 0;
		Visibility = EVisibility::Hidden;
		ActionIcon = NULL;
	}
};

struct FActionButtonInfo
{
	TSharedPtr<class SStrategyButtonWidget> Widget;
	FActionButtonData Data;
};


class FMTHelpers
{
public:
    /** convert point in screen space to ray in world space */
    static bool DeprojectScreenToWorld(const FVector2D& ScreenPosition, class ULocalPlayer* Player, FVector& RayOrigin, FVector& RayDirection);

    /** find intersection of ray in world space with ground plane */
    static FVector IntersectRayWithPlane(const FVector& RayOrigin, const FVector& RayDirection, const FPlane& Plane);

    /** create alpha map from UTexture2D for hit-tests in Slate */
    static TSharedPtr<TArray<uint8>> CreateAlphaMapFromTexture(UTexture2D* Texture);

    /** creates FCanvasUVTri without UV from 3x FVector2D */
    static FCanvasUVTri CreateCanvasTri(FVector2D V0, FVector2D V1, FVector2D V2);
};
