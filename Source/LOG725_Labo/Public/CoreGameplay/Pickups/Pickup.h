// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPickedUpDelegate);

UCLASS(Abstract)
class LOG725_LABO_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	APickup();

	UPROPERTY(BlueprintAssignable, Category = "Pickup")
	FPickedUpDelegate OnPickedUp;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	UBoxComponent* BoxComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent* StaticMeshComponent;
};
