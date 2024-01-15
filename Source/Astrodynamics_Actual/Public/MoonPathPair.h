// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "MoonPathPair.generated.h"


USTRUCT(BlueprintType)
struct ASTRODYNAMICS_ACTUAL_API FMoonPathPair
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Moon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USplineComponent* Path;
};

