// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "IsCloseEnough.generated.h"

/**
 *
 */
UCLASS()
class LOG725_LABO_API UIsCloseEnough : public UBTDecorator
{
	GENERATED_BODY()

public:
	UIsCloseEnough();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const override;

	UPROPERTY(EditAnywhere, Category = "Node")
	float MaxDistance = 500.0f;

	UPROPERTY(EditAnywhere, Category = "BlackboardKeys")
	FBlackboardKeySelector DistanceTo;

};
