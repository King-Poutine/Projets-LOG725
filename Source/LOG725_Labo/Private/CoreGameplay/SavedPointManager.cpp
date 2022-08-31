// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreGameplay/SavedPointManager.h"

// Sets default values
ASavedPointManager::ASavedPointManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASavedPointManager::BeginPlay()
{
	Super::BeginPlay();

	for (ASavePoint* SavePoint : SavePointList)
	{
		SavePoint->OnVirusSave.AddDynamic(this, &ASavedPointManager::OnSavePointSaved);
	}
	
}

void ASavedPointManager::OnSavePointSaved(ASavePoint* SavePoint)
{
	if (this->SavedPoint == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Change SavedPoint"));
		this->SavedPoint = SavePoint;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Change SavedPoint"));
		this->SavedPoint->UnSave();
		this->SavedPoint = SavePoint;
	}
	UE_LOG(LogTemp, Warning, TEXT("Change SavedPoint BroadCast"));
	OnVirusSaved.Broadcast(this->SavedPoint->GetActorLocation());
}



