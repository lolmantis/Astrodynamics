// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralHelpFunctions.h"
#include "Math/Vector.h"
#include "physics_applicable_planet_base.h"
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

	UPrimitiveComponent* Baseplate;

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

	UFUNCTION(BlueprintPure, category = "spacecraft | functions")
		void FuelPercentage(float& percent);

	UFUNCTION(BlueprintPure, category = "spacecraft | functions")
		void BatteryPercentage(float& percent);

	UFUNCTION(BlueprintPure, category = "spacecraft | astrophysics | functions")
		void OrbitInitialForce(const float OrbitRadiusMeters, const FVector OrbitDirection, const float PlanetMass, FVector& ForceVector);

	UFUNCTION(BlueprintPure, category = "spaceacraft | astrophysics | functions")
		float StandardGravParam(const float& PrimaryMass, const float& SecondaryMass);

	UFUNCTION(BlueprintCallable, category = "spacecraft | astrophysics | functions")
		void SemiImplicitEuler(const float DeltaSeconds, const TArray<Aphysics_applicable_planet_base*> Bodies, FVector& Force);

	// calculates Delta V for a given maneuver, or can be used for the full deltaV budget
	UFUNCTION(BlueprintCallable, category = "spacecraft | astrophysics | functions")
		void RocketEquation(const float& SpecificImpulse, const float& InitialMass,const float& FinalMass, float& velocity);

	// calculates velocity of a given orbit, very useful in getting Delta V for Hohmann maneuvers
	UFUNCTION(BlueprintPure, category = "spacecraft | astrophysics | functions")
	UPARAM(DisplayName="force in m/s")
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
		/*
		* a hohmann transfer between two orbits (they need to be circular and co-planar, though)
		*/

	UFUNCTION(BlueprintCallable, category = "spacecraft | astrophysics | functions")
		void BiElliptic(
			const int32& InitialOrbitRadius, const int32& TargetOrbitRadius, const int32& transferMagnitude,
			const float& PrimaryMassActual, const float& SecondaryMassActual,
			float& ApogeeRad, float& TransferApogee1, float& TransferApogee2,
			float& TransferSemiMjrAxs1, float& TransferSemiMjrAxs2,
			float& DeltaV1, float& DeltaV2, float& DeltaV3, float& DeltaVT
		);
	/*
	* a bielliptical transfer between two orbits, same conditions as a hohmann
	*/

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintPure, category = "spacecraft | astrophysics | functions")
		void HohmannMoreEfficient(const float InitialOrbitRadius, const float FinalOrbitRadius, const float Apoapsis,
			bool& bHohmannEfficient, float& BiEllipticPreference);

	UFUNCTION(BlueprintCallable, category = "spacecraft | astrophysics | functions")
	UPARAM(DisplayName = "Transfer Semi Major Axis")
		float TransferSemiMajorAxis(const float InitialOrbitRadius, const float FinalOrbitRadius);

	UFUNCTION(BlueprintPure, category = "spacecraft | astrophysics | functions")
	UPARAM(DisplayName="Destination Worldspace Position")
		FVector InterceptPosition(const FVector InitialPosition, const FVector TargetBodyLocation, const FVector TargetOrbitRadius);

	UFUNCTION(BlueprintPure, category = "spacecraft | functions")
	UPARAM(DisplayName="All components")
		TArray<FName> ArrayAllComponents(FName NHull, TArray<FName> NThrusters, TArray<FName> NReactors, TArray<FName> NReactionWheels, TArray<FName> NGyroscopes);

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