// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* SphereMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USplineComponent* OrbitPath;

	UStaticMeshComponent* GetMesh();

	/** Sets sphere material*/
	UFUNCTION(BlueprintCallable)
		bool setMaterial(UMaterialInstance* texture);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float OrbitSpeed;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//float
};

