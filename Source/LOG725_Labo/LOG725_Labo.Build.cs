// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LOG725_Labo : ModuleRules
{
	public LOG725_Labo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AIModule", "GameplayTasks", "UMG" });
    }
}
