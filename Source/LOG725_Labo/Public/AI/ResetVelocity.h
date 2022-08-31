// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ResetVelocity.generated.h"

class ACharacter;

/**
 * 
 */
UCLASS()
class LOG725_LABO_API UResetVelocity : public UBTService
{
	GENERATED_BODY()

public:
	UResetVelocity(const FObjectInitializer& ObjectInitializer);

	virtual void OnCeaseRelevant(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) override;

private:
	ACharacter* Character;

};
