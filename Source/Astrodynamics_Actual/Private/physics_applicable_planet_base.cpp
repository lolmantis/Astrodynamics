// Fill out your copyright notice in the Description page of Project Settings.


#include "physics_applicable_planet_base.h"
#include "Components/SplineComponent.h"

// Sets default values
Aphysics_applicable_planet_base::Aphysics_applicable_planet_base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//manually defining root component to avoid nullptr
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = RootComp;

	//creating sphere & mesh
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Default Mesh"));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Engine/BasicShapes/Sphere"));
	SphereMesh->SetupAttachment(RootComponent);
	
	//instancing Orbit Path
	OrbitPath = CreateDefaultSubobject<USplineComponent>(TEXT("OrbitPath"));
	OrbitPath->SetupAttachment(RootComponent);

	//spline comes with two points initially, we need to remove these for the system to function correctly
	OrbitPath->RemoveSplinePoint(0, true);
	OrbitPath->RemoveSplinePoint(0, true);

	if (MeshObj.Object) {
		SphereMesh->SetStaticMesh(MeshObj.Object);
	};

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
	//distance += (DeltaTime * OrbitSpeed);
	
	/*FTransform transform = OrbitPath->GetTransformAtDistanceAlongSpline(distance, ESplineCoordinateSpace::Local, false);
	FVector CurrentLocation = FVector(transform.GetLocation().X,transform.GetLocation().Y, 0);
	FTransform move = FTransform(FRotator::ZeroRotator,CurrentLocation,FVector::OneVector);
	float test = move.GetLocation().X;
	GEngine->AddOnScreenDebugMessage(-1,1.0,FColor::Red,*FString::SanitizeFloat(distance));
	SetActorRelativeTransform(move);
	FTransform translation = GetActorTransform();
	

	if (distance >= OrbitPath->GetSplineLength())
	{
		distance = 0;
	}*/
}

UStaticMeshComponent* Aphysics_applicable_planet_base::GetMesh()
{
	return Cast<UStaticMeshComponent>(GetComponentByClass(UStaticMeshComponent::StaticClass()));
}

bool Aphysics_applicable_planet_base::setMaterial(UMaterialInstance* surface_texture)
{
	UStaticMeshComponent* mesh = GetMesh();
	mesh->SetMaterial(0, surface_texture);
	if (mesh->GetMaterial(0) == surface_texture) {
		return true;
	}
	return false;
}