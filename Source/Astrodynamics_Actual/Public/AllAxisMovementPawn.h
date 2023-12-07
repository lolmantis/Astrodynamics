// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AllAxisMovementPawn.generated.h"

UCLASS()
class ASTRODYNAMICS_ACTUAL_API AAllAxisMovementPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAllAxisMovementPawn();

public:	
	/*
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Handles inputs to update location
	void Move(const struct FInputActionValue& ActionValue);

	// Handles input to update rotation
	void Rotate(const struct FInputActionValue& ActionValue);

	// Sphere for all other attachments
	UPROPERTY(EditAnywhere)
	class USphereComponent* Sphere;

	// arm for camera, deprecated
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArm;

	// camera
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	class UFloatingPawnMovement* Movement;

	UPROPERTY(EditAnywhere)
	float MoveScale;

	UPROPERTY(EditAnywhere)
	float RotateScale;

	class AMissionPlayerController* MPC;
	*/
};
