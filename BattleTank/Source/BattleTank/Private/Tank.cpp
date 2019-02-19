// Fill out your copyright notice in the Description page of Project Settings.

//#include "Tank.h"
#include "Public/Tank.h"
#include "Public/TankAimingComponent.h"
#include "Public/TankBarrel.h"
#include "Engine/World.h"
#include "Public/Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>("Aiming Component");
}

void ATank::AimAt(const FVector & HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	//FString OurTankName = GetName();

	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at: %s"), *OurTankName, *HitLocation.ToString());


}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret * TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire()
{
	
	if (!Barrel)
	{
		UE_LOG(LogTemp, Warning, TEXT("NO BARREL"));
		return;
	}
	else
	{
		GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
											Barrel->GetSocketLocation(FName("Projectile")),
											Barrel->GetSocketRotation(FName("Projectile")));
	}
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

