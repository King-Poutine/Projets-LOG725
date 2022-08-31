// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SavePoint.h"
#include "GameFramework/Actor.h"
#include "SavedPointManager.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FVirusSavedPointDelegate, FVector, SavedPointLocation);

UCLASS()
class LOG725_LABO_API ASavedPointManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASavedPointManager();

	UPROPERTY(BlueprintAssignable)
		FVirusSavedPointDelegate OnVirusSaved;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ASavePoint*> SavePointList;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnSavePointSaved(ASavePoint* SavePoint);

	UPROPERTY(EditDefaultsOnly)
		ASavePoint* SavedPoint;

};
