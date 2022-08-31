// Copyright Epic Games, Inc. All Rights Reserved.

#include "LOG725_LaboGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "PlayerControllers/HackathonPlayerController.h"
#include "PlayerStates/VirusPlayerState.h"

ALOG725_LaboGameMode::ALOG725_LaboGameMode()
{
	// no default pawn class
	DefaultPawnClass = NULL;

	// set default player controller class from blueprint
	static ConstructorHelpers::FClassFinder<AHackathonPlayerController> HackathonPlayerControllerBPClass(TEXT("/Game/Hackathon/Gameplay/BP_HackathonPlayerController"));
	if (HackathonPlayerControllerBPClass.Class != nullptr)
	{
		this->PlayerControllerClass = HackathonPlayerControllerBPClass.Class;
	}

	// set default player state class from blueprint
	static ConstructorHelpers::FClassFinder<AVirusPlayerState> VirusPlayerStateBPClass(TEXT("/Game/Hackathon/Gameplay/BP_VirusPlayerState"));
	if (VirusPlayerStateBPClass.Class != nullptr)
	{
		this->PlayerStateClass = VirusPlayerStateBPClass.Class;
	}
}
