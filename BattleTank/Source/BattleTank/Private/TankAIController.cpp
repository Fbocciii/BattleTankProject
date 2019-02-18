// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Public/Tank.h"
#include "Engine/World.h"

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerControlledTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	CurrentTank = GetControlledTank();
	PlayerTank = GetPlayerControlledTank();

	if (CurrentTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank: %s"), *CurrentTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NO AI TANK FOUND"));
	} 

	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Tank: %s"), *PlayerTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NO PLAYER TANK FOUND"));
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentTank)
	{
		if (PlayerTank)
		{
			CurrentTank->AimAt(PlayerTank->GetTargetLocation());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("%s has no player to aim at!"), *CurrentTank->GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no tank attached!"), *GetName());
	}
}

