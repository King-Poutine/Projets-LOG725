// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FlyDirectlyToward.generated.h"

class AAIController;
class ACharacter;

/**
 * 
 */
UCLASS()
class LOG725_LABO_API UFlyDirectlyToward : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UFlyDirectlyToward(const FObjectInitializer& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "Node")
	float AcceptableRadius = 5.0f;

	UPROPERTY(EditAnywhere, Category = "BlackboardKeys")
	FBlackboardKeySelector PatrolDestination;

private:
	AAIController* AIController;
	ACharacter* Character;
	UBlackboardComponent* BlackboardComp;

	AActor* DestinationHasActor;

};
