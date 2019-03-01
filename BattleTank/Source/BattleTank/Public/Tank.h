// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//TODO remove
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 10000.0f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTime = 3.0f;

	double LastFireTime = 0.0;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint; //Alternative TSubclassOf<T>

	

public:
	// Sets default values for this pawn's properties
	ATank();

	//TODO move to aiming comp and remove!
	UFUNCTION(BlueprintCallable, Category = Runtime)
	void Fire();
};
