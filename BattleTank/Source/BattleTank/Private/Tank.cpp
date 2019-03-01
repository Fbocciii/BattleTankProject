// Fill out your copyright notice in the Description page of Project Settings.

//#include "Tank.h"
#include "Public/Tank.h"
#include "Engine/World.h"
#include "Public/Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}


void ATank::Fire()
{
	//bool IsReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTime;
	//if(ensure(TankAimingComponent) && ensure(TankAimingComponent->GetBarrel()) && IsReloaded)
	//{
	//	AProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
	//										TankAimingComponent->GetBarrel()->GetSocketLocation(FName("Projectile")),
	//										TankAimingComponent->GetBarrel()->GetSocketRotation(FName("Projectile")));
	//	SpawnedProjectile->LaunchProjectile(LaunchSpeed);
	//	LastFireTime = GetWorld()->GetTimeSeconds();
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Fire malfunction!"));
	//}
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

