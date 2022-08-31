// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScrollingBackgroundActor.generated.h"

UCLASS()
class LOG725_LABO_API AScrollingBackgroundActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScrollingBackgroundActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	    TSubclassOf<AActor> BackgroundElementToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FVector InitialPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	    FVector ScrollingSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 SpawnInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	    int32 MaxElementCount;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<AActor*> SpawnedBackgrounds;

	TArray<AActor*> BackgroundsToDelete;

	FVector NormalizedScrollingSpeed;

	FVector MaxPosition;

	void SpawnBackgroundElementAt(const FVector Location);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
