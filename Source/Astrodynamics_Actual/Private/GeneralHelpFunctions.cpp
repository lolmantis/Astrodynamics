// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralHelpFunctions.h"

UGeneralHelpFunctions::UGeneralHelpFunctions()
{
}

UGeneralHelpFunctions::~UGeneralHelpFunctions()
{
}

TArray<FString> UGeneralHelpFunctions::GetTypeSpecificSaves(TArray<FString> Saves, ESaveType type)
{
	FString prefix;
	switch (type) {
	case(ESaveType::ST_System):
		prefix = "SYST_";
		break;
	case(ESaveType::ST_Spacecraft):
		prefix = "CRFT_";
		break;
	case(ESaveType::ST_Planet):
		prefix = "PLNT_";
		break;
	case(ESaveType::ST_Mission):
		prefix = "MISN_";
		break;
	}
	int32 max = Saves.Num();

	TArray<FString> NewSaveArray;

	for (int i = 0; i<max; i++) {
		if (Saves[i].StartsWith(prefix)) {
			NewSaveArray.Add(Saves[i]);
		}
	}

	return NewSaveArray;
}

void UGeneralHelpFunctions::RotateSpringArm(const APlayerController* controller, const FRotator currentrot,
	FRotator& ArmWorldRotation)
{
	float DeltaX; float DeltaY;
	controller->GetInputMouseDelta(DeltaX,DeltaY);
	float ChangeY = currentrot.Pitch + DeltaY;
	float ChangeX = currentrot.Yaw + DeltaX;
	ChangeY = FMath::Clamp(ChangeY, -89.9f, 89.9f);
	ArmWorldRotation.Pitch = ChangeY; ArmWorldRotation.Yaw = ChangeX;
}

double UGeneralHelpFunctions::KeplerThirdLaw(const float SemiMajorAxisM, const float CentralBodyMass, const float SecondBodyMass, const bool bIsParentSun)
{
	if (bIsParentSun)
	{
		double a3 = FMath::Pow((SemiMajorAxisM / 1.496e+11), 3);
		double P = FMath::Sqrt(a3); // P2=A3
		return P;
	};
	double CentralMKg = CentralBodyMass * pow(10, 24); //counting in kilograms
	double SecondMKg = SecondBodyMass * pow(10, 24);
	double a3Meters = pow((SemiMajorAxisM),3); //counting in meters cubed
	double TotalMass = CentralMKg + SecondMKg;
	double GM = 6.6743e-11 * (CentralMKg+SecondMKg);
	double K = (4.0f * PI * PI) / GM;
	double P2 = K * a3Meters;
	double PSec =  FMath::Sqrt(P2); // seconds
	return PSec / 31536000.0; // converts to years
}

TArray<FVector> UGeneralHelpFunctions::GenerateSplineRing(float OrbitRadius, float OrbitTilt, float OrbitEllipse, int Complexity)
{
	int sections = 6;
	Complexity = FMath::Clamp(Complexity, 2, 12);
	int length = sections * Complexity;
	float AngleUnit = sections * 10;
	// note: angle units are in degrees up to sin/cos funcs, where they're swapped for their radian counterparts
	float Increment = AngleUnit / Complexity;
	TArray<FVector> SplinePoints;
	for (int i = 1; i < (length+1); i++)
	{
		float WayAlongCircle = i * Increment;
		FVector CurrentPoint;
		WayAlongCircle = FMath::DegreesToRadians(WayAlongCircle);
		CurrentPoint.X = FMath::Sin(WayAlongCircle) * (2 - OrbitEllipse) * OrbitRadius;
		float DistAlong = FMath::Cos(WayAlongCircle);
		CurrentPoint.Y = DistAlong * OrbitEllipse * OrbitRadius;
		CurrentPoint.Z = DistAlong * OrbitTilt * OrbitRadius;
		SplinePoints.Add(CurrentPoint);
	}

	return SplinePoints;
}

FVector UGeneralHelpFunctions::ForceAonB(const double MassA, const double MassB, const FVector A, const FVector B)
{
	FVector VectDirect = A - B;
	double distancesqrd = VectDirect.SquaredLength();
	// picture it as a planet (A) attracting a spacecraft (B) towards it
	VectDirect.Normalize();
	// returns the unit vector pointing between the two
	
	double force = ((MassA * MassB) / (distancesqrd)) * 6.6743e-11;
	/* note that force is directionless at this point,
	*  quick explanation for why it's distance squared and not distance cubed given we're multiplying by radius again;
	*  we're using the unit vector which has a |magnitude| of 1, which doesn't affect the calculation
	*/
	return (VectDirect * force);
	// scales unit vector pointing from B to A up to the force required
	
}