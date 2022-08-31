// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "Virus.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathDelegate);

UCLASS()
class LOG725_LABO_API AVirus : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	AVirus();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SetInput(float Input);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void FlipDirection();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Movement")
	void ChangeMaxMoveSpeed(float maxMoveSpeed, float duration);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gameplay")
	void Kill();

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float MaxNomralZToTurn = .2f;

	UPROPERTY(BlueprintAssignable, Category = "Gameplay")
	FDeathDelegate OnDeath;

	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;

	virtual FGenericTeamId GetGenericTeamId() const override;

private:
	void MoveRight(float Value);

	void RevertToOriginalMoveSpeed();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	float MoveDirection = -1.f;

	float MoveInput = 0.f;

	float originalMaxWalkSpeed;

	FTimerHandle ChangeMaxMoveSpeedTimerHandle;
};
