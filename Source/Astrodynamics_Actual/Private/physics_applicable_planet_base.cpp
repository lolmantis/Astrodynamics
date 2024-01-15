// Fill out your copyright notice in the Description page of Project Settings.


#include "physics_applicable_planet_base.h"
//#include "Components/SplineComponent.h"

// Sets default values
Aphysics_applicable_planet_base::Aphysics_applicable_planet_base()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//manually defining root component to avoid nullptr
	RootComp = CreateDefaultSubobject<USceneComponent>("SceneComp");
	RootComponent = RootComp;

	PlanetRoot = CreateDefaultSubobject<UStaticMeshComponent>("PlanetRoot");
	PlanetRoot->SetupAttachment(RootComponent);

	//creating sphere & mesh
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>("DefaultMesh");
	SphereMesh->SetupAttachment(PlanetRoot);
	
	//instancing Orbit Path
	OrbitPath = CreateDefaultSubobject<USplineComponent>("OrbitPath");
	OrbitPath->SetupAttachment(RootComponent);

	//spline comes with two points initially, we need to remove these for the system to function correctly
	OrbitPath->RemoveSplinePoint(0, true);
	OrbitPath->RemoveSplinePoint(0, true);

	OrbitSpeed = 1000.0;
	distance = 0.0; //for moving actor along spline
}

// Called when the game starts or when spawned
void Aphysics_applicable_planet_base::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void Aphysics_applicable_planet_base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UStaticMeshComponent* Aphysics_applicable_planet_base::GetMesh() const
{
	return SphereMesh;
}

bool Aphysics_applicable_planet_base::setMaterial(UMaterialInstance* surface_texture)
{
	SphereMesh->SetMaterial(0, surface_texture);
	if (SphereMesh->GetMaterial(0) == surface_texture) {
		return true;
	}
	return false;
}
float Aphysics_applicable_planet_base::GetRadiusMeters() const
{
	FVector Scale = SphereMesh->GetComponentScale();
	float Radius = Scale.X;
	return Radius;
}
FVector Aphysics_applicable_planet_base::GetPlanetWorldLoc() const
{
	return PlanetRoot->GetComponentLocation();
}

FVector Aphysics_applicable_planet_base::GetPlanetWorldVel() const
{
	return SphereMesh->GetComponentVelocity();
}

FVector Aphysics_applicable_planet_base::SetAngularRotation(float Period)
{
	double time = Period * 3600;
	double Radians = 2 * PI;
	FVector force (0,0,0);
	force.Y = Radians/time;
	SphereMesh->AddAngularImpulseInRadians(force,NAME_None,true); 
	return SphereMesh->GetPhysicsAngularVelocityInRadians();
}

void Aphysics_applicable_planet_base::OrbitInitialForce(const float RadiusToPlanetCenter, const FVector OrbitDirection, const float PlanetMass, FVector& ForceVector)
{
	double mass = PlanetMass * pow(10, 24); //noting that radius to planet is the CENTER of the planet
	double GM = 6.6743e-11f * mass; // gravity constant as literal value, we don't need to define it as a constant because spacecraft already does that
	double radius = RadiusToPlanetCenter;
	double vel = FMath::Sqrt(GM / radius);
	FVector directionNormalised = OrbitDirection.GetSafeNormal();
	ForceVector = directionNormalised * vel;
}
void Aphysics_applicable_planet_base::SemiImplicitEuler(const float DeltaSeconds, const TArray<Aphysics_applicable_planet_base*> Bodies)
{
	for (Aphysics_applicable_planet_base* Body : Bodies)
	{
		if (Body == this) {
			continue;
		};
		double R = GetDistanceTo(Body);
		FVector Direction = Body->GetPlanetWorldLoc() - GetPlanetWorldLoc();
		double dist = Direction.SquaredLength();
		Direction.Normalize();
		double Mass = Body->Data.Mass * pow(10, 24);
		double MyMass = Data.Mass * pow(10, 24);
		double Force = 6.6743e-11f*(Mass * MyMass) / dist;
		double Accel = Force / MyMass;
		double Vel = Accel * DeltaSeconds;
		FVector ForceVect = Vel * Direction;
		//FVector Force = UGeneralHelpFunctions::ForceAonB(mass, MyMass, Body, PlanetRoot) * DeltaSeconds;
		
		PlanetRoot->AddImpulse(ForceVect, NAME_None, true);
	};
};