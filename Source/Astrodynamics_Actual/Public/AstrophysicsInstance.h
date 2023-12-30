// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AstrophysicsInstance.generated.h"

/**
 * 
 */
UCLASS()
class ASTRODYNAMICS_ACTUAL_API UAstrophysicsInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
};
