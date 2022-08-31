// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreGameplay/PlayAreaPlaneActor.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/HackathonPlayerController.h"

// Sets default values
APlayAreaPlaneActor::APlayAreaPlaneActor()
{
	this->DefaultNormal = FVector(0.0f, 0.0f, 1.0f);
}

// Called when the game starts or when spawned
void APlayAreaPlaneActor::BeginPlay()
{
	Super::BeginPlay();

	auto PC = Cast<AHackathonPlayerController>(UGameplayStatics::GetPlayerController(this->GetWorld(), 0));

	PC->PlaneOrigin = this->GetActorLocation();
	PC->PlaneNormal = this->GetActorRotation().RotateVector(this->DefaultNormal);

	UE_LOG(LogTemp, Warning, TEXT("PlayAreaPlane: - Position: %s - Normal: %s"), *PC->PlaneOrigin.ToString(), *PC->PlaneNormal.ToString());
}

