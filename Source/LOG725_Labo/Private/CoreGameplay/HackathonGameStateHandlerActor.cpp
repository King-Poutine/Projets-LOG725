// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreGameplay/HackathonGameStateHandlerActor.h"
#include "Blueprint/UserWidget.h"
#include "Characters/Virus.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerStates/VirusPlayerState.h"
#include "CoreGameplay/HighScoreSubsystem.h"

// Sets default values
AHackathonGameStateHandlerActor::AHackathonGameStateHandlerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AHackathonGameStateHandlerActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHackathonGameStateHandlerActor::OnVirusDeath()
{
	const auto PlayerState = UGameplayStatics::GetPlayerController(this->GetWorld(), 0)->GetPlayerState<AVirusPlayerState>();
	const auto NewLivesCount = PlayerState->GetLivesCount() - 1;

	UE_LOG(LogTemp, Warning, TEXT("Lives: %d -> %d"), PlayerState->GetLivesCount(), NewLivesCount);

    PlayerState->SetLivesCount(NewLivesCount);

	if(NewLivesCount > 0)
	{
		this->SpawnVirus();
	}
	else
	{
		this->ShowDefeatWidget();
	}
}

void AHackathonGameStateHandlerActor::ConnectGameEvents()
{
	//UE_LOG(LogTemp, Warning, TEXT("Attempting to connect events..."));
	if(this->VirusSpawner != nullptr)
	{
		this->VirusSpawner->OnVirusDeath.AddDynamic(this, &AHackathonGameStateHandlerActor::OnVirusDeath);
		//UE_LOG(LogTemp, Warning, TEXT("Connected events..."));
	}

	if(this->Portal != nullptr)
	{
		this->Portal->OnVirusReachPortal.AddDynamic(this, &AHackathonGameStateHandlerActor::OnWin);
	}

	if (this->SavedPointManager != nullptr)
	{
		this->SavedPointManager->OnVirusSaved.AddDynamic(this, &AHackathonGameStateHandlerActor::ChangeVirusSpawndLocation);
		UE_LOG(LogTemp, Warning, TEXT("Connect Event SavedManager"));
	}
}

void AHackathonGameStateHandlerActor::DisconnectGameEvents()
{
	if(this->VirusSpawner != nullptr)
	{
		this->VirusSpawner->OnVirusDeath.RemoveDynamic(this, &AHackathonGameStateHandlerActor::OnVirusDeath);
	}
}

void AHackathonGameStateHandlerActor::SpawnVirus()
{
	UE_LOG(LogTemp, Warning, TEXT("Attempting to spawn virus..."));
	const float WaitHandleTickRate = 0.1f;

    if(this->VirusSpawner != nullptr)
    {
		this->VirusSpawner->SpawnVirus();
		this->GetWorldTimerManager().SetTimer(this->WaitForVirusSpawnHandle, this, &AHackathonGameStateHandlerActor::WaitForVirusSpawn, WaitHandleTickRate, true, WaitHandleTickRate);
		UE_LOG(LogTemp, Warning, TEXT("Spawned virus..."));
    }
}

void AHackathonGameStateHandlerActor::WaitForVirusSpawn()
{
	UE_LOG(LogTemp, Warning, TEXT("Waiting for virus..."));

	const auto Virus = this->VirusSpawner->GetSpawnedVirus();

    if(this->VirusSpawner != nullptr && Virus != nullptr)
    {
		this->GetWorldTimerManager().ClearTimer(this->WaitForVirusSpawnHandle);
		Virus->SetInput(1);

		UE_LOG(LogTemp, Warning, TEXT("Found virus..."));

		if(this->Camera != nullptr)
		{
			this->Camera->Target = Virus;
			UE_LOG(LogTemp, Warning, TEXT("Updated camera target..."));
		}

		
    }
}

void AHackathonGameStateHandlerActor::BeginGame()
{
	if (this->VirusSpawner != nullptr)
	{
		this->SpawnVirus();
	}

	for(auto Spawner : this->AntiVirusSpawners)
	{
		Spawner->SpawnAntiVirus();
	}

	
}

void AHackathonGameStateHandlerActor::ShowTutorialWidget()
{
	if(this->TutorialWidget != nullptr)
	{
		const auto TutorialWidgetInstance = CreateWidget<UUserWidget>(this->GetWorld(), this->TutorialWidget);
		TutorialWidgetInstance->AddToViewport();
	}
}

void AHackathonGameStateHandlerActor::OnWin()
{
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UHighScoreSubsystem* highScoreSubsystem = GameInstance->GetSubsystem<UHighScoreSubsystem>();
	
	const auto PlayerState = UGameplayStatics::GetPlayerController(this->GetWorld(), 0)->GetPlayerState<AVirusPlayerState>();

	if (highScoreSubsystem->IsScoreHighEnough(PlayerState->GetScore()) && this->RequestNameWidget != nullptr)
	{
		RequestNameWidgetInstance = CreateWidget<UUserWidget>(this->GetWorld(), this->RequestNameWidget);
		RequestNameWidgetInstance->AddToViewport();
	}
	else
	{
		ShowVictoryWidget();
	}
}

void AHackathonGameStateHandlerActor::ConfirmName(FString name)
{
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UHighScoreSubsystem* highScoreSubsystem = GameInstance->GetSubsystem<UHighScoreSubsystem>();

	const auto PlayerState = UGameplayStatics::GetPlayerController(this->GetWorld(), 0)->GetPlayerState<AVirusPlayerState>();
	highScoreSubsystem->AddHighScore(name, PlayerState->GetScore());
	highScoreSubsystem->SaveHighScore();

	RequestNameWidgetInstance->RemoveFromParent();
	ShowVictoryWidget();
}

void AHackathonGameStateHandlerActor::ShowVictoryWidget()
{
	if(this->VictoryWidget != nullptr)
	{
		const auto VictoryWidgetInstance = CreateWidget<UUserWidget>(this->GetWorld(), this->VictoryWidget);
		VictoryWidgetInstance->AddToViewport();
	}
}

void AHackathonGameStateHandlerActor::ShowDefeatWidget()
{
	if(this->DefeatWidget != nullptr)
	{
		const auto DefeatWidgetInstance = CreateWidget<UUserWidget>(this->GetWorld(), this->DefeatWidget);
		DefeatWidgetInstance->AddToViewport();
	}
}

void AHackathonGameStateHandlerActor::ChangeVirusSpawndLocation(FVector Location)
{
	UE_LOG(LogTemp, Warning, TEXT("Change VirusSpawnerLocation"));
	this->VirusSpawner->SetActorLocation(Location);
}