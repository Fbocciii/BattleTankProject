// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Public/Tank.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	CurrentTank = Cast<ATank>(GetPawn());
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentTank)
	{
		if (PlayerTank)
		{
			MoveToActor(PlayerTank, 100.0f);

			CurrentTank->AimAt(PlayerTank->GetTargetLocation());

			CurrentTank->Fire();
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

