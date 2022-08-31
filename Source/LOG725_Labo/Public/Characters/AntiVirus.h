// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AntiVirus.generated.h"

UCLASS(Abstract)
class LOG725_LABO_API AAntiVirus : public ACharacter
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Movement")
	void ChangeMaxMoveSpeed(float maxMoveSpeed, float duration);

private:
	void RevertToOriginalMoveSpeed();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	float originalMaxWalkSpeed;
	float originalMaxFlySpeed;

	FTimerHandle ChangeMaxMoveSpeedTimerHandle;
};
