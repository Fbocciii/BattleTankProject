// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

class UTankTurret;
/**
 * 
 */
UCLASS( meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 5.0f;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegrees = 30.0f;
		
	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegrees = 0.0f;

	UTankTurret* Turret = nullptr;
public:
	//Parameter is between -1 (Max downward speed) and +1 (Max updward speed)
	void Elevate(float RelativeSpeed);

	
};
