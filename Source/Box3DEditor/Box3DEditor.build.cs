// Copyright (c) 2026 LiamLeo

using UnrealBuildTool;

public class Box3DEditor : ModuleRules
{
    public Box3DEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        IWYUSupport = IWYUSupport.Full;
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core"
            });

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",

                "Box3DRuntime",
                "Box3DGameplay",

                "UnrealEd",
                "AssetTools",
                "AssetDefinition",
                "Slate",
                "SlateCore",
                "EditorFramework",
                "Projects",
                "ToolMenus"
            });
    }
}