// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Public/Tank.h"


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* CurrentTank = GetControlledTank();
	if (CurrentTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled tank: %s"), *CurrentTank->GetName());
	} 
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NO CONTROLLED TANK"));
	}
}
