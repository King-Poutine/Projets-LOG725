// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreGameplay/PlatformActor.h"

//#pragma warning(disable: 4458)

// Sets default values
APlatformActor::APlatformActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->PlatformState = EPlatformState::Default;
}

// Called when the game starts or when spawned
void APlatformActor::BeginPlay()
{
	Super::BeginPlay();

	this->GetComponents<UStaticMeshComponent>(this->Meshes);

	//this->SetGhostState(true);
}

// Called every frame
void APlatformActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformActor::UpdatePosition(FVector& Location)
{

	this->SetActorLocation(Location);
	if (this->bSnapToGround)
	{
		this->bGrounded = this->SnapToGround(Location);
	}
	else
	{
		this->bGrounded = true;
	}

	//when in ghost state, check position validity
	if (this->PlatformState == EPlatformState::Ghost || this->PlatformState == EPlatformState::Ghost_Invalid)
	{
		TArray<AActor*> OverlappingActors;
		this->GetOverlappingActors(OverlappingActors);
		this->SetPositionValid(OverlappingActors.Num() == 0 && this->bGrounded);
		//UE_LOG(LogTemp, Warning, TEXT("OverlappingActors num : %d"), OverlappingActors.Num());
		//this->SetPositionValid(true);
	}
}


void APlatformActor::SetPositionValid(const bool PositionValid)
{
	if (this->PlatformState == EPlatformState::Ghost && PositionValid ||
		this->PlatformState == EPlatformState::Ghost_Invalid && !PositionValid) return;
	this->PlatformState = PositionValid ? EPlatformState::Ghost : EPlatformState::Ghost_Invalid;

	//if the position is not valid, tint the object red
	for (int32 i = 0; i < this->Meshes.Num(); i++)
	{
		const auto Mesh = this->Meshes[i];
		if (Mesh == nullptr) continue;

		Mesh->SetVectorParameterValueOnMaterials("Tint", PositionValid ? FVector(1, 1, 1) : FVector(1, 0, 0));
		Mesh->SetVectorParameterValueOnMaterials("TintBlend", PositionValid ? FVector(0.5f, 0.5f, 0.5f) : FVector(1, 1, 1));
	}
}

void APlatformActor::SetGhostState(const bool GhostState)
{
	if (this->PlatformState != EPlatformState::Default && GhostState ||
		this->PlatformState == EPlatformState::Default && !GhostState) return;
	this->PlatformState = GhostState ? EPlatformState::Ghost : EPlatformState::Default;

	//when in ghost state, the object is transparent and does not block other objects
	for (int32 i = 0; i < this->Meshes.Num(); i++)
	{
		const auto Mesh = this->Meshes[i];
		if (Mesh == nullptr) continue;

		Mesh->SetScalarParameterValueOnMaterials("Opacity", GhostState ? 0.5f : 1);
		Mesh->SetVectorParameterValueOnMaterials("TintBlend", GhostState ? FVector(0.5f, 0.5f, 0.5f) : FVector(0, 0, 0));
		Mesh->SetCollisionProfileName(GhostState ? this->PreviewCollisionPreset : this->DefaultCollisionPreset);
	}
}

EPlatformState APlatformActor::GetPlatformState() const
{
	return this->PlatformState;
}

int32 APlatformActor::GetPlacementCost() const
{
	return this->PlacementCost;
}

bool APlatformActor::SnapToGround(FVector& Location)
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery1); //World Static channel
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery7); //Platform channel

	FHitResult OutHit;

	const auto Result = this->GetWorld()->LineTraceSingleByObjectType(
		OutHit, 
		this->GetActorLocation(),
		Location - FVector(0, 0, this->MaxGroundDistance),
		ObjectTypes
	);

	if(Result)
	{
		this->SetActorLocation(OutHit.Location);
		return true;
	}

    return false;
}
