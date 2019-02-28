// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankMovementComponent.h"
#include "Public/TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack)
	{
		UE_LOG(LogTemp, Error, TEXT("Missing Track(s) in Movement component!"));
		return;
	}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack)
	{
		UE_LOG(LogTemp, Error, TEXT("Missing Track(s) in Movement component!"));
		return;
	}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

}
void UTankMovementComponent::Initialize(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet)
	{
		UE_LOG(LogTemp, Error, TEXT("Missing Track(s) in Movement component!"));
	}
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{

	FVector TankForward = GetOwner()->GetActorForwardVector();
	FVector MoveNormal = MoveVelocity.GetSafeNormal();

	float ForwardThrow = FVector::DotProduct(TankForward, MoveNormal);
	float TurnThrow = FVector::CrossProduct(TankForward, MoveNormal).Z;

	IntendMoveForward(ForwardThrow);
	IntendTurnRight(TurnThrow);
}

