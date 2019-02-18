// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Public/Tank.h"
#include "Engine/World.h"
#include "Public/TankAimingComponent.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardCrosshair()
{
	ATank* CurTank = GetControlledTank();
	if (!CurTank)
	{
		return;
	}

	
	FVector HitLocation(-1.0f);

	GetSightRayHitLocation(HitLocation);
	
	CurTank->AimAt(HitLocation);
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & Hit) 
{
	FCollisionQueryParams Params = FCollisionQueryParams(FName(""), false, GetOwner());
	
	GetViewportSize(ViewportX, ViewportY);
	ScreenLocation.Set(ViewportX * CrossHairXLocation, ViewportY * CrossHairYLocation);

	//UE_LOG(LogTemp, Warning, TEXT("Screen Loc: %s"), *ScreenLocation.ToString());
	FVector CamLocation;
	FVector CamDirection;
	DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CamLocation, CamDirection);
	//UE_LOG(LogTemp, Warning, TEXT("View direction: %s"), *CamDirection.ToString());
	//FVector HitLocation(0.0);
	if(GetLookVectorHitLocation(CamDirection, Hit))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
		
	}

	//Hit = HitLocation;
	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(const FVector& LookDirection, FVector& HitLocation)
{
	FHitResult Result;

	

	//Already gotten, refactor so it's not DUMB
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	bool hit = GetWorld()->LineTraceSingleByChannel(Result,
													StartLocation,
													EndLocation,
													ECollisionChannel::ECC_Visibility);
	if (hit)
	{
		HitLocation = Result.Location;
		return true;
	}
	return false;
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardCrosshair();
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
