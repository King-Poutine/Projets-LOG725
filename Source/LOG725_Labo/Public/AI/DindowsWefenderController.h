// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/PatrollingAIController.h"
#include "DindowsWefenderController.generated.h"

class ACharacter;

/**
 * 
 */
UCLASS(Abstract)
class LOG725_LABO_API ADindowsWefenderController : public APatrollingAIController
{
	GENERATED_BODY()
	
public:
	ADindowsWefenderController();

	UPROPERTY(EditDefaultsOnly, Category = "Behavior")
	float Height;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;

protected:

	void ChangeMovementType();

	FTimerHandle ChangeMovementTypeTimer;

private:

	void InitializeController();
	
	ACharacter* MyCharacter;

	float StartingPosition;

	float FinalPosition;

	float Bugging;

	float RandTimer;

	FVector Direction;

	uint8 MovementTypeRD;

};
