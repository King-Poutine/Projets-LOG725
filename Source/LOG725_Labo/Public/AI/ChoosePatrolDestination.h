// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChoosePatrolDestination.generated.h"

/**
 * 
 */
UCLASS()
class LOG725_LABO_API UChoosePatrolDestination : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UChoosePatrolDestination(const FObjectInitializer& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "BlackboardKeys")
	FBlackboardKeySelector PatrolDestination;

private:
	uint8 CurrentIndex = -1;

};
