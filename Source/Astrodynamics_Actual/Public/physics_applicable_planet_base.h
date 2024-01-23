// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GeneralHelpFunctions.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "LoadedValuesStruct.h"
#include "MoonPathPair.h"
#include "physics_applicable_planet_base.generated.h"

UCLASS(Blueprintable)
class ASTRODYNAMICS_ACTUAL_API Aphysics_applicable_planet_base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Aphysics_applicable_planet_base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USceneComponent* RootComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float distance;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FLoadedValuesStruct Data;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* PlanetRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* SphereMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USplineComponent* OrbitPath;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USpringArmComponent* Stabiliser;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<Aphysics_applicable_planet_base*> Moons;


	UStaticMeshComponent* GetPlanet() const;

	/** Sets sphere material*/
	UFUNCTION(BlueprintCallable)
	UPARAM(DisplayName="Success")
		bool setMaterial(UMaterialInstance* texture);

	UFUNCTION(BlueprintPure, category="planets | functions")
	UPARAM(DisplayName="Planet Radius")
		float GetRadiusMeters() const;

	UFUNCTION(BlueprintPure, category="planets | functions")
	UPARAM(DisplayName="World Location")
		FVector GetPlanetWorldLoc() const;

	UFUNCTION(BlueprintPure, category="planets | astrophysics | functions")
	UPARAM(DisplayName="Force Vector")
		FVector GetPlanetWorldVel() const;

	/** Gets angular velocity of planet, takes period in hours*/
	UFUNCTION(BlueprintCallable, category="planets | astrophysics | functions")
	UPARAM(DisplayName = "Rad/sec")
		FRotator GetAngularRotation(float Period);

	UFUNCTION(BlueprintPure,category="planets | astrophysics | functions")
		void OrbitInitialForce(const float RadiusToPlanetCenter, const FVector OrbitDirection, const float PlanetMass, FVector& ForceVector);

	UFUNCTION(BlueprintCallable, category = "planets | astrophysics | functions")
		void SemiImplicitEuler(const float DeltaSeconds, const TArray<Aphysics_applicable_planet_base*> Bodies);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float OrbitSpeed;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, category = "planets | astrophysics | variables")
		float PeriodYears;
};