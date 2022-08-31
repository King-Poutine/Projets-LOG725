// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreGameplay/HighScoreSubsystem.h"

const FString UHighScoreSubsystem::HighScoreSaveName = TEXT("HighScore");

void UHighScoreSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	RunningAsynchroneMethod = false;

	HighScoreSavedDelegate.BindUObject(this, &UHighScoreSubsystem::OnAsyncSaveHighScoreFinish);

	LoadHighScore();
}

void UHighScoreSubsystem::Deinitialize()
{
	HighScoreSavedCallback.Clear();
}

bool UHighScoreSubsystem::LoadHighScore()
{
	if (RunningAsynchroneMethod)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't load the high score while the high score subsystem is running an asynchrone method"));
		return false;
	}

	if (DoesHighScoreExist())
	{
		// Retrieve and cast the USaveGame object to USaveHighScore
		LoadedHighScore = Cast<USaveHighScore>(UGameplayStatics::LoadGameFromSlot(HighScoreSaveName, 0));
	}
	else
	{
		// Create a new save
		LoadedHighScore = Cast<USaveHighScore>(UGameplayStatics::CreateSaveGameObject(USaveHighScore::StaticClass()));
	}

	return LoadedHighScore != nullptr;
}

bool UHighScoreSubsystem::SaveHighScore()
{
	if (RunningAsynchroneMethod)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't save the high score while the high score subsystem is running an asynchrone method"));
		return false;
	}

	if (LoadedHighScore == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("The high score is not loaded"));
		return false;
	}

	return UGameplayStatics::SaveGameToSlot(LoadedHighScore, HighScoreSaveName, 0);
	return false;
}

void UHighScoreSubsystem::AsyncSaveHighScore(const FAsyncSaveHighScoreDelegate& Callback)
{
	if (RunningAsynchroneMethod)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't save the high score while the high score subsystem is running an asynchrone method"));

		Callback.ExecuteIfBound(false);
		return;
	}

	if (LoadedHighScore == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("The high score is not loaded"));

		Callback.ExecuteIfBound(false);
		return;
	}

	RunningAsynchroneMethod = true;

	HighScoreSavedCallback = Callback;

	UGameplayStatics::AsyncSaveGameToSlot(LoadedHighScore, HighScoreSaveName, 0, HighScoreSavedDelegate);
}

void UHighScoreSubsystem::OnAsyncSaveHighScoreFinish(const FString& SlotName, const int32 UserIndex, const bool saved)
{
	RunningAsynchroneMethod = false;

	// Move the stored delegate to a local variable before executing it to avoid race conditions when executing the same method in response of the callback
	FAsyncSaveHighScoreDelegate tempDelegateCopy = HighScoreSavedCallback;
	HighScoreSavedCallback.Clear();

	tempDelegateCopy.ExecuteIfBound(saved);
}

bool UHighScoreSubsystem::DoesHighScoreExist() const
{
	return UGameplayStatics::DoesSaveGameExist(HighScoreSaveName, 0);
}

bool UHighScoreSubsystem::IsScoreHighEnough(int32 score) const
{
	if (LoadedHighScore == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("The high score is not loaded"));

		return false;
	}

	FHighScoreEntry* highScore;

	for (uint8 i = 0; i < MaxHighScoreCount; i++)
	{
		highScore = LoadedHighScore->HighScores.Find(i);

		if (highScore == nullptr || score > highScore->score)
		{
			return true;
		}
	}

	return false;
}

bool UHighScoreSubsystem::AddHighScore(FString name, int32 score)
{
	if (LoadedHighScore == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("The high score is not loaded"));

		return false;
	}

	if (score < 0)
	{
		score = 0;
	}

	TMap<uint8, FHighScoreEntry> oldHighScores = LoadedHighScore->HighScores;
	FHighScoreEntry* highScore;
	bool newHighScoreInserted = false;

	for(uint8 i = 0; i < MaxHighScoreCount; i++)
	{
		if (!newHighScoreInserted)
		{
			highScore = oldHighScores.Find(i);

			if (highScore == nullptr || score > highScore->score)
			{
				LoadedHighScore->HighScores.Add(i, FHighScoreEntry{ name, score });
				newHighScoreInserted = true;
			}

			if (highScore == nullptr)
			{
				break;
			}
		}
		else if (newHighScoreInserted)
		{
			highScore = oldHighScores.Find(i - 1);

			if (highScore == nullptr)
			{
				break;
			}

			LoadedHighScore->HighScores.Add(i, *highScore);
		}
	}

	return newHighScoreInserted;
}

TMap<uint8, FHighScoreEntry> UHighScoreSubsystem::GetHighScores()
{
	if (LoadedHighScore == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("The high score is not loaded"));

		return TMap<uint8, FHighScoreEntry>();
	}

	return LoadedHighScore->HighScores;
}

void UHighScoreSubsystem::ClearHighScores()
{
	if (LoadedHighScore == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("The high score is not loaded"));

		return;
	}

	LoadedHighScore->HighScores.Empty();
}