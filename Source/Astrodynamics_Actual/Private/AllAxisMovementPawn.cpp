// Fill out your copyright notice in the Description page of Project Settings.


#include "AllAxisMovementPawn.h"
#include "MissionPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "../../../../../../../../Program Files/Epic Games/UE_5.2/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../../../../../../../../Program Files/Epic Games/UE_5.2/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AAllAxisMovementPawn::AAllAxisMovementPawn()
{
	/*
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);

	//spring arm redundant for this system
	//SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	//SpringArm->SetupAttachment(Sphere);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Sphere);
	//keeping redundant system as a reference for how spring arms should be set up
	// Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	MoveScale = 1.f;
	RotateScale = 50.f;
	//bRMB = false;
	*/
}
/*
// Called to bind functionality to input
void AAllAxisMovementPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	MPC = Cast<AMissionPlayerController>(Controller);
	check(EIC && MPC);
	EIC->BindAction(MPC->MoveAction, ETriggerEvent::Triggered, this, &AAllAxisMovementPawn::Move);
	EIC->BindAction(MPC->RotateAction, ETriggerEvent::Triggered, this, &AAllAxisMovementPawn::Rotate);

	ULocalPlayer* LocalPlayer = MPC->GetLocalPlayer();
	check(LocalPlayer);
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(MPC->PawnMappingContext, 0);
}

void AAllAxisMovementPawn::Move(const FInputActionValue& ActionValue)
{
	FVector Input = ActionValue.Get<FInputActionValue::Axis3D>();
	//scales input with DeltaTime for the frame
	AddMovementInput(GetActorRotation().RotateVector(Input), MoveScale);
}

void AAllAxisMovementPawn::Rotate(const FInputActionValue& ActionValue)
{
	FRotator Input(ActionValue[0], ActionValue[1], ActionValue[2]);
	Input *= GetWorld()->GetDeltaSeconds() * RotateScale;
	//AddActorLocalRotation(Input);
	Input += GetActorRotation();
	Input.Pitch = FMath::ClampAngle(Input.Pitch, -89.9f, 89.9f);
	Input.Roll = 0;
	SetActorRotation(Input);
	MPC->SnapMouseToCenter(MPC);
}
*/