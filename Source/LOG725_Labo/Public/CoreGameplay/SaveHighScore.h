// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveHighScore.generated.h"

USTRUCT(BlueprintType)
struct FHighScoreEntry
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "HighScore")
	FString name;

	UPROPERTY(BlueprintReadOnly, Category = "HighScore")
	int32 score;
};

UCLASS()
class LOG725_LABO_API USaveHighScore : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TMap<uint8, FHighScoreEntry> HighScores;
};
