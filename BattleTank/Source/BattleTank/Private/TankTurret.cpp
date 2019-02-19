// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	//Rotate turret based on degrees passed 
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1); //Clamp input

	float RotationChange = RelativeSpeed * MaxRotationSpeed * GetWorld()->GetDeltaSeconds();
	float Rotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, Rotation, 0));

	//UE_LOG(LogTemp, Warning, TEXT("Relative speed: %f  Rotation Change: %f  Current turret rotation: %f"),RelativeSpeed, RotationChange, Rotation);
}
