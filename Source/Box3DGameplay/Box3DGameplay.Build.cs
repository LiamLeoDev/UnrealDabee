// Copyright (c) 2026 LiamLeo

using UnrealBuildTool;
using System.IO;
public class Box3DGameplay : ModuleRules
{
	public Box3DGameplay(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		IWYUSupport = IWYUSupport.Full;
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","Chaos","Box3DWrapper","Box3DRuntime"});
	}
}
