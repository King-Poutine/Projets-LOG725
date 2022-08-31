// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreGameplay/DestroyableLedge.h"
#include "Components/BoxComponent.h"
#include "Engine/CollisionProfile.h"
#include "Characters/Virus.h"

// Sets default values
ADestroyableLedge::ADestroyableLedge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponentBlock = CreateDefaultSubobject<UBoxComponent>("DestroyableLedgeBlock");
	BoxComponentBlock->SetGenerateOverlapEvents(true);
	BoxComponentBlock->SetCollisionProfileName("BlockAllDynamic");
	SetRootComponent(BoxComponentBlock);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("DestroyableLedgeMesh");
	StaticMeshComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	StaticMeshComponent->SetupAttachment(BoxComponentBlock);

	BoxComponentOverLap = CreateDefaultSubobject<UBoxComponent>("DestroyableLedgeOverLap");
	BoxComponentOverLap->SetGenerateOverlapEvents(true);
	BoxComponentOverLap->SetCollisionProfileName("OverlapAllDynamic");
	//BoxComponentOverLap->SetupAttachment(BoxComponentBlock);
}

/*
void ADestroyableLedge::DestroyLedge()
{
}
*/
void ADestroyableLedge::DestroyLedge_Implementation()
{
	this->Destroy();
}

// Called when the game starts or when spawned
void ADestroyableLedge::BeginPlay()
{
	Super::BeginPlay();
	BoxComponentOverLap->OnComponentBeginOverlap.AddDynamic(this, &ADestroyableLedge::OnBeginOverlap);
	
}

void ADestroyableLedge::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AVirus* Virus = Cast<AVirus>(OtherActor);

	if (Virus)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnBeginOverLap Ledge"));
		this->DestroyLedge();
	}
}



