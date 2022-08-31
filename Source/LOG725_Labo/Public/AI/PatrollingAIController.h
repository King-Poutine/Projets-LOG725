// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "PatrollingAIController.generated.h"

// Forward declaration
class UAISenseConfig_Sight;
class ATargetPoint;

UCLASS(Abstract)
class LOG725_LABO_API APatrollingAIController : public AAIController
{
	GENERATED_BODY()

public:
	APatrollingAIController();

	virtual void OnPossess(APawn* InPawn) override;

	virtual FGenericTeamId GetGenericTeamId() const override;

	void SetPatrolPoints(TArray<ATargetPoint*> PatrolPoints);

	TArray<ATargetPoint*> GetPatrolPoints() const { return PatrolPoints; }

	UPROPERTY(EditDefaultsOnly, Category = "Behavior")
	UBehaviorTree* BehaviorTreeUsed;

	UPROPERTY(EditDefaultsOnly, Category = "Behavior")
	UBlackboardData* BlackboardUsed;

	UPROPERTY(EditDefaultsOnly, Category = "Perception")
	FName VirusKeyName = FName(TEXT("Virus"));

private:
	void InitializeBehavior();
	
	UFUNCTION()
	void OnPerception(const FActorPerceptionUpdateInfo& UpdateInfo);

	UAISenseConfig_Sight* SightConfig;

	TArray<ATargetPoint*> PatrolPoints;
};
