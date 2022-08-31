// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreGameplay/HackathonCameraPawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AHackathonCameraPawn::AHackathonCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHackathonCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHackathonCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    this->MoveCamera(DeltaTime);
}

// Called to bind functionality to input
void AHackathonCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AHackathonCameraPawn::SetMoveDirection(FVector2D MoveDir)
{
    this->MoveDirection = MoveDir;
}

FVector2D AHackathonCameraPawn::GetMoveDirection() const
{
    return this->MoveDirection;
}

void AHackathonCameraPawn::Zoom(float Amount)
{
    if (Amount == 0) return;

    const auto Rotation = this->GetActorRotation();
    const auto CameraForward = Rotation.RotateVector(FVector(1, 0, 0));

    auto NewPosition = this->GetActorLocation() + CameraForward * this->ZoomScale * Amount;
    NewPosition = ClampVector(NewPosition, InnerBound, OuterBound);

    this->SetActorLocation(NewPosition);
}

void AHackathonCameraPawn::MoveCamera(float DeltaTime)
{
    const auto Rotation = this->GetActorRotation();
    const auto CameraUp = Rotation.RotateVector(FVector(0, 0, 1));
    const auto CameraRight = Rotation.RotateVector(FVector(0, 1, 0));

    FVector WorldDir = FVector(0, 0, 0);
    WorldDir += CameraRight * this->MoveDirection.X;
    WorldDir += CameraUp * this->MoveDirection.Y;

    auto NewPosition = this->GetActorLocation() + WorldDir * this->MoveSpeed * DeltaTime;
    NewPosition = ClampVector(NewPosition, InnerBound, OuterBound);

    this->SetActorLocation(NewPosition);
}

void AHackathonCameraPawn::RecenterOnTarget()
{
    if(this->Target == nullptr)
    {
        return;
    }

    const auto Rotation = this->GetActorRotation();
    const auto CameraForward = Rotation.RotateVector(FVector(1, 0, 0));
    auto Distance = this->Target->GetActorLocation() - this->GetActorLocation();
    //don't modify zoom level
    Distance -= Distance.ProjectOnTo(CameraForward);

    auto NewPosition = this->GetActorLocation() + Distance;
    NewPosition = ClampVector(NewPosition, InnerBound, OuterBound);

    this->SetActorLocation(NewPosition);
}
