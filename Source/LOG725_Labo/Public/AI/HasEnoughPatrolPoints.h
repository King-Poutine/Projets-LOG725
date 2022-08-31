// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "HasEnoughPatrolPoints.generated.h"

/**
 * 
 */
UCLASS()
class LOG725_LABO_API UHasEnoughPatrolPoints : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UHasEnoughPatrolPoints();

	virtual bool CalculateRawConditionValue (UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const override;

	UPROPERTY(EditAnywhere, Category = "PatrolPoints")
	uint8 MinPatrolPointsNbr = 2;

};
