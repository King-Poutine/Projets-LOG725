// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreGameplay/Portal.h"
#include "Components/BoxComponent.h"
#include "Engine/CollisionProfile.h"
#include "CoreGameplay/Pickups/Pickup.h"
#include "Characters/Virus.h"

APortal::APortal()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Trigger");
	BoxComponent->SetGenerateOverlapEvents(false);
	BoxComponent->SetCollisionProfileName("OverlapAllDynamic");
	SetRootComponent(BoxComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("PortalMesh");
	StaticMeshComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	StaticMeshComponent->SetupAttachment(BoxComponent);
}

void APortal::BeginPlay()
{
	Super::BeginPlay();
	
	for (APickup* Pickup : NeededPickups)
	{
		if(Pickup != nullptr)
		{
			Pickup->OnPickedUp.AddDynamic(this, &APortal::OnPickedUp);
		}
	}

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnBeginOverlap);
}

void APortal::OnPickedUp()
{
	nbrPickupCollected++;

	if (nbrPickupCollected >= NeededPickups.Num())
	{
		OpenGate();
	}
}

void APortal::OpenGate()
{
	BoxComponent->SetGenerateOverlapEvents(true);
	this->OnGateOpened.Broadcast();
}

void APortal::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AVirus* Virus = Cast<AVirus>(OtherActor);

	if (Virus)
	{
		OnVirusReachPortal.Broadcast();
	}
}
