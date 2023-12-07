// Fill out your copyright notice in the Description page of Project Settings.


#include "MissionPlayerController.h"
#include "../../../../../../../../Program Files/Epic Games/UE_5.2/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/InputAction.h"
#include "../../../../../../../../Program Files/Epic Games/UE_5.2/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/InputMappingContext.h"
#include "../../../../../../../../Program Files/Epic Games/UE_5.2/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/InputTriggers.h"
#include "../../../../../../../../Program Files/Epic Games/UE_5.2/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/InputModifiers.h"
#include "../../../../../../../../Program Files/Epic Games/UE_5.2/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedActionKeyMapping.h"

// Map Key to actions for context & optional modifiers
/*
void AMissionPlayerController::_MapKey(
	UInputMappingContext* InputMappingContext, UInputAction* InputAction, FKey Key,
	bool bNegate = false,
	bool bSwizzle = false, EInputAxisSwizzle SwizzleOrder = EInputAxisSwizzle::YXZ,
	bool bChord = false, UInputAction* ChordAction = NULL)
{
	FEnhancedActionKeyMapping& Mapping = InputMappingContext->MapKey(InputAction, Key);
	UObject* Outer = InputMappingContext->GetOuter();

	if (bNegate)
	{
		UInputModifierNegate* Negate = NewObject<UInputModifierNegate>(Outer);
		Mapping.Modifiers.Add(Negate);
	}

	if (bSwizzle)
	{
		UInputModifierSwizzleAxis* Swizzle = NewObject<UInputModifierSwizzleAxis>(Outer);
		Swizzle->Order = SwizzleOrder;
		Mapping.Modifiers.Add(Swizzle);
	}

	if (bChord)
	{
		UInputTriggerChordAction* Chord = NewObject<UInputTriggerChordAction>(Outer);
		Chord->ChordAction = ChordAction;
		Mapping.Triggers.Add(Chord);

	}
}

void AMissionPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//creates object here
	PawnMappingContext = NewObject<UInputMappingContext>(this);

	

	MoveAction = NewObject<UInputAction>(this);
	MoveAction->ValueType = EInputActionValueType::Axis3D;
	_MapKey(PawnMappingContext, MoveAction, EKeys::W);
	_MapKey(PawnMappingContext, MoveAction, EKeys::S, true);
	_MapKey(PawnMappingContext, MoveAction, EKeys::A, true, true);
	_MapKey(PawnMappingContext, MoveAction, EKeys::D, false, true);
	_MapKey(PawnMappingContext, MoveAction, EKeys::R, false, true, EInputAxisSwizzle::ZYX);
	_MapKey(PawnMappingContext, MoveAction, EKeys::F, true, true, EInputAxisSwizzle::ZYX);

	RotateAction = NewObject<UInputAction>(this);
	RotateAction->ValueType = EInputActionValueType::Axis3D;

	RMB = NewObject<UInputAction>(this);
	RMB->ValueType = EInputActionValueType::Boolean;
	//_MapKey(PawnMappingContext, RMB, EKeys::RightMouseButton);

	//_MapKey(PawnMappingContext, RotateAction, EKeys::MouseY, false, false, EInputAxisSwizzle::YXZ, true, RMB);
	//_MapKey(PawnMappingContext, RotateAction, EKeys::MouseX, false, true, EInputAxisSwizzle::YXZ, true, RMB);
	//UInputTriggerChordAction* ChordedAction = NewObject<UInputTriggerChordAction>();
	
	
	//_MapKey(PawnMappingContext, RMB, EKeys::RightMouseButton);
	//ChordedAction->ChordAction = RMB;
	//_MapKey(PawnMappingContext, RotateAction, EKeys::RightMouseButton);

	//RotateAction->
}
*/
void AMissionPlayerController::SnapMouseToCenter(const APlayerController* PlayerController)
{
	if (PlayerController)
	{
		const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
		if (LocalPlayer && LocalPlayer->ViewportClient)
		{
			FViewport* Viewport = LocalPlayer->ViewportClient->Viewport;
			if (Viewport)
			{
				FVector2D ViewportSize;
				LocalPlayer->ViewportClient->GetViewportSize(ViewportSize);
				const int32 X = static_cast<int32>(ViewportSize.X * 0.5f);
				const int32 Y = static_cast<int32>(ViewportSize.Y * 0.5f);

				Viewport->SetMouse(X, Y);
			}
		}
	}
}
