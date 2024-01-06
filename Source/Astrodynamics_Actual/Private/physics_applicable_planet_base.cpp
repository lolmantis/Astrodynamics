// Fill out your copyright notice in the Description page of Project Settings.


#include "physics_applicable_planet_base.h"
//#include "Components/SplineComponent.h"

// Sets default values
Aphysics_applicable_planet_base::Aphysics_applicable_planet_base()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//manually defining root component to avoid nullptr
	RootComp = CreateDefaultSubobject<USceneComponent>("SceneComp");
	RootComponent = RootComp;

	PlanetRoot = CreateDefaultSubobject<UStaticMeshComponent>("PlanetRoot");
	PlanetRoot->SetupAttachment(RootComponent);

	//creating sphere & mesh
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>("DefaultMesh");
	//const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Engine/BasicShapes/Sphere"));
	SphereMesh->SetupAttachment(PlanetRoot);
	
	//instancing Orbit Path
	OrbitPath = CreateDefaultSubobject<USplineComponent>("OrbitPath");
	OrbitPath->SetupAttachment(RootComponent);

	//spline comes with two points initially, we need to remove these for the system to function correctly
	OrbitPath->RemoveSplinePoint(0, true);
	OrbitPath->RemoveSplinePoint(0, true);

	/*if (MeshObj.Object) {
		SphereMesh->SetStaticMesh(MeshObj.Object);
	};*/

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

UStaticMeshComponent* Aphysics_applicable_planet_base::GetMesh()
{
	return Cast<UStaticMeshComponent>(GetComponentByClass(UStaticMeshComponent::StaticClass()));
}

bool Aphysics_applicable_planet_base::setMaterial(UMaterialInstance* surface_texture)
{
	SphereMesh->SetMaterial(0, surface_texture);
	if (SphereMesh->GetMaterial(0) == surface_texture) {
		return true;
	}
	return false;
}
float Aphysics_applicable_planet_base::GetRadiusMeters()
{
	FVector Scale = SphereMesh->GetComponentScale();
	float Radius = Scale.X;
	return Radius;
}
FVector Aphysics_applicable_planet_base::GetPlanetWorldLoc()
{
	return PlanetRoot->GetComponentLocation();
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
		double mass = Body->Data.Mass * pow(10, 24);
		double Force = (mass * MyMassActual) / dist;
		FVector ForceVect = Force * Direction;
		//FVector Force = UGeneralHelpFunctions::ForceAonB(mass, MyMass, Body, PlanetRoot) * DeltaSeconds; //  || test this to see if you need to multiply by delta seconds to get accurate timesteps
		
		PlanetRoot->AddImpulse(ForceVect, NAME_None, true);
	};
};