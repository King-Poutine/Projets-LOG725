// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreGameplay/FallingBackgroundActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"

// Sets default values
AFallingBackgroundActor::AFallingBackgroundActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->BoxSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxSpawnFallingObject"));
}

// Called when the game starts or when spawned
void AFallingBackgroundActor::BeginPlay()
{
	Super::BeginPlay();
	
	this->NormalizedFallingSpeed = this->FallingSpeed.GetSafeNormal();

	//Set timer to spawn the falling object
	GetWorldTimerManager().SetTimer(TimerHandleSpawner, this, &AFallingBackgroundActor::SpawnElement, this->SpawnRate, true, 1.0f);
}

// Called every frame
void AFallingBackgroundActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for(auto FallingObject : this->SpawnedFallingObject)
	{
		if (FallingObject != nullptr)
		{
			auto DistanceToMax = this->MaxDistanceFalling - FallingObject->GetActorLocation();
			DistanceToMax.Normalize();
			const auto CoLinearity = FVector::DotProduct(DistanceToMax, this->NormalizedFallingSpeed);

			if (CoLinearity > 0)
			{
				//Keep moving
				FallingObject->SetActorLocation(FallingObject->GetActorLocation() + this->FallingSpeed * DeltaTime);

			}
			else
			{
				//Delete Object
				this->FallingObjectToDelete.Add(FallingObject);
			}
		}
	}

	if (this->FallingObjectToDelete.Num() > 0)
	{
		for (auto FallingObject : this->FallingObjectToDelete)
		{
			this->SpawnedFallingObject.Remove(FallingObject);
			FallingObject->Destroy();
		}

		this->FallingObjectToDelete.Reset();
	}

}

FVector AFallingBackgroundActor::GetRandomPointInBox()
{
	FVector BoxOrigin = BoxSpawn->Bounds.Origin;
	FVector BoxExtent = BoxSpawn->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(BoxOrigin, BoxExtent);
}

void AFallingBackgroundActor::SpawnElement()
{
	if (this->FallingElementToSpawn != NULL)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			
			FVector SpawnLocation = this->GetRandomPointInBox();
			FRotator SpawnRotation;
			SpawnRotation.Yaw = 0.f;
			SpawnRotation.Pitch = 0.f;
			SpawnRotation.Roll = 0.f;


			const auto SpawnedFallingObjectActor = this->GetWorld()->SpawnActor(this->FallingElementToSpawn, &SpawnLocation, &SpawnRotation, SpawnParams);

			this->SpawnedFallingObject.Add(SpawnedFallingObjectActor);
		}
	}

}

