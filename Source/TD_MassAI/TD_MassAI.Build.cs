// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TD_MassAI : ModuleRules
{
	public TD_MassAI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
