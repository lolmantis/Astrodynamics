// Fill out your copyright notice in the Description page of Project Settings.


#include "Spacecraft.h"

// Sets default values
ASpacecraft::ASpacecraft()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpacecraft::BeginPlay()
{
	Super::BeginPlay();
	Baseplate = GetComponentByClass<UPrimitiveComponent>();
	
}

void ASpacecraft::Initialiser(
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
	const TArray<FName>& IN_gyros)
{
	Name = IN_Name;
	FuelCapacity = IN_FuelCapacity;
	FuelCurrent = IN_FuelCapacity;
	BatteryCapacity = IN_BatteryCapacity;
	BatteryCurrent = IN_BatteryCapacity;
	DryMass = IN_DryMass;
	WetMass = IN_WetMass;
	crew = IN_crew;
	hull = IN_hull;
	thrusters = IN_Thrusters;
	reactors = IN_Reactors;
	ReactionWheels = IN_ReactionWheels;
	gyroscopes = IN_gyros;
}

void ASpacecraft::FuelPercentage(float& percent)
{
	percent = FuelCurrent / FuelCapacity;
}

void ASpacecraft::BatteryPercentage(float& percent)
{
	percent = BatteryCurrent / BatteryCapacity;
}

void ASpacecraft::OrbitInitialForce(const float OrbitRadiusMeters, const FVector OrbitDirection, const float PlanetMass, FVector& ForceVector)
	{
	double mass = PlanetMass * pow(10, 24); //noting that radius to planet is the CENTER of the planet
	double GM = GravityConstant * mass;
	double vel = FMath::Sqrt(GM / OrbitRadiusMeters);
	FVector directionNormalised = OrbitDirection.GetSafeNormal();
	ForceVector = directionNormalised * vel;
}

float ASpacecraft::StandardGravParam(const float& PrimaryMass, const float& SecondaryMass)
{
	return float ((GravityConstant * ((PrimaryMass * pow(10, 24)) + (SecondaryMass * pow(10, 24)))) / 1000);
}

void ASpacecraft::SemiImplicitEuler(const float DeltaSeconds, const TArray<Aphysics_applicable_planet_base*> Bodies, FVector& Force)
{
	for (Aphysics_applicable_planet_base* Body : Bodies)
	{
		double mass = Body->Data.Mass * pow(10, 24);
		FVector PlanetLoc = Body->GetPlanetWorldLoc();
		FVector TempForce = UGeneralHelpFunctions::ForceAonB(mass, 1, PlanetLoc, GetActorLocation()) * DeltaSeconds; //  scales force to the timestep (m/s**2 to m/s)
		Baseplate->AddImpulse(TempForce, NAME_None, true);
		Force += TempForce;
	};
}

void ASpacecraft::RocketEquation(const float& SpecificImpulse,const float& InitialMass,const float& FinalMass, float& Velocity)
{
	Velocity = SpecificImpulse * 9.8 * log(InitialMass / FinalMass);
}

float ASpacecraft::VisViva(const float& RadiusFromPrimary, const float& OrbitSemiMajorAxis, const float& StandardGravitationalParameter)
{
	float velocity = sqrt(StandardGravitationalParameter * ((2 / RadiusFromPrimary) - (1 / OrbitSemiMajorAxis)));
	return velocity; // equation relating velocity, gravity, and distance, it comes in handy just about everywhere physics related
}

void ASpacecraft::Hohmann(
	const int32& PrimaryOrbitRadius, const int32& SecondaryOrbitRadius,
	const float& PrimaryMassActual, const float& SecondaryMassActual, 
	float& TrnsfrSemiMjrAxis, float& TrnsfrSemiMinrAxis,
	float& PeriapsisVel, float& ApoapsisVel,
	float& FirstDeltaV, float& FinalDeltaV,
	float& TotalDeltaV)
{
	// Standard Gravity Parameter that sees use throughout, simple one liner gets the job done
	double StandardGravitationalParameter = StandardGravParam(PrimaryMassActual,SecondaryMassActual); 
	//divided by 1000 to convert from m**3/s**2 to km**3/s**2

	float ParkedVel = VisViva(PrimaryOrbitRadius, PrimaryOrbitRadius, StandardGravitationalParameter);
	
	TrnsfrSemiMjrAxis = (PrimaryOrbitRadius + SecondaryOrbitRadius) / 2;
	TrnsfrSemiMinrAxis = sqrt((PrimaryOrbitRadius * SecondaryOrbitRadius));

	PeriapsisVel = VisViva(PrimaryOrbitRadius, TrnsfrSemiMjrAxis, StandardGravitationalParameter);
	ApoapsisVel = VisViva(SecondaryOrbitRadius, TrnsfrSemiMjrAxis, StandardGravitationalParameter);

	float TargetVel = VisViva(SecondaryOrbitRadius, SecondaryOrbitRadius, StandardGravitationalParameter);

	FirstDeltaV = PeriapsisVel - ParkedVel;
	FinalDeltaV = TargetVel - ApoapsisVel;
	TotalDeltaV = FirstDeltaV + FinalDeltaV;

}

void ASpacecraft::BiElliptic(
	const int32& InitialOrbitRadius, const int32& TargetOrbitRadius, const int32& transferMagnitude, 
	const float& PrimaryMassActual, const float& SecondaryMassActual,
	float& ApogeeRad, float& TransferApogee1, float& TransferApogee2,
	float& TransferSemiMjrAxs1, float& TransferSemiMjrAxs2,
	float& DeltaV1, float& DeltaV2, float& DeltaV3, float& DeltaVT)
{
	// quick shorthand for standard grav param, pre-calced values exist, but it's quicker to just do the math here and now then go looking them up for each planet/moon/etc
	float StandardGravitationalParameter = StandardGravParam(PrimaryMassActual,SecondaryMassActual);

	TransferSemiMjrAxs1 = ((TargetOrbitRadius * transferMagnitude) + InitialOrbitRadius) / 2;

	// velocity at midpoint of longest arc
	float TransferPeriapsis1 = VisViva(TargetOrbitRadius, TransferSemiMjrAxs1, StandardGravitationalParameter);

	// get velocity and scale from Unreal units of cm/s to m/s then get DeltaV for first transfer orbit
	UE::Math::TVector<double> CurrentVelocity = GetVelocity()/100; // note: this gets current velocity, not the velocity you need for the maneuver
	/*what I mean by that is that at the point of the periapsis, you need THAT velocity, but you're getting whatever velocity you have at  that instant*/
	DeltaV1 = (TransferPeriapsis1 * 2) -sqrt(pow(CurrentVelocity.X,2) + pow(CurrentVelocity.Y,2) + pow(CurrentVelocity.Z,2));

	// and now for the second transfer ellipse
	ApogeeRad = (TransferSemiMjrAxs1 * 2) -InitialOrbitRadius;
	TransferSemiMjrAxs2 = ((2 * TransferSemiMjrAxs1) + (TargetOrbitRadius - InitialOrbitRadius)) / 2;

	// calc velocities of the two transfer orbits
	TransferApogee1 = VisViva(ApogeeRad, TransferSemiMjrAxs1, StandardGravitationalParameter);
	TransferApogee2 = VisViva(ApogeeRad, TransferSemiMjrAxs2, StandardGravitationalParameter);

	/*
	   essentially, in a bi - elliptic you burn hard to get really far away, then burn a little to change the other end to be where you want the new orbit to be
	   hence why the second delta V is second orbit - first orbit, the second will always be slightly larger
	   and if you're wondering what if the second transfer is smaller, you would be doing a Hohmann not a bi-elliptic in that case so we don't need to calc it
	*/
	DeltaV2 = TransferApogee2 - TransferApogee1;

	// now for third insertion burn
	float TransferPeriapsis2 = VisViva(StandardGravitationalParameter, TargetOrbitRadius, TransferSemiMjrAxs2);
	float TargetOrbitVel = VisViva(StandardGravitationalParameter, TargetOrbitRadius, TransferSemiMjrAxs1);
	DeltaV3 = TargetOrbitVel - TransferPeriapsis2;
	// for the budget to calc if viable
	DeltaVT = DeltaV1 + DeltaV2 + DeltaV3;
}

// Called every frame
void ASpacecraft::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpacecraft::HohmannMoreEfficient(const float InitialOrbitRadius, const float FinalOrbitRadius, const float Apoapsis, bool& bHohmannEfficient, float& BiEllipticPreference)
{
	float OrbitRatio = FinalOrbitRadius / InitialOrbitRadius;
	if (OrbitRatio < 11.34f)
	{
		bHohmannEfficient = true;
	}
	else if (OrbitRatio > 15.56f)
	{
		bHohmannEfficient = false;
	};
	BiEllipticPreference = Apoapsis / InitialOrbitRadius;

	//return false;
}

float ASpacecraft::TransferSemiMajorAxis(const float InitialOrbitRadius, const float FinalOrbitRadius)
{
	return (InitialOrbitRadius+FinalOrbitRadius)/2;
}

FVector ASpacecraft::InterceptPosition(const FVector InitialPosition, const FVector TargetBodyLocation, const FVector TargetOrbitRadius)
{
	return (TargetBodyLocation + TargetOrbitRadius) - InitialPosition;
}

/*This only exists because I didn't want to have to build a function in blueprint to get all the craft component arrays, this means I can get the array quickly
and the blueprint just has to handle the mass part with a switch statement, a win win in my books*/
TArray<FName> ASpacecraft::ArrayAllComponents(FName NHull, TArray<FName> NThrusters, TArray<FName> NReactors, TArray<FName> NReactionWheels, TArray<FName> NGyroscopes)
{
	TArray<FName> Array;
	Array.Add(NHull);
	Array.Append(NReactors);
	Array.Append(NThrusters); // reverse this to be the order you want them displayed
	Array.Append(NReactionWheels);
	Array.Append(NGyroscopes);
	return Array;
};