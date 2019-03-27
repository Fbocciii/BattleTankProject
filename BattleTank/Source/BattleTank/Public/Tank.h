// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

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

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	float CurrentHealth;

	
	
public:
	// Sets default values for this pawn's properties
	ATank();

	virtual float TakeDamage(float DamageAmount,
							 struct FDamageEvent const & DamageEvent,
							 class AController* EventInstigator,
							 AActor* DamageCauser) override;
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const { return CurrentHealth / MaxHealth; };

	FTankDelegate OnTankDeath;
};
