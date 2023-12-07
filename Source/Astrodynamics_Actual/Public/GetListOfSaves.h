// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GetListOfSaves.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, category = "initials")
class ASTRODYNAMICS_ACTUAL_API UGetListOfSaves : public UObject
{
	GENERATED_BODY()

public:
	UGetListOfSaves();
	~UGetListOfSaves();

	/** returns a list of all save games in /Saved/SaveGames folder, without the .sav extension (filename only) */
	UFUNCTION(BlueprintPure, Category = Game)
		static TArray<FString> GetAllSaveGameSlotNames();
};