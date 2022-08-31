// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreGameplay/VirusSpawner.h"
#include "Characters/Virus.h"
#include "AIController.h"

// Sets default values
AVirusSpawner::AVirusSpawner()
{

}

void AVirusSpawner::SpawnVirus()
{
	if (SpawnedVirus == nullptr && ensure(VirusToSpawn))
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
		SpawnedVirus = GetWorld()->SpawnActor<AVirus>(VirusToSpawn, GetActorLocation(), GetActorRotation(), SpawnParameters);

		if (SpawnedVirus != nullptr)
		{
			GetWorldTimerManager().ClearTimer(SpawnTimerHandle);

			SpawnedVirus->OnDeath.AddDynamic(this, &AVirusSpawner::OnSpawnedVirusDeath);
			AAIController* controller = GetWorld()->SpawnActor<AAIController>(AAIController::StaticClass());
			controller->Possess(SpawnedVirus);
		}
		else
		{
			GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AVirusSpawner::SpawnVirus, SpawnDelay, true, SpawnDelay);
		}
	}
}

void AVirusSpawner::KillVirus()
{
	if (SpawnedVirus != nullptr)
	{
		SpawnedVirus->Kill();
	}
}

void AVirusSpawner::OnSpawnedVirusDeath()
{
	SpawnedVirus->OnDeath.RemoveDynamic(this, &AVirusSpawner::OnSpawnedVirusDeath);
	SpawnedVirus = nullptr;
	OnVirusDeath.Broadcast();
}


AVirus* AVirusSpawner::GetSpawnedVirus()
{
	return this->SpawnedVirus;
}

