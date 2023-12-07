// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../../../../../../../../Program Files/Epic Games/UE_5.2/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/InputMappingContext.h"
#include "../../../../../../../../Program Files/Epic Games/UE_5.2/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/InputModifiers.h"
#include "MissionPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ASTRODYNAMICS_ACTUAL_API AMissionPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/*
	static void _MapKey(UInputMappingContext* InputMappingContext, UInputAction* InputAction, FKey Key,
		bool bNegate,
		bool bSwizzle, EInputAxisSwizzle SwizzleOrder,
		bool bChord, UInputAction* ChordAction);
	// input actions & context maps
	virtual void SetupInputComponent() override;
	*/
	UFUNCTION(BlueprintCallable)
	static void SnapMouseToCenter(const APlayerController* PlayerController);
	/*
	//map context for pawn control
	UPROPERTY()
	class UInputMappingContext* PawnMappingContext;

	//Update location action
	UPROPERTY()
	class UInputAction* MoveAction;

	//Update rotation action
	UPROPERTY()
	class UInputAction* RotateAction;

	//right mouse button, specifically for rotation
	UPROPERTY()
	class UInputAction* RMB;
	*/
};
