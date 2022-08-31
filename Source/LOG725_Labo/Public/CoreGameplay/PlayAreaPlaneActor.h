// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayAreaPlaneActor.generated.h"

UCLASS()
class LOG725_LABO_API APlayAreaPlaneActor : public AActor
{
	GENERATED_BODY()

public:
	// Normal of the plane in its default position
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector DefaultNormal;

	// Sets default values for this actor's properties
	APlayAreaPlaneActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
