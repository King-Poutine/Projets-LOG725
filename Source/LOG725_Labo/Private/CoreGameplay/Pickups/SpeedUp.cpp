// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreGameplay/Pickups/SpeedUp.h"
#include "Characters/Virus.h"

void ASpeedUp::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AVirus* Virus = Cast<AVirus>(OtherActor);

	if (Virus)
	{
		OnPickedUp.Broadcast();

		Virus->ChangeMaxMoveSpeed(speedUpMaxMoveSpeed, speedUpDuration);

		Destroy();
	}
}