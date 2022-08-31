// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "VirusPlayerState.generated.h"

/**
 *
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLivesCountChangedDelegate, uint8, OldValue, uint8, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSpentFundsChangedDelegate, int32, OldValue, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTimerChangedDelegate, int32, SecValue);

UCLASS()
class LOG725_LABO_API AVirusPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		uint8 InitialLivesCount;

	UFUNCTION(BlueprintCallable)
		uint8 GetLivesCount() const;

	UFUNCTION(BlueprintCallable)
		void SetLivesCount(uint8 NewLivesCount);

	UPROPERTY(BlueprintAssignable)
		FLivesCountChangedDelegate OnLivesCountChanged;

	UFUNCTION(BlueprintCallable)
		int32 GetSpentFunds() const;

	UFUNCTION(BlueprintCallable)
		void SetSpentFunds(int32 NewSpentFunds);

	UFUNCTION(BlueprintCallable)
		int32 GetScore() const;

	UPROPERTY(BlueprintAssignable)
		FSpentFundsChangedDelegate OnSpentFundsChanged;

	UFUNCTION(BlueprintCallable)
		void TimerFunction();

	UPROPERTY(BlueprintAssignable)
		FTimerChangedDelegate OnTimerChanged;



protected:
	UPROPERTY(BlueprintReadWrite)
	    uint8 CurrentLivesCount;

	UPROPERTY(BlueprintReadWrite)
		int32 CurrentSpentFunds;

	UPROPERTY(BlueprintReadWrite)
		int32 CurrentSecs;

	FTimerHandle TimerHandle;

	// Called when the game starts
	virtual void BeginPlay() override;
};
