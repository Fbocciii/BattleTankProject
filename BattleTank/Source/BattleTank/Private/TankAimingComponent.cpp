// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Public/TankBarrel.h"
#include "Public/TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;// true;

	// ...
	Owner = GetOwner();
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UTankAimingComponent::MoveBarrelTowards(const FVector AimDirection)
{
	if (!ensure(Barrel && Turret))
	{
		return;
	}
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;
	
	Barrel->Elevate(DeltaRotator.Pitch);
	
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}

}



void UTankAimingComponent::AimAt(const FVector & HitLocation)
{

	if (!Barrel)
		return;

	FVector LaunchVelocity(0.0f);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	

	bool HaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this,
																	   LaunchVelocity,
																	   StartLocation,
																	   HitLocation,
																	   LaunchSpeed,
																	   false,
																	   0.0f,
																	   0.0f,
																	   ESuggestProjVelocityTraceOption::DoNotTrace);
	auto Time = GetWorld()->GetTimeSeconds();
	if(HaveAimSolution)
	{
		FString OurTankName = Owner->GetName();
		FVector AimDirection = LaunchVelocity.GetSafeNormal();

		MoveBarrelTowards(AimDirection);
	}

}

void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

const UTankBarrel * UTankAimingComponent::GetBarrel() const
{
	return Barrel;
}
