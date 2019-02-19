// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankBarrel.h"
#include "Engine/World.h"
#include "Public/TankTurret.h"
#include "Engine/StaticMeshSocket.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1); //Clamp input

	float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
	float RawNewElevation = FMath::Clamp<float>(RelativeRotation.Pitch + ElevationChange, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(RawNewElevation, 0, 0));
	
}



