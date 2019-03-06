// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Public/TankAimingComponent.h"



void ATankPlayerController::AimTowardCrosshair()
{
	if (!GetPawn())
		return;
	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAimingComponent))
	{
		return;
	}

	
	FVector HitLocation(-1.0f);
	
	if (GetSightRayHitLocation(HitLocation))
	{
		TankAimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & Hit) 
{
	FCollisionQueryParams Params = FCollisionQueryParams(FName(""), false, GetOwner());
	
	GetViewportSize(ViewportX, ViewportY);
	ScreenLocation.Set(ViewportX * CrossHairXLocation, ViewportY * CrossHairYLocation);

	FVector CamLocation;
	FVector CamDirection;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CamLocation, CamDirection))
	{
		return GetLookVectorHitLocation(CamDirection, Hit);
	}

	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(const FVector& LookDirection, FVector& HitLocation)
{
	FHitResult Result;

	

	//Already gotten, refactor so it's not DUMB
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetPawn());
	//const FName TraceTag("TraceTag");
	//GetWorld()->DebugDrawTraceTag = TraceTag;
	//CollisionParams.TraceTag = TraceTag;
	bool hit = GetWorld()->LineTraceSingleByChannel(Result,
													StartLocation,
													EndLocation,
													ECollisionChannel::ECC_Visibility,
													CollisionParams);
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
	auto AimingComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComp))
	{
		FoundAimingComponent(AimingComp);
	}
}
