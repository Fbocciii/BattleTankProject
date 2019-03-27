// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include <Particles/ParticleSystemComponent.h>
#include "PhysicsEngine/RadialForceComponent.h"
#include <mutex>
#include "Engine/World.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"

//int AProjectile::PoolIndex = 0;
//AProjectile* AProjectile::ProjectilePool[AProjectile::MAX_PROJECTILES] = { nullptr };

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Creating and setting some variables
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Movement Component");
	MovementComponent->bAutoActivate = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>("Collision Mesh");
	SetRootComponent(CollisionMesh); //Sets this as root in BP
	CollisionMesh->SetNotifyRigidBodyCollision(true); //Turns on generate hit events by default
	CollisionMesh->SetVisibility(false); //Turns off mesh visibility by default
	
	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>("Launch Blast");
	
	LaunchBlast->SetupAttachment(CollisionMesh);
	
	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>("Impact Blast");

	ImpactBlast->AttachToComponent(CollisionMesh, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactBlast->bAutoActivate = false;
	//LaunchBlast->AttachToComponent(CollisionMesh, FAttachmentTransformRules::KeepRelativeTransform);
	
	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>("Explosion Force");
	ExplosionForce->SetupAttachment(CollisionMesh);
	ExplosionForce->bAutoActivate = false;

	//POOL MANAGEMENT 
	//std::mutex Lock;
	//Lock.lock();
	////Add to object pool
	//if (ProjectilePool[PoolIndex])
	//{
	//	ProjectilePool[PoolIndex]->Destroy();
	//}
	//ProjectilePool[PoolIndex] = this;
	//UE_LOG(LogTemp, Warning, TEXT("Pool Index: %i"), PoolIndex);
	//
	//if (++PoolIndex == MAX_PROJECTILES)
	//{
	//	PoolIndex = 0;
	//}
	//Lock.unlock();
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float Speed)
{
	MovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	MovementComponent->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ExplosionForce->Activate();
	ExplosionForce->FireImpulse();

	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();
	//this->Destroy();

	UGameplayStatics::ApplyRadialDamage(this,
										ProjectileDamage,
										GetActorLocation(),
										ExplosionForce->Radius, //for consistency
										UDamageType::StaticClass(),
										TArray<AActor*>()); //damage all actors (ignore empty array (i.e. none))

	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AProjectile::DelayDestroy, DestroyDelay);
}

void AProjectile::DelayDestroy()
{
	this->Destroy();
}

