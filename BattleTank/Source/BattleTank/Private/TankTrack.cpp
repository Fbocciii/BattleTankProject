// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankTrack.h"

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	
	
	ApplySidewaysForce();
	DriveTrack();
	CurrentThrottle = 0.0f;

}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>((CurrentThrottle + Throttle), -1.0f, 1.0f);

}

void UTankTrack::DriveTrack()
{
	FVector ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}



void UTankTrack::ApplySidewaysForce()
{
	float SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());

	float DeltaTime = GetWorld()->GetDeltaSeconds();

	FVector CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	FVector CorrectionForce = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent())->GetMass() * CorrectionAcceleration *.5f;

	Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent())->AddForce(CorrectionForce);
}


