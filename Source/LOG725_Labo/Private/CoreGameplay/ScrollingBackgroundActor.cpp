// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreGameplay/ScrollingBackgroundActor.h"

// Sets default values
AScrollingBackgroundActor::AScrollingBackgroundActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AScrollingBackgroundActor::BeginPlay()
{
	Super::BeginPlay();

	this->NormalizedScrollingSpeed = this->ScrollingSpeed.GetSafeNormal();

	this->MaxPosition = this->InitialPosition + this->NormalizedScrollingSpeed * this->SpawnInterval;

	if(this->BackgroundElementToSpawn != nullptr)
	{
		for (int i = 0; i < this->MaxElementCount; i++)
		{
			//spawn each object along the scrolling direction, behind the previous object
			const FVector Location = this->InitialPosition - this->NormalizedScrollingSpeed * this->SpawnInterval * i;
			this->SpawnBackgroundElementAt(Location);
		}
	}	
}

// Called every frame
void AScrollingBackgroundActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for(auto Background : this->SpawnedBackgrounds)
	{
	    if(Background != nullptr)
	    {
			//check if the background element has gone beyond its destination by comparing its scrolling direction to the distance to the destination
			auto DistanceToMax = this->MaxPosition - Background->GetActorLocation();
			DistanceToMax.Normalize();
			const auto Collinearity = FVector::DotProduct(DistanceToMax, this->NormalizedScrollingSpeed);

			if(Collinearity > 0) //still moving towards the destination
			{
				//move actor
				Background->SetActorLocation(Background->GetActorLocation() + this->ScrollingSpeed * DeltaTime);
			}
			else //is beyond it
			{
				this->BackgroundsToDelete.Add(Background);
			}
	    }
	}

	if(this->BackgroundsToDelete.Num() > 0)
	{
		//remove elements from the front after they went too far
		for (auto Background : this->BackgroundsToDelete)
		{
			this->SpawnedBackgrounds.Remove(Background);
			Background->Destroy();
		}

		this->BackgroundsToDelete.Reset();

		//respawn them at the back
		for (int i = this->SpawnedBackgrounds.Num(); i < this->MaxElementCount; i++)
		{
			//spawn each object along the scrolling direction, behind the previous object
			const FVector Location = this->InitialPosition - this->NormalizedScrollingSpeed * this->SpawnInterval * i;
			this->SpawnBackgroundElementAt(Location);
		}
	}
}

void AScrollingBackgroundActor::SpawnBackgroundElementAt(const FVector Location)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const auto SpawnedBackground = this->GetWorld()->SpawnActor(this->BackgroundElementToSpawn, &Location, &this->Rotation, SpawnParameters);

	this->SpawnedBackgrounds.Add(SpawnedBackground);
}