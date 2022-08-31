// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CoreGameplay/HackathonCameraPawn.h"
#include "CoreGameplay/PlatformActor.h"
#include "GameFramework/PlayerController.h"
#include "HackathonPlayerControllerState.h"
#include "HackathonPlayerController.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlatformPlacedDelegate, APlatformActor*, Platform);

UCLASS()
class LOG725_LABO_API AHackathonPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	//max distance from the edge of the screen where the mouse moves the camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 CameraMoveBorderWidth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bShowPlatformPreview;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector PlaneOrigin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector PlaneNormal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class TSubclassOf<APlatformActor> PlatformActorClass;

	UPROPERTY(BlueprintReadOnly)
	    APlatformActor* SelectedPlatform;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void CreatePlatformPreview();

	UFUNCTION(BlueprintCallable)
		void ClearPlatformPreview();

	UFUNCTION(BlueprintCallable)
		void UpdatePlatformPreview() const;

	UFUNCTION(BlueprintCallable)
		void PlacePlatform();

    UFUNCTION(BlueprintCallable)
	    void UpdateCameraZoom(float Amount);

	UFUNCTION(BlueprintCallable)
		void SetState(EHackathonPlayerControllerState NewState);

	UFUNCTION(BlueprintCallable)
		EHackathonPlayerControllerState GetState();

	UPROPERTY(BlueprintAssignable)
		FPlatformPlacedDelegate OnPlatformPlaced;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	FVector ProjectMouseOnPlayArea() const;

	void GetCameraMoveDirection(FVector2D& DirectionBuffer) const;

	void RecenterCamera();

	void GetPlatformUnderCursor();

	void OnClick();

	AHackathonCameraPawn* Camera;

	FVector2D CameraMoveDirection;

	EHackathonPlayerControllerState State;
};
