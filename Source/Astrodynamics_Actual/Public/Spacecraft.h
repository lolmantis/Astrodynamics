// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <cmath>
#include "GameFramework/Actor.h"
#include "Spacecraft.generated.h"

UCLASS()
class ASTRODYNAMICS_ACTUAL_API ASpacecraft : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpacecraft();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, category = "spacecraft | astrophysics | variables")
	float GravityConstant = 6.6743e-11f;

	UFUNCTION(BlueprintCallable, category = "spacecraft | functions")
	void Initialiser(
		const FString& IN_Name,
		const float& IN_FuelCapacity,
		const float& IN_BatteryCapacity,
		const float& IN_DryMass,
		const float& IN_WetMass,
		const int32& IN_crew,
		const FName& IN_hull,
		const TArray<FName>& IN_Thrusters,
		const TArray<FName>& IN_Reactors,
		const TArray<FName>& IN_ReactionWheels,
		const TArray<FName>& IN_gyros
	);

	UFUNCTION(BlueprintPure, BlueprintCallable, category = "spacecraft | functions")
		void FuelPercentage(float& percent);

	UFUNCTION(BlueprintPure, BlueprintCallable, category = "spacecraft | functions")
		void BatteryPercentage(float& percent);

	// calculates Delta V for a given maneuver, or can be used for the full deltaV budget
	UFUNCTION(BlueprintCallable, category = "spacecraft | astrophysics | functions")
		void RocketEquation(const float& SpecificImpulse, const float& InitialMass,const float& FinalMass, float& velocity);

	// calculates velocity of a given orbit, very useful in getting Delta V for Hohmann maneuvers
	UFUNCTION(BlueprintCallable, category = "spacecraft | astrophysics | functions")
	float VisViva(const float& RadiusFromPrimary, const float& OrbitSemiMajorAxis, const float& StandardGravitationalParameter);

	/* calculates delta V required for a given hohmann transfer, also provides:
	* semi major axis of transfer orbit, periapsis velocity, apoapsis velocity
	* 
	*/
	UFUNCTION(BlueprintCallable, category = "spacecraft | astrophysics | functions")
		void Hohmann(
			const int32& PrimaryOrbitRadius, const int32& SecondaryOrbitRadius,
			const float& PrimaryMassActual, const float& SecondaryMassActual,
			float& TrnsfrSemiMjrAxis, float& TrnsfrSemiMinrAxis,
			float& PeriapsisVel, float& ApoapsisVel,
			float& FirstDeltaV, float& FinalDeltaV,
			float& TotalDeltaV
		);

	UFUNCTION(BlueprintCallable, category = "spacecraft | astrophysics | functions")
	void BiElliptic(
		const int32& InitialOrbitRadius, const int32& TargetOrbitRadius, const int32& transferMagnitude,
		const float& PrimaryMassActual, const float& SecondaryMassActual,
		float& ApogeeRad, float& TransferApogee1, float& TransferApogee2,
		float& TransferSemiMjrAxs1, float& TransferSemiMjrAxs2,
		float& DeltaV1, float& DeltaV2, float& DeltaV3, float& DeltaVT);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintPure, category = "spacecraft | astrophysics | functions")
	void HohmannMoreEfficient(const float InitialOrbitRadius, const float FinalOrbitRadius, const float Apoapsis,
		bool& bHohmannEfficient, float& BiEllipticPreference);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "spacecraft | variables")
		FString Name;

	// measured in tons || volume of hydrazine fuel in meters cubed (m**3), note: 1 meter cubed of hydrazine = 0.795 tons of hydrazine
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "spacecraft | variables")
		float FuelCapacity;

	// measured in tons, used in calculating force required to move fuel
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "spacecraft | variables")
		float FuelCurrent;

	// measured in milliamp hours (mAH)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "spacecraft | variables")
		float BatteryCapacity;

	// measured in milliamp hours (mAH), works in tandem with reactor component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "spacecraft | variables")
		float BatteryCurrent;

	// mass of the spacecraft when all fuel has been expended
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "spacecraft | astrophysics | variables")
		float DryMass;

	// mass of spacecraft at launch, with full fuel load
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "spacecraft | astrophysics | variables")
		float WetMass;

	// total DeltaV available for maneuvers
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "spacecraft | astrophysics | variables")
		float DeltaVBudget;

	// number of people on board for crew-related tasks
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "spacecraft | variables")
		int32 crew;

	UPROPERTY(editAnywhere, BlueprintReadWrite, category = "spacecraft | components")
		FName hull;

	UPROPERTY(editAnywhere, BlueprintReadWrite, category = "spacecraft | components")
		TArray<FName> thrusters;

	UPROPERTY(editAnywhere, BlueprintReadWrite, category = "spacecraft | components")
		TArray<FName> reactors;

	UPROPERTY(editAnywhere, BlueprintReadWrite, category = "spacecraft | components")
		TArray<FName> ReactionWheels;

	UPROPERTY(editAnywhere, BlueprintReadWrite, category = "spacecraft | components")
		TArray<FName> gyroscopes;
};