// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SavePoint.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UMaterialInterface;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FVirusSavePointDelegate, ASavePoint*, SavedPoint);

UCLASS()
class LOG725_LABO_API ASavePoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASavePoint();

	UPROPERTY(BlueprintAssignable)
		FVirusSavePointDelegate OnVirusSave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInterface* ActiveFlag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInterface* NonActiveFlag;

	UFUNCTION(BlueprintCallable)
		void UnSave();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly)
		UBoxComponent* BoxComponent;

	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* StaticMeshComponent;

};
