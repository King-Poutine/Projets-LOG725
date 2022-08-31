// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DindowsWefenderController.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"

ADindowsWefenderController::ADindowsWefenderController()
{
	PrimaryActorTick.bCanEverTick = true;

	Bugging = 10.0f;
	MovementTypeRD = 0;
	RandTimer = FMath::FRandRange(1.0f, 5.0f);
}

void ADindowsWefenderController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	//UE_LOG(LogTemp, Warning, TEXT("Dindows Wefender Possess"));
	MyCharacter = Cast<ACharacter>(InPawn);

	if (MyCharacter == nullptr)
	{
		return;
	}

	InitializeController();
	GetWorldTimerManager().SetTimer(ChangeMovementTypeTimer, this, &ADindowsWefenderController::ChangeMovementType, RandTimer, false);
}

void ADindowsWefenderController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MyCharacter == nullptr)
	{
		return;
	}

	float Position = MyCharacter->GetActorLocation().Z;
	
	if (MovementTypeRD == 0)
	{
		if (Position >= FinalPosition)
		{
			Direction = FVector(0.0f, 0.0f, -1.0f);
		}
		else if (Position <= StartingPosition)
		{
			Direction = FVector(0.0f, 0.0f, 1.0f);
		}
		MyCharacter->AddMovementInput(Direction, 0.5);
	}
	else
	{
		Bugging = Bugging * -1.0f;
		MyCharacter->SetActorLocation(MyCharacter->GetActorLocation() + FVector(0.0f, 0.0f, Bugging));
	}
	
	
	
}

void ADindowsWefenderController::ChangeMovementType()
{

	UE_LOG(LogTemp, Warning, TEXT("Teleport"));
	FVector RandPosition = MyCharacter->GetActorLocation() + FVector(0.0f, 0.0f, FMath::FRandRange(StartingPosition, FinalPosition) - MyCharacter->GetActorLocation().Z);
	MyCharacter->SetActorLocation(RandPosition);
	MovementTypeRD = 0;
	RandTimer = FMath::FRandRange(1.0f, 5.0f);

	float again = FMath::FRandRange(0, 10);
	if (again >= 7)
	{
		MovementTypeRD = 1;
		RandTimer = FMath::FRandRange(1.0f, 2.0f);
	}

	GetWorldTimerManager().SetTimer(ChangeMovementTypeTimer, this, &ADindowsWefenderController::ChangeMovementType, RandTimer, false);
}

void ADindowsWefenderController::InitializeController()
{
	StartingPosition = MyCharacter->GetActorLocation().Z;
	FinalPosition = StartingPosition + Height;
	Direction = FVector(0.0f, 0.0f, 1.0f);
}
