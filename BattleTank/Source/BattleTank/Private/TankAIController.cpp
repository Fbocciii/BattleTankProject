// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Public/Tank.h"

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ATank* CurrentTank = GetControlledTank();

	if (CurrentTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank: %s"), *CurrentTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NO AI TANK FOUND"));
	}
}

