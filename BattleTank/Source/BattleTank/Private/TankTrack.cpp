// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankTrack.h"

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("On Hit!"));
}

void UTankTrack::SetThrottle(float Throttle)
{
	auto Name = GetName();

	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

	//UE_LOG(LogTemp, Warning, TEXT("%s force: %s at %s\tThrottle:%f"), *TankRoot->GetName(), *ForceApplied.ToString(), *ForceLocation.ToString(), Throttle);
}

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());

	FVector CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	FVector CorrectionForce = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent())->GetMass() * CorrectionAcceleration *.5f;

	Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent())->AddForce(CorrectionForce);

}


