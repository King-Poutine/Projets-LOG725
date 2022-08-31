// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "CoreGameplay/SaveHighScore.h"
#include "HighScoreSubsystem.generated.h"

class USaveHighScore;

DECLARE_DYNAMIC_DELEGATE_OneParam(FAsyncSaveHighScoreDelegate, const bool, successful);

UCLASS(DisplayName = "High Score Subsystem")
class LOG725_LABO_API UHighScoreSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End USubsystem

	UFUNCTION(BlueprintCallable, Category = HighScoreSubsystem)
	bool SaveHighScore();

	UFUNCTION(BlueprintCallable, Category = HighScoreSubsystem)
	void AsyncSaveHighScore(const FAsyncSaveHighScoreDelegate& Callback);

	UFUNCTION(BlueprintCallable, Category = HighScoreSubsystem)
	bool IsScoreHighEnough(int32 score) const;

	// Returns true if the high score changed
	UFUNCTION(BlueprintCallable, Category = HighScoreSubsystem)
	bool AddHighScore(FString name, int32 score);

	UFUNCTION(BlueprintCallable, Category = HighScoreSubsystem)
	TMap<uint8, FHighScoreEntry> GetHighScores();

	UFUNCTION(BlueprintCallable, Category = HighScoreSubsystem)
	void ClearHighScores();

private:

	bool DoesHighScoreExist() const;
	bool LoadHighScore();

	static const FString HighScoreSaveName;
	static const uint8 MaxHighScoreCount = 10;
	
	// Must be a UPROPERTY or else the garbage collector while erase some of the data
	UPROPERTY()
	USaveHighScore* LoadedHighScore;

	bool RunningAsynchroneMethod;

	// Delegate used to store the callback when saving a slot
	FAsyncSaveHighScoreDelegate HighScoreSavedCallback;
	// Delegate given to UGameplayStatics::OnAsyncSaveHighScoreFinish when saving a high score
	FAsyncSaveGameToSlotDelegate HighScoreSavedDelegate;

	void OnAsyncSaveHighScoreFinish(const FString& SlotName, const int32 UserIndex, const bool saved);
};
