// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FallingTrap.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class LOG725_LABO_API AFallingTrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFallingTrap();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector FallingSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void RayCast();

	void DestroyFallingTrap();

	bool VirusDetected;

	FTimerHandle DestroyTimerHandler;

private:

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly)
		UBoxComponent* BoxComponent;

	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* StaticMeshComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
