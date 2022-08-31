// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AntiVirusSpawner.h"
#include "Portal.h"
#include "VirusSpawner.h"
#include "SavedPointManager.h"
#include "HackathonCameraPawn.h"
#include "GameFramework/Actor.h"
#include "HackathonGameStateHandlerActor.generated.h"

UCLASS()
class LOG725_LABO_API AHackathonGameStateHandlerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHackathonGameStateHandlerActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AHackathonCameraPawn* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	    AVirusSpawner* VirusSpawner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	    APortal* Portal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ASavedPointManager* SavedPointManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	    TArray<AAntiVirusSpawner*> AntiVirusSpawners;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UUserWidget> TutorialWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UUserWidget> RequestNameWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	    TSubclassOf<UUserWidget> VictoryWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UUserWidget> DefeatWidget;

	UFUNCTION(BlueprintCallable)
	    void ConnectGameEvents();

	UFUNCTION(BlueprintCallable)
	    void DisconnectGameEvents();

	UFUNCTION(BlueprintCallable)
		void BeginGame();

	UFUNCTION(BlueprintCallable)
		void ShowTutorialWidget();

	UFUNCTION(BlueprintCallable)
		void ConfirmName(FString name);

	UFUNCTION(BlueprintCallable)
	    void ShowVictoryWidget();

	UFUNCTION(BlueprintCallable)
		void ShowDefeatWidget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnVirusDeath();

	void SpawnVirus();

	void WaitForVirusSpawn();

	UFUNCTION()
	void ChangeVirusSpawndLocation(FVector Location);

	UFUNCTION()
	void OnWin();

	FTimerHandle WaitForVirusSpawnHandle;

	UUserWidget* RequestNameWidgetInstance;
};
