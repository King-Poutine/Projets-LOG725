// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

class APickup;
class UBoxComponent;
class UStaticMeshComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGateOpenedPortal);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVirusReachPortal);

UCLASS()
class LOG725_LABO_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	APortal();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TArray<APickup*> NeededPickups;

	UPROPERTY(BlueprintAssignable, Category = "Portal")
	FGateOpenedPortal OnGateOpened;

	UPROPERTY(BlueprintAssignable, Category = "Portal")
	FVirusReachPortal OnVirusReachPortal;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPickedUp();

	void OpenGate();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	UBoxComponent* BoxComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* StaticMeshComponent;

	int nbrPickupCollected = 0;
};
