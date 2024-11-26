// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BidDemo : ModuleRules
{
	public BidDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "ALSV4_CPP", "UMG" });

        
    }
}
