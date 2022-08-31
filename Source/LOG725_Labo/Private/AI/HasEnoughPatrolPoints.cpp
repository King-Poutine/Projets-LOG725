// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/HasEnoughPatrolPoints.h"
#include "AI/PatrollingAIController.h"

UHasEnoughPatrolPoints::UHasEnoughPatrolPoints()
{
	NodeName = "Has Enough Patrol Points";
}

bool UHasEnoughPatrolPoints::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	APatrollingAIController* AIController = Cast<APatrollingAIController>(OwnerComp.GetAIOwner());

	if (AIController)
	{
		return AIController->GetPatrolPoints().Num() >= MinPatrolPointsNbr;
	}

	return false;
}