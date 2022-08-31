// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreGameplay/SavePoint.h"
#include "Components/BoxComponent.h"
#include "Engine/CollisionProfile.h"
#include "Characters/Virus.h"

// Sets default values
ASavePoint::ASavePoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("SavePoint"));
	BoxComponent->SetGenerateOverlapEvents(true);
	BoxComponent->SetCollisionProfileName("OverlapAllDynamic");
	SetRootComponent(BoxComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("SavePointMesh");
	StaticMeshComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	StaticMeshComponent->SetupAttachment(BoxComponent);
}

// Called when the game starts or when spawned
void ASavePoint::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ASavePoint::OnBeginOverlap);
	
}

void ASavePoint::UnSave()
{
	//change color back
	if (this->NonActiveFlag != nullptr)
	{
		this->StaticMeshComponent->SetMaterial(1, NonActiveFlag);
	}
}

// Called on begin overlap
void ASavePoint::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AVirus* Virus = Cast<AVirus>(OtherActor);

	if (Virus)
	{

		UE_LOG(LogTemp, Warning, TEXT("Overlap Virus"));
		OnVirusSave.Broadcast(this);

		//Call function to change color
		if (this->ActiveFlag != nullptr)
		{
			if (StaticMeshComponent != nullptr)
			{
				this->StaticMeshComponent->SetMaterial(1, ActiveFlag);
			}
		}
		
	}
}


