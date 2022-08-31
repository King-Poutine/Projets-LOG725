// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlatformState.h"
#include "GameFramework/Actor.h"
#include "PlatformActor.generated.h"



UCLASS()
class LOG725_LABO_API APlatformActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 PlacementCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName PreviewCollisionPreset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName DefaultCollisionPreset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bSnapToGround;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MaxGroundDistance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetPositionValid(const bool PositionValid);

	//Attempt to snap the platform to the ground. Returns false if the ground is too far.
	bool SnapToGround(FVector& Location);

	TArray<UStaticMeshComponent*> Meshes;

	EPlatformState PlatformState;

	bool bGrounded;


public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	    void SetGhostState(const bool GhostState);

	UFUNCTION(BlueprintCallable)
	    EPlatformState GetPlatformState() const;

	UFUNCTION(BlueprintCallable)
		int32 GetPlacementCost() const;

	UFUNCTION(BlueprintCallable)
		void UpdatePosition(FVector& Location);

};
