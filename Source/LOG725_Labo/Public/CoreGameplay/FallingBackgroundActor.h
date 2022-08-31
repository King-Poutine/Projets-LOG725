// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FallingBackgroundActor.generated.h"

UCLASS()
class LOG725_LABO_API AFallingBackgroundActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFallingBackgroundActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor> FallingElementToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector FallingSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector MaxDistanceFalling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SpawnRate;

	FORCEINLINE class UBoxComponent* GetBoxSpawn() const { return BoxSpawn; }

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UBoxComponent* BoxSpawn;

	TArray<AActor*> SpawnedFallingObject;

	TArray<AActor*> FallingObjectToDelete;

	FVector NormalizedFallingSpeed;

	FTimerHandle TimerHandleSpawner;

	FVector GetRandomPointInBox();

	void SpawnElement();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
