// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PatrollingAIController.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"

APatrollingAIController::APatrollingAIController()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = false;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;

	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());

	PerceptionComponent->OnTargetPerceptionInfoUpdated.AddDynamic(this, &APatrollingAIController::OnPerception);
}

void APatrollingAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	InitializeBehavior();
}

FGenericTeamId APatrollingAIController::GetGenericTeamId() const
{
	return FGenericTeamId(1);
}

void APatrollingAIController::SetPatrolPoints(TArray<ATargetPoint*> TargetPoints)
{
	PatrolPoints = TargetPoints;
}

void APatrollingAIController::InitializeBehavior()
{
	UseBlackboard(BlackboardUsed, Blackboard);
	RunBehaviorTree(BehaviorTreeUsed);
}

void APatrollingAIController::OnPerception(const FActorPerceptionUpdateInfo& UpdateInfo)
{
	if (BlackboardUsed != nullptr)
	{
		if (UpdateInfo.Stimulus.WasSuccessfullySensed())
		{
			GetBlackboardComponent()->SetValueAsObject(VirusKeyName, UpdateInfo.Target.Get());
		}
		else
		{
			GetBlackboardComponent()->SetValueAsObject(VirusKeyName, nullptr);
		}
	}
	
}