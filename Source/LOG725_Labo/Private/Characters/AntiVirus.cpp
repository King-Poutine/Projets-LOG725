// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AntiVirus.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/Virus.h"

void AAntiVirus::BeginPlay()
{
	Super::BeginPlay();

	originalMaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	originalMaxFlySpeed = GetCharacterMovement()->MaxFlySpeed;

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AAntiVirus::OnHit);
}

void AAntiVirus::ChangeMaxMoveSpeed_Implementation(float maxMoveSpeed, float duration)
{
	GetCharacterMovement()->MaxWalkSpeed = maxMoveSpeed;
	GetCharacterMovement()->MaxFlySpeed = maxMoveSpeed;

	GetWorldTimerManager().ClearTimer(ChangeMaxMoveSpeedTimerHandle);
	GetWorldTimerManager().SetTimer(ChangeMaxMoveSpeedTimerHandle, this, &AAntiVirus::RevertToOriginalMoveSpeed, duration);
}

void AAntiVirus::RevertToOriginalMoveSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = originalMaxWalkSpeed;
	GetCharacterMovement()->MaxFlySpeed = originalMaxFlySpeed;

	GetWorldTimerManager().ClearTimer(ChangeMaxMoveSpeedTimerHandle);
}

void AAntiVirus::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	AVirus* Virus = Cast<AVirus>(OtherActor);

	if (Virus)
	{
		Virus->Kill();
	}
}
