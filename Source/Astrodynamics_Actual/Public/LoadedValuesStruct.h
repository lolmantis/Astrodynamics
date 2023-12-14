// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"
#include "LoadedValuesStruct.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType, category = "initials")
struct ASTRODYNAMICS_ACTUAL_API FLoadedValuesStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText BodyType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInstance* SurfaceTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Mass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ERelMass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ERelRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector WorldPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FVector> SplineMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString CentralStar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsMoon;


	FLoadedValuesStruct() 
	{
		WorldPos = FVector::ZeroVector;
		Name = FText::FromString("NULL");
		BodyType = FText::FromString("NULL");
		SurfaceTexture = NULL;
		Mass = 0.0;
		ERelMass = 0.0;
		Radius = 1;
		ERelRadius = 1.0;
		SplineMap;
		CentralStar = NULL;
		bIsMoon = false;
	}
};