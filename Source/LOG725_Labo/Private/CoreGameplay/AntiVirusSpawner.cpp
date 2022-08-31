// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreGameplay/AntiVirusSpawner.h"
#include "AI/PatrollingAIController.h"
#include "Characters/AntiVirus.h"

// Sets default values
AAntiVirusSpawner::AAntiVirusSpawner()
{

}

void AAntiVirusSpawner::SpawnAntiVirus()
{
	if (SpawnedAntiVirus == nullptr && ensure(AntiVirusToSpawn))
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
		SpawnedAntiVirus = GetWorld()->SpawnActor<APawn>(AntiVirusToSpawn, GetActorLocation(), GetActorRotation(), SpawnParameters);

		if (SpawnedAntiVirus != nullptr)
		{
			GetWorldTimerManager().ClearTimer(SpawnTimerHandle);

			APatrollingAIController* controller = GetWorld()->SpawnActor<APatrollingAIController>(AIControllerUsed);
			controller->SetPatrolPoints(PatrolPoints);
			controller->Possess(SpawnedAntiVirus);
		}
		else
		{
			GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AAntiVirusSpawner::SpawnAntiVirus, SpawnDelay, true, SpawnDelay);
		}
	}
}

