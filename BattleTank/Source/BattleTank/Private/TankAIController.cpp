// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Engine/World.h"
#include "Public/TankAimingComponent.h"
#include "Tank.h"

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
			MoveToActor(PlayerTank, AcceptanceRadius);

			TankAimingComponent->AimAt(PlayerTank->GetTargetLocation() + FVector(0, 0, 100.0f));

			if(TankAimingComponent->GetFiringState() == EFiringStatus::Locked)
				TankAimingComponent->Fire();
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

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!(ensure(PossessedTank)))
		{
			return;
		}

		PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankAIController::OnDeath);
	}
}

void ATankAIController::OnDeath()
{
	
	CurrentTank->DetachFromControllerPendingDestroy();
}

