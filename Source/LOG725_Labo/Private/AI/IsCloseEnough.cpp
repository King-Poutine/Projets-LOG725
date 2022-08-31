// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/IsCloseEnough.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"

UIsCloseEnough::UIsCloseEnough()
{
	NodeName = "Is Close Enough";
}

bool UIsCloseEnough::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	AAIController* AIController = Cast<AAIController>(OwnerComp.GetAIOwner());
	ACharacter* Character;
	UBlackboardComponent* BlackboardComp;

	if (AIController)
	{
		Character = Cast<ACharacter>(AIController->GetPawn());
		BlackboardComp = AIController->GetBlackboardComponent();

		if (!Character || !BlackboardComp)
		{
			return false;
		}

		AActor* DistanceToHasActor = (AActor*)BlackboardComp->GetValueAsObject(DistanceTo.SelectedKeyName);
		float DistanceSquared;

		if (DistanceToHasActor)
		{
			DistanceSquared = (DistanceToHasActor->GetActorLocation() - Character->GetActorLocation()).SizeSquared();
		}
		else
		{
			DistanceSquared = (BlackboardComp->GetValueAsVector(DistanceTo.SelectedKeyName) - Character->GetActorLocation()).SizeSquared();
		}

		return DistanceSquared <= MaxDistance * MaxDistance;
	}

	return false;
}