// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreGameplay/Pickups/SlowDown.h"
#include "Characters/Virus.h"
#include "EngineUtils.h"
#include "Characters/AntiVirus.h"

void ASlowDown::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AVirus* Virus = Cast<AVirus>(OtherActor);

	if (Virus)
	{
		OnPickedUp.Broadcast();
		
		for (TActorIterator<AAntiVirus> It(GetWorld()); It; ++It)
		{
			AAntiVirus* AntiVirus = *It;
			AntiVirus->ChangeMaxMoveSpeed(slowDownMaxMoveSpeed, slowDownDuration);
		}

		Destroy();
	}
}