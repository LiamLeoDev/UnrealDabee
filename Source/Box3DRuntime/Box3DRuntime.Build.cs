// Copyright (c) 2026 LiamLeo

using UnrealBuildTool;
using System.IO;
public class Box3DRuntime : ModuleRules
{
	public Box3DRuntime(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		IWYUSupport = IWYUSupport.Full;
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "Box3DWrapper"});
		PrivateDependencyModuleNames.AddRange(new string[] {"DeveloperSettings"});
	}
}
