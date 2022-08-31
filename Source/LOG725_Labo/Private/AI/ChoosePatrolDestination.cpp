// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ChoosePatrolDestination.h"
#include "AI/PatrollingAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/TargetPoint.h"

UChoosePatrolDestination::UChoosePatrolDestination(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Choose Next Destination";
}

EBTNodeResult::Type UChoosePatrolDestination::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	APatrollingAIController* AIController = Cast<APatrollingAIController>(OwnerComp.GetAIOwner());

	if (AIController)
	{
		UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();
		TArray<ATargetPoint*> PatrolPoints = AIController->GetPatrolPoints();

		if (BlackboardComp && PatrolPoints.Num() > 0)
		{
			CurrentIndex = (CurrentIndex + 1) % PatrolPoints.Num();
			BlackboardComp->SetValueAsVector(PatrolDestination.SelectedKeyName, PatrolPoints[CurrentIndex]->GetActorLocation());
			
			return EBTNodeResult::Succeeded;
		}
	}
	
	return EBTNodeResult::Failed;
}

