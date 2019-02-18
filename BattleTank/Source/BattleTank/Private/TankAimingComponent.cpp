// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Public/TankBarrel.h"

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
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;
	
	Barrel->Elevate(5.0f);

	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString())
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(const FVector & HitLocation, float LaunchSpeed)
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
	if(HaveAimSolution)
	{
		FString OurTankName = Owner->GetName();
		FVector AimDirection = LaunchVelocity.GetSafeNormal();

		MoveBarrelTowards(AimDirection);
		//UE_LOG(LogTemp, Warning, TEXT("%s aiming at: %s"), *OurTankName, *AimDirection.ToString());
	}
	
	
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at: %s \n\tFrom barrel position: %s"), *OurTankName, *HitLocation.ToString(), *Barrel->GetComponentLocation().ToString());


}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}
