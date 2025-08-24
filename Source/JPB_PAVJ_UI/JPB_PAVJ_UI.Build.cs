// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class JPB_PAVJ_UI : ModuleRules
{
	public JPB_PAVJ_UI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
