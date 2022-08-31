// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreGameplay/FallingTrap.h"
#include "Components/BoxComponent.h"
#include "Engine/CollisionProfile.h"
#include "Characters/Virus.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"

// Sets default values
AFallingTrap::AFallingTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->VirusDetected = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("FallingTrap");
	BoxComponent->SetGenerateOverlapEvents(true);
	BoxComponent->SetCollisionProfileName("OverlapAllDynamic");
	SetRootComponent(BoxComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("FallingTrapMesh");
	StaticMeshComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	StaticMeshComponent->SetupAttachment(BoxComponent);

}

// Called when the game starts or when spawned
void AFallingTrap::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AFallingTrap::OnBeginOverlap);
}

void AFallingTrap::RayCast()
{

	FHitResult OutLeftHit;
	FHitResult OutCenterHit;
	FHitResult OutRightHit;

	FVector Start = this->GetActorLocation();
	FVector ForwardCenterVector = FVector(0.0f, 0.0f, -1.0f);
	FVector FowardLeftVector = FVector(0.0f, 0.1f, -1.0f);
	FVector FowardRightVector = FVector(0.0f, -0.1f, -1.0f);
	FowardLeftVector.Normalize();
	FowardRightVector.Normalize();
	FVector RightEnd = Start + (FowardRightVector * 5000.f);
	FVector LeftEnd = Start + (FowardLeftVector * 5000.f);
	FVector CenterEnd = Start + (ForwardCenterVector * 5000.f);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this->GetOwner());

	//Draw Debug Line
	/*
	DrawDebugLine(GetWorld(), Start, LeftEnd, FColor::Green, false, 1, 0, 1);
	DrawDebugLine(GetWorld(), Start, CenterEnd, FColor::Blue, false, 1, 0, 1);
	DrawDebugLine(GetWorld(), Start, RightEnd, FColor::Red, false, 1, 0, 1);
	*/

	bool LeftHit = GetWorld()->LineTraceSingleByChannel(OutLeftHit, Start, LeftEnd, ECC_Pawn, CollisionParams);
	bool CenterHit = GetWorld()->LineTraceSingleByChannel(OutCenterHit, Start, CenterEnd, ECC_Pawn, CollisionParams);
	bool RightHit = GetWorld()->LineTraceSingleByChannel(OutRightHit, Start, RightEnd, ECC_Pawn, CollisionParams);

	if (LeftHit)
	{
		AVirus* Virus = Cast<AVirus>(OutLeftHit.GetActor());
		//UE_LOG(LogTemp, Warning, TEXT("Actor : %s"), *OutLeftHit.GetActor()->GetName());
		if (Virus)
		{
			UE_LOG(LogTemp, Warning, TEXT("LeftHit true"));
			VirusDetected = true;
			GetWorldTimerManager().SetTimer(DestroyTimerHandler, this, &AFallingTrap::DestroyFallingTrap, 3.0f, false);
		}
	}
	if (CenterHit)
	{
		AVirus* Virus = Cast<AVirus>(OutCenterHit.GetComponent());
		//UE_LOG(LogTemp, Warning, TEXT("Actor : %s"), *OutCenterHit.GetActor()->GetName());
		if (Virus)
		{
			UE_LOG(LogTemp, Warning, TEXT("CenterHit true"));
			VirusDetected = true;
			GetWorldTimerManager().SetTimer(DestroyTimerHandler, this, &AFallingTrap::DestroyFallingTrap, 3.0f, false);
		}
	}
	if (RightHit)
	{
		AVirus* Virus = Cast<AVirus>(OutRightHit.GetActor());
		
		if (Virus)
		{
			UE_LOG(LogTemp, Warning, TEXT("RightHit true"));
			VirusDetected = true;
			GetWorldTimerManager().SetTimer(DestroyTimerHandler, this, &AFallingTrap::DestroyFallingTrap, 3.0f, false);
		}
	}

}

void AFallingTrap::DestroyFallingTrap()
{
	Destroy();
}

// Called every frame
void AFallingTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!VirusDetected)
	{
		RayCast();
	}
	else
	{
		this->SetActorLocation(this->GetActorLocation() + this->FallingSpeed * DeltaTime);
	}


}

void AFallingTrap::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AVirus* Virus = Cast<AVirus>(OtherActor);

	if (Virus)
	{
		Virus->Kill();
	}
}

