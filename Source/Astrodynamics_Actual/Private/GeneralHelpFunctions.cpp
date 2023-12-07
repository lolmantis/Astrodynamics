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

TArray<FVector> UGeneralHelpFunctions::GenerateSplineRing(float OrbitRadius, float OrbitTilt, float OrbitEllipse, int Complexity)
{
	int sections = 6;
	Complexity = FMath::Clamp(Complexity, 2, 6);
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

FVector UGeneralHelpFunctions::ForceAonB(const int MassA, const int MassB, const AActor* A, const AActor* B)
{
	float distance = A->GetDistanceTo(B);
	// make sure the world-scale is true to life, I don't really care how you do it
	FVector VectDirect = A->GetActorLocation() - B->GetActorLocation();
	// picture it as a planet (A) attracting a spacecraft (B) towards it
	VectDirect.Normalize();
	// returns the unit vector pointing between the two
	
	float force = ((static_cast<float>(MassA) * static_cast<float>(MassB)) / (distance * distance)) * 6.6743e-11f;
	// note that force is directionless at this point

	return VectDirect * force;
	// scales unit vector pointing from B to A up to the force required
	
}

/*void UGeneralHelpFunctions::SortArray(TArray<Aphysics_applicable_planet_base*>* Array)
{
	Array->Sort();
}*/
