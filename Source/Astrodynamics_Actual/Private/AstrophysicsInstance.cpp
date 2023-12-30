// Fill out your copyright notice in the Description page of Project Settings.


#include "AstrophysicsInstance.h"

void UAstrophysicsInstance::Init()
{
	Super::Init();
	if (GEngine)
	{
		GEngine->Exec(GetWorld(), TEXT("show splines"));
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("GameInstance Setup Complete"));
}
