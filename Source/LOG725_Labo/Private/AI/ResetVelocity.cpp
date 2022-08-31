// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ResetVelocity.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UResetVelocity::UResetVelocity(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bNotifyCeaseRelevant = true;
	NodeName = "Reset Velocity";
}

void UResetVelocity::OnCeaseRelevant(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);

	if (!Character)
	{
		AAIController* AIController = Cast<AAIController>(OwnerComp.GetAIOwner());

		if (AIController)
		{
			Character = Cast<ACharacter>(AIController->GetPawn());
		}

		if (!Character || !AIController)
		{
			return;
		}
	}

	Character->GetCharacterMovement()->Velocity = FVector::ZeroVector;
}