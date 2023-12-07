// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CRFT_CMPNTS_Struct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType, category = "spacecraft")
struct ASTRODYNAMICS_ACTUAL_API FComponentStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, category = "spacecraft | main")
	FString Name;

	// measured in tons
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, category = "spacecraft | main")
	float FuelCapacity;

	// measured in tons, used in calculating force required to move fuel
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, category = "spacecraft | main")
	float FuelCurrent;

	// measured in milliamp hours (mAH)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, category = "spacecraft | main")
	float BatteryCapacity;

	// measured in milliamp hours (mAH), works in tandem with reactor component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, category = "spacecraft | main")
	float BatteryCurrent;

	// number of people on board for crew-related tasks
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, category = "spacecraft | main")
	int32 crew;

	// row name of relevant struct for hull
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, category = "spacecraft | struct row names")
	FName Hull;

	// row name of relevant struct for thruster
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, category = "spacecraft | struct row names")
	FName Thruster;

	// row name of relevant struct for reactor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, category = "spacecraft | struct row names")
	FName Reactor;

	// row name of relevant struct for reaction wheel
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, category = "spacecraft | struct row names")
	FName RWheel;

	// row name of relevant struct for gyroscope
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, category = "spacecraft | struct row names")
	FName Gyroscope;

	FComponentStruct()
	{
		Name = "";
		FuelCapacity = 0.0;
		FuelCurrent = 0.0;
		BatteryCapacity = 0.0;
		BatteryCurrent = 0.0;
		crew = 0;
		Hull = "";
		Thruster = "";
		Reactor = "";
		RWheel = "";
		Gyroscope = "";
	}
};