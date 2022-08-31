// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AntiVirusSpawner.generated.h"

// Forward declaration
class AAntiVirus;
class APatrollingAIController;
class ATargetPoint;

UCLASS()
class LOG725_LABO_API AAntiVirusSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAntiVirusSpawner();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnAntiVirus();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<AAntiVirus> AntiVirusToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<APatrollingAIController> AIControllerUsed;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	float SpawnDelay = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
	TArray<ATargetPoint*> PatrolPoints;

private:
	FTimerHandle SpawnTimerHandle;

	APawn* SpawnedAntiVirus;
};
