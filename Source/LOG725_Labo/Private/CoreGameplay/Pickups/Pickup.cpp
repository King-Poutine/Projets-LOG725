// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreGameplay/Pickups/Pickup.h"
#include "Components/BoxComponent.h"
#include "Engine/CollisionProfile.h"
#include "Characters/Virus.h"

APickup::APickup()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Trigger");
	BoxComponent->SetGenerateOverlapEvents(true);
	BoxComponent->SetCollisionProfileName("OverlapAllDynamic");
	SetRootComponent(BoxComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	StaticMeshComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	StaticMeshComponent->SetupAttachment(BoxComponent);
}

void APickup::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnBeginOverlap);
}

void APickup::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AVirus* Virus = Cast<AVirus>(OtherActor);

	if (Virus)
	{
		OnPickedUp.Broadcast();
		Destroy();
	}
}

