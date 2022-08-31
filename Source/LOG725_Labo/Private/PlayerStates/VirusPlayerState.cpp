// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStates/VirusPlayerState.h"
#include "TimerManager.h"

void AVirusPlayerState::BeginPlay()
{
    Super::BeginPlay();

    this->CurrentLivesCount = this->InitialLivesCount;
    this->CurrentSpentFunds = 0;
    this->CurrentSecs = 0;

    GetWorldTimerManager().SetTimer(TimerHandle, this, &AVirusPlayerState::TimerFunction, 1.0f, true, 0.2f);
}


uint8 AVirusPlayerState::GetLivesCount() const
{
    return this->CurrentLivesCount;
}

void AVirusPlayerState::SetLivesCount(const uint8 NewLivesCount)
{
    const auto OldVal = this->CurrentLivesCount;
    this->CurrentLivesCount = NewLivesCount;
    this->OnLivesCountChanged.Broadcast(OldVal, this->CurrentLivesCount);
    //UE_LOG(LogTemp, Warning, TEXT("Set lives"));
}

int32 AVirusPlayerState::GetSpentFunds() const
{
    return this->CurrentSpentFunds;
}

void AVirusPlayerState::SetSpentFunds(int32 NewSpentFunds)
{
    const auto OldVal = this->CurrentSpentFunds;
    this->CurrentSpentFunds = NewSpentFunds;
    this->OnSpentFundsChanged.Broadcast(OldVal, this->CurrentSpentFunds);
    //UE_LOG(LogTemp, Warning, TEXT("Set spent funds : %d"), NewSpentFunds);
}

int32 AVirusPlayerState::GetScore() const
{
    /*
    UE_LOG(LogTemp, Warning, TEXT("Live : %d"), CurrentLivesCount);
    UE_LOG(LogTemp, Warning, TEXT("Founds : %d"), CurrentSpentFunds);
    UE_LOG(LogTemp, Warning, TEXT("Time : %d"), CurrentSecs);
    UE_LOG(LogTemp, Warning, TEXT("Score : %d"), (((this->CurrentLivesCount * 10000) - this->CurrentSpentFunds) / this->CurrentSecs));
    */
    return ((this->CurrentLivesCount * 10000) - this->CurrentSpentFunds) / FMath::CeilToInt(this->CurrentSecs/60.0f);
}

void AVirusPlayerState::TimerFunction() 
{
    this->CurrentSecs = this->CurrentSecs + 1;
    this->OnTimerChanged.Broadcast(this->CurrentSecs);
    //UE_LOG(LogTemp, Warning, TEXT("Time : %d"), CurrentSecs);
}

