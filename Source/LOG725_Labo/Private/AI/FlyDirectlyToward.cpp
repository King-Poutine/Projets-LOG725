// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/FlyDirectlyToward.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UFlyDirectlyToward::UFlyDirectlyToward(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bNotifyTick = true;
	NodeName = "Fly Directly Toward";
}

EBTNodeResult::Type UFlyDirectlyToward::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	if (!AIController)
	{
		AIController = Cast<AAIController>(OwnerComp.GetAIOwner());

		if (AIController)
		{
			Character = Cast<ACharacter>(AIController->GetPawn());
			BlackboardComp = AIController->GetBlackboardComponent();
		}

		if (!Character || !BlackboardComp || !AIController)
		{
			return EBTNodeResult::Failed;
		}
	}

	DestinationHasActor = (AActor*)BlackboardComp->GetValueAsObject(PatrolDestination.SelectedKeyName);

	return EBTNodeResult::InProgress;
}

void UFlyDirectlyToward::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	FVector Destination;

	if (DestinationHasActor)
	{
		Destination = DestinationHasActor->GetActorLocation();
	}
	else
	{
		Destination = BlackboardComp->GetValueAsVector(PatrolDestination.SelectedKeyName);
	}

	FVector LocationToTarget = Destination - Character->GetActorLocation();
	Character->AddMovementInput(LocationToTarget.GetSafeNormal(), 1.0f);

	if (LocationToTarget.SizeSquared() <= (AcceptableRadius * AcceptableRadius))
	{
		//Character->GetCharacterMovement()->Velocity = FVector::ZeroVector;

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}