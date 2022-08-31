// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HackathonCameraPawn.generated.h"

UCLASS()
class LOG725_LABO_API AHackathonCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHackathonCameraPawn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ZoomScale;

	// location constraint
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	    FVector InnerBound;

	// location constraint
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	    FVector OuterBound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* Target;

	UFUNCTION(BlueprintCallable)
	    FVector2D GetMoveDirection() const;

	UFUNCTION(BlueprintCallable)
	    void Zoom(float Amount);

	UFUNCTION(BlueprintCallable)
	    void SetMoveDirection(FVector2D MoveDir);

	UFUNCTION(BlueprintCallable)
		void RecenterOnTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveCamera(float DeltaTime);

	FVector2D MoveDirection;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
