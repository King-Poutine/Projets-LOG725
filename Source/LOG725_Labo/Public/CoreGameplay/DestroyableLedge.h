// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestroyableLedge.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class LOG725_LABO_API ADestroyableLedge : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestroyableLedge();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UStaticMeshComponent* StaticMeshComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly)
		UBoxComponent* BoxComponentBlock;

	UPROPERTY(EditDefaultsOnly)
		UBoxComponent* BoxComponentOverLap;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void DestroyLedge();

	virtual void DestroyLedge_Implementation();
};
