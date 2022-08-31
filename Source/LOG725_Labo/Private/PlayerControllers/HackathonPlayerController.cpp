// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/HackathonPlayerController.h"

#include "CoreGameplay/HackathonCameraPawn.h"
#include "PlayerStates/VirusPlayerState.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"

void AHackathonPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    this->InputComponent->BindAction("PlacePlatform", IE_Pressed, this, &AHackathonPlayerController::OnClick);
    this->InputComponent->BindAxis("Zoom", this, &AHackathonPlayerController::UpdateCameraZoom);
    this->InputComponent->BindAxis("CameraHorizontal");
    this->InputComponent->BindAxis("CameraVertical");
    this->InputComponent->BindAction("CameraRecenter", IE_Pressed, this, &AHackathonPlayerController::RecenterCamera);
}

void AHackathonPlayerController::BeginPlay()
{
    this->bShowMouseCursor = true;
    this->Camera = Cast<AHackathonCameraPawn>(this->GetPawn());
}

void AHackathonPlayerController::Tick(float DeltaTime)
{
    // debug mouse pos
    //auto mousePos = this->ProjectMouseOnPlayArea();
    //UE_LOG(LogTemp, Warning, TEXT("Projected mouse pos: %s"), *mousePos.ToString());

    if(this->Camera != nullptr)
    {
        this->GetCameraMoveDirection(this->CameraMoveDirection);
        this->Camera->SetMoveDirection(this->CameraMoveDirection);
        //UE_LOG(LogTemp, Warning, TEXT("%s"), *this->CameraMoveDirection.ToString());    
    }

    switch (this->State) {
        case EHackathonPlayerControllerState::Place_Platform:
            if (this->bShowPlatformPreview)
            {
                //auto preview
                if (this->SelectedPlatform == nullptr)
                {
                    this->CreatePlatformPreview();
                }

                this->UpdatePlatformPreview();
            }
            else
            {
                this->ClearPlatformPreview();
            }
            break;
        case EHackathonPlayerControllerState::Delete_Platform:
            this->GetPlatformUnderCursor();
            break;
        case EHackathonPlayerControllerState::Default:
        default:
            break;
    }    
}

// Project the mouse position to a plane aligned with the stage depth and orientation
FVector AHackathonPlayerController::ProjectMouseOnPlayArea() const
{
    FVector WorldLoc;
    FVector WorldDir;
    const FPlane Plane(this->PlaneOrigin, this->PlaneNormal);

    this->DeprojectMousePositionToWorld(WorldLoc, WorldDir);

    return FMath::RayPlaneIntersection(WorldLoc, WorldDir, Plane);
}

//create a platform in the ghost state at the mouse position
void AHackathonPlayerController::CreatePlatformPreview()
{
    this->ClearPlatformPreview();

    //spawn an object at mouse position

    const FVector Location = this->ProjectMouseOnPlayArea();
    const FRotator Rotation = FRotator(0, 0, 0);

    FActorSpawnParameters SpawnParameters;
    SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    //debug spawn
    //UE_LOG(LogTemp, Warning, TEXT("Spawn actor at: %s"), *Location.ToString());

    if(this->PlatformActorClass == nullptr)
    {
        //UE_LOG(LogTemp, Error, TEXT("Cannot instantiate platform as no platform actor was defined"));
        return;
    }
    
    const auto Actor = this->GetWorld()->SpawnActor(this->PlatformActorClass, &Location, &Rotation, SpawnParameters);
    this->SelectedPlatform = Cast<APlatformActor>(Actor);
    this->SelectedPlatform->SetGhostState(true);
}

//remove the ghost platform
void AHackathonPlayerController::ClearPlatformPreview()
{
    if (this->SelectedPlatform != nullptr)
    {
        this->SelectedPlatform->Destroy();
        this->SelectedPlatform = nullptr;
    }
}

//move the platform preview under the mouse
void AHackathonPlayerController::UpdatePlatformPreview() const
{
    if (this->SelectedPlatform == nullptr) return;

    FVector Location = this->ProjectMouseOnPlayArea();
    this->SelectedPlatform->UpdatePosition(Location);
}

//turn the platform preview into a "real" platform by removing the ghost state and stop tracking it
void AHackathonPlayerController::PlacePlatform()
{
    if (this->SelectedPlatform == nullptr || 
        this->SelectedPlatform->GetPlatformState() == EPlatformState::Ghost_Invalid) return;

    this->SelectedPlatform->SetGhostState(false);

    const auto PS = this->GetPlayerState<AVirusPlayerState>();
    PS->SetSpentFunds(PS->GetSpentFunds() + this->SelectedPlatform->GetPlacementCost());

    this->OnPlatformPlaced.Broadcast(this->SelectedPlatform);

    this->SelectedPlatform = nullptr;
}

void AHackathonPlayerController::GetCameraMoveDirection(FVector2D& DirectionBuffer) const
{
    float mouseX;
    float mouseY;
    int32 sizeX;
    int32 sizeY;

    if(this->GetMousePosition(mouseX, mouseY))
    {
        this->GetViewportSize(sizeX, sizeY);
        DirectionBuffer.X = mouseX < this->CameraMoveBorderWidth ? -1 : mouseX > sizeX - this->CameraMoveBorderWidth ? 1 : 0;
        DirectionBuffer.Y = mouseY < this->CameraMoveBorderWidth ? 1 : mouseY > sizeY - this->CameraMoveBorderWidth ? -1 : 0;
    }
    //mouse outside viewport
    else
    {
        DirectionBuffer.X = 0;
        DirectionBuffer.Y = 0;
    }

    //wasd overrides mouse movement
    const auto CameraHorizontalValue = this->InputComponent->GetAxisValue("CameraHorizontal");
    const auto CameraVerticalValue = this->InputComponent->GetAxisValue("CameraVertical");
    //UE_LOG(LogTemp, Warning, TEXT("WASD: %f %f"), CameraHorizontalValue, CameraVerticalValue);
    DirectionBuffer.X = CameraHorizontalValue != 0 ? CameraHorizontalValue : DirectionBuffer.X;
    DirectionBuffer.Y = CameraVerticalValue != 0 ? CameraVerticalValue : DirectionBuffer.Y;
}

void AHackathonPlayerController::UpdateCameraZoom(float Amount)
{
    if(this->Camera != nullptr)
    {
        this->Camera->Zoom(Amount);
    }
}

void AHackathonPlayerController::SetState(EHackathonPlayerControllerState NewState)
{
    if (this->State == NewState) return;

    if(this->State == EHackathonPlayerControllerState::Place_Platform)
    {
        this->ClearPlatformPreview();
    }

    this->State = NewState;
}

EHackathonPlayerControllerState AHackathonPlayerController::GetState()
{
    return this->State;
}

void AHackathonPlayerController::GetPlatformUnderCursor()
{
    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery7); //Platform channel
    FHitResult HitResult;
    this->GetHitResultUnderCursorForObjects(ObjectTypes, true, HitResult);

    if (HitResult.IsValidBlockingHit())
    {
        //UE_LOG(LogTemp, Warning, TEXT("%s"), *HitResult.GetActor()->GetName());
        const auto Platform = Cast<APlatformActor>(HitResult.GetActor());
        this->SelectedPlatform = Platform;
    }
    else
    {
        this->SelectedPlatform = nullptr;
    }
}

void AHackathonPlayerController::OnClick()
{
    switch (this->State) {
        case EHackathonPlayerControllerState::Place_Platform:
            UE_LOG(LogTemp, Warning, TEXT("Place Platform"));
            this->PlacePlatform();
            break;
        case EHackathonPlayerControllerState::Delete_Platform:
            UE_LOG(LogTemp, Warning, TEXT("Delete Platform"));
            this->ClearPlatformPreview();
            break;
        case EHackathonPlayerControllerState::Default: 
        default:
            break;
    }
}

void AHackathonPlayerController::RecenterCamera()
{
    if(this->Camera != nullptr)
    {
        this->Camera->RecenterOnTarget();
    }
}

