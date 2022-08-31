// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreGameplay/Pickups/Pickup.h"
#include "SpeedUp.generated.h"

/**
 * 
 */
UCLASS()
class LOG725_LABO_API ASpeedUp : public APickup
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Speed Up")
	float speedUpMaxMoveSpeed = 250.f;

	UPROPERTY(EditDefaultsOnly, Category = "Speed Up")
	float speedUpDuration = 5.f;

protected:
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
