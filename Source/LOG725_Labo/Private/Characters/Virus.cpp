// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Virus.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Actor.h"

AVirus::AVirus()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1200.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 1700.f;
	GetCharacterMovement()->MaxFlySpeed = 1200.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void AVirus::BeginPlay()
{
	Super::BeginPlay();

	originalMaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AVirus::OnHit);
}

void AVirus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveRight(MoveDirection * MoveInput);
}

void AVirus::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f, 1.f, 0.f), Value);
}

void AVirus::SetInput(float Input)
{
	MoveInput = Input;
}

void AVirus::FlipDirection()
{
	MoveDirection *= -1.f;
}

void AVirus::ChangeMaxMoveSpeed_Implementation(float maxMoveSpeed, float duration)
{
	GetCharacterMovement()->MaxWalkSpeed = maxMoveSpeed;

	GetWorldTimerManager().ClearTimer(ChangeMaxMoveSpeedTimerHandle);
	GetWorldTimerManager().SetTimer(ChangeMaxMoveSpeedTimerHandle, this, &AVirus::RevertToOriginalMoveSpeed, duration);
}

void AVirus::RevertToOriginalMoveSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = originalMaxWalkSpeed;

	GetWorldTimerManager().ClearTimer(ChangeMaxMoveSpeedTimerHandle);
}

void AVirus::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (abs(Hit.ImpactNormal.Z) <= MaxNomralZToTurn)
	{
		FlipDirection();
	}
}

void AVirus::Kill_Implementation()
{
	OnDeath.Broadcast();
	Destroy();
}

void AVirus::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	
}

FGenericTeamId AVirus::GetGenericTeamId() const
{
	return FGenericTeamId(0);
}
