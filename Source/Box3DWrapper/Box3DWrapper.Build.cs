// Copyright (c) 2026 LiamLeo

using UnrealBuildTool;
using System.IO;
public class Box3DWrapper : ModuleRules
{
	public Box3DWrapper(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		IWYUSupport = IWYUSupport.Full;
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "TraceLog" });
		PrivateDependencyModuleNames.AddRange(new string[] { });

        string Box3DPath = Path.Combine(ModuleDirectory, "../../ThirdParty/Box3D");
		PublicIncludePaths.Add(Path.Combine(Box3DPath, "include"));
		// PrivateIncludePaths.Add(Path.Combine(Box3DPath, "src"));

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicAdditionalLibraries.Add(Path.Combine(Box3DPath, "lib", "Win", "box3d.lib"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            PublicAdditionalLibraries.Add(Path.Combine(Box3DPath, "lib", "Mac", "libbox3d.a"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Linux)
        {
            PublicAdditionalLibraries.Add(Path.Combine(Box3DPath, "lib", "Linux", "libbox3d.a"));
        }
        
		PublicDefinitions.Add("BOX3D_DOUBLE_PRECISION");
		PublicDefinitions.Add("B3_SECRET_COOKIE=1152023");
		
		PublicDefinitions.Add("BOX3D_ENABLE_ENSURES=1");
		// Use this to force ensure in Shipping:
		// PublicDefinitions.Add("BOX3D_FORCE_ENSURES_IN_SHIPPING=1");
	}
}
