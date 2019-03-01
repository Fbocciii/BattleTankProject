// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Engine/World.h"
#include "Public/TankAimingComponent.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	CurrentTank = (GetPawn());
	PlayerTank = (GetWorld()->GetFirstPlayerController()->GetPawn());

	TankAimingComponent = CurrentTank->FindComponentByClass<UTankAimingComponent>();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentTank)
	{
		PlayerTank = (GetWorld()->GetFirstPlayerController()->GetPawn());
		if (ensure(PlayerTank))
		{
			MoveToActor(PlayerTank, 100.0f);

			TankAimingComponent->AimAt(PlayerTank->GetTargetLocation());

			//TankAimingComponent->Fire();
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

