// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"
//#include <physics_applicable_planet_base.h>
#include "Math/UnrealMathUtility.h"
#include "GeneralHelpFunctions.generated.h"

/**
 * 
 */

UENUM(BlueprintType, category = "macros|variables")
enum class ESaveType : uint8 {
	ST_System UMETA(DisplayName="System"),
	ST_Spacecraft UMETA(DisplayName = "Spacecraft"),
	ST_Planet UMETA(DisplayName = "Planet"),
	ST_Mission UMETA(DisplayName = "Mission")
};

UCLASS()
class ASTRODYNAMICS_ACTUAL_API UGeneralHelpFunctions : public UObject
{

	GENERATED_BODY()

protected:
	
	UPROPERTY()
	float GravityConst = 6.6743e-11f;

public:
	UGeneralHelpFunctions();
	~UGeneralHelpFunctions();

	UFUNCTION(BlueprintCallable, BlueprintPure, category="macros|functions")
	static TArray<FString> GetTypeSpecificSaves(TArray<FString> Saves, ESaveType Type);

	/*rotates spring arm with delta seconds against mouse deltaXY, mouse left = rotate right, mouse up = rotate down*/
	UFUNCTION(BlueprintCallable, BlueprintPure, category="macros|functions")
	static void RotateSpringArm(const APlayerController* controller, const FRotator currentrot,
		FRotator& ArmWorldRotation
		);

	/*returns the period of a given orbit in years as standard, you'll have to convert to days later down the line if needed*/
	UFUNCTION(BlueprintCallable, BlueprintPure, category="astrophysics|functions")
	static UPARAM(DisplayName = "period (years)") double KeplerThirdLaw(const float SemiMajorAxisM, const float CentralBodyMass, const float SecondBodyMass, const bool bIsParentSun);

	UFUNCTION(BlueprintPure,category="macros|functions")
	static TArray<FVector> GenerateSplineRing(float OrbitRadius, float OrbitTilt, float OrbitEllipse, int Complexity);

	UFUNCTION(BlueprintPure,category="astrophysics|functions")
	static FVector ForceAonB(const double MassPrimary, const double MassSecondary, const FVector Primary, const FVector Secondary);
};
