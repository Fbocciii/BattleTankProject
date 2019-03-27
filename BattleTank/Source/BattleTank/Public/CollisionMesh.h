// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "CollisionMesh.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API UCollisionMesh : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UCollisionMesh();

	virtual void BeginPlay();


protected:

};
