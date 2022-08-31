// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Orbit.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UOrbit::UOrbit(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bNotifyTick = true;
	NodeName = "Orbit";
}

EBTNodeResult::Type UOrbit::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
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

	return EBTNodeResult::InProgress;
}

void UOrbit::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	FVector TargetToLocation = Character->GetActorLocation() - BlackboardComp->GetValueAsVector(PatrolDestination.SelectedKeyName);
	FVector Input = FVector::CrossProduct(TargetToLocation, FVector::ForwardVector).GetSafeNormal();

	Character->AddMovementInput((Input - TargetToLocation).GetSafeNormal(), 1.0f);
}