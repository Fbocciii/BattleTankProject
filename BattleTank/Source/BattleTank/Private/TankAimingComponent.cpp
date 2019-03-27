// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Public/TankBarrel.h"
#include "Public/TankTurret.h"
#include "Public/Projectile.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	Owner = GetOwner();

	
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	LastFireTime = GetWorld()->GetTimeSeconds();
	CurrentAmmo = AmmoCapacity;
	Super::BeginPlay();

	// ...
	
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if (CurrentAmmo <= 0)
	{
		FiringStatus = EFiringStatus::Empty;
	}
	else if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTime)
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else
	{
		FiringStatus = EFiringStatus::Locked;
	}
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



bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel))
		return false;

	return !AimDirection.Equals(Barrel->GetForwardVector(), 0.01f);

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
		AimDirection = LaunchVelocity.GetSafeNormal();

		MoveBarrelTowards(AimDirection);
	}

}

void UTankAimingComponent::Fire()
{
	if (FiringStatus != EFiringStatus::Reloading && FiringStatus != EFiringStatus::Empty)
	{
		AProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
																			 Barrel->GetSocketLocation(FName("Projectile")),
																			 Barrel->GetSocketRotation(FName("Projectile")));
		SpawnedProjectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
		FiringStatus = EFiringStatus::Reloading;
		--CurrentAmmo;
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
