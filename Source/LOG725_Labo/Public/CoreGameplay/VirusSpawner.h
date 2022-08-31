// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VirusSpawner.generated.h"

// Forward declaration
class AVirus;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVirusDeathDelegate);

UCLASS()
class LOG725_LABO_API AVirusSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVirusSpawner();
	
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnVirus();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void KillVirus();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	AVirus* GetSpawnedVirus();

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AVirus> VirusToSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	float SpawnDelay = 2.f;
	
	UPROPERTY(BlueprintAssignable, Category = "Gameplay")
	FVirusDeathDelegate OnVirusDeath;

private:
	UFUNCTION()
	void OnSpawnedVirusDeath();

	FTimerHandle SpawnTimerHandle;

	AVirus* SpawnedVirus;
};
