// Copyright (c) 2026 LiamLeo

#include "Box3DEditorStyle.h"

#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Interfaces/IPluginManager.h"
#include "Slate/SlateGameResources.h"
#include "Brushes/SlateRoundedBoxBrush.h"

#define IMAGE_BRUSH(RelativePath, ...) FSlateImageBrush(StyleSet->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)

TSharedPtr<FSlateStyleSet> FBox3DEditorStyle::StyleInstance = nullptr;

void FBox3DEditorStyle::Initialize()
{
    if (!StyleInstance.IsValid())
    {
        StyleInstance = Create();
        FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
        FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
    }
}

void FBox3DEditorStyle::Shutdown()
{
    if (StyleInstance.IsValid())
    {
        FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
        StyleInstance.Reset();
    }
}

FName FBox3DEditorStyle::GetStyleSetName()
{
    static FName StyleSetName(TEXT("Box3DEditorStyle"));
    return StyleSetName;
}

const FVector2D Icon20x20(20.0f, 20.0f);
const FVector2D Icon40x40(40.0f, 40.0f);

TSharedRef<FSlateStyleSet> FBox3DEditorStyle::Create()
{
    TSharedRef<FSlateStyleSet> StyleSet = MakeShareable(new FSlateStyleSet(GetStyleSetName()));
    StyleSet->SetContentRoot(IPluginManager::Get().FindPlugin(TEXT("UnrealDabee"))->GetBaseDir() / TEXT("Source/Box3DEditor/Resources"));
    StyleSet->Set("Box3DEditor.ToolbarIcon", new IMAGE_BRUSH(TEXT("Box3DIcon128"), Icon20x20));
    StyleSet->Set("Box3DEditor.DiscordIcon", new IMAGE_BRUSH(TEXT("DiscordIcon128"), Icon20x20));
    StyleSet->Set("Box3DEditor.HeartIcon", new IMAGE_BRUSH(TEXT("HeartIcon128"), Icon20x20));


    FButtonStyle DiscordButtonStyle = FButtonStyle()
    .SetNormal(FSlateRoundedBoxBrush(FLinearColor(FColor::FromHex(TEXT("#5865F2"))), 6.0f, FLinearColor(FColor::FromHex(TEXT("#4752C4"))), 1.0f))
    .SetHovered(FSlateRoundedBoxBrush(FLinearColor(FColor::FromHex(TEXT("#4752C4"))), 6.0f, FLinearColor(FColor::FromHex(TEXT("#3C45A5"))), 1.5f))
    .SetPressed(FSlateRoundedBoxBrush(FLinearColor(FColor::FromHex(TEXT("#3C45A5"))), 6.0f, FLinearColor(FColor::FromHex(TEXT("#2F3784"))), 2.0f))
    .SetNormalForeground(FLinearColor::White)
    .SetHoveredForeground(FLinearColor(0.9f, 0.9f, 0.9f, 1.f))
    .SetPressedForeground(FLinearColor(0.7f, 0.7f, 0.7f, 1.f))
    .SetNormalPadding(FMargin(10.0f, 6.0f))
    .SetPressedPadding(FMargin(10.0f, 7.0f, 10.0f, 5.0f));

    StyleSet->Set("Box3DEditor.DiscordButton", DiscordButtonStyle);

    FButtonStyle SupportButtonStyle = FButtonStyle()
    .SetNormal(FSlateRoundedBoxBrush(FLinearColor(FColor::FromHex(TEXT("#FF3B5C"))), 6.0f, FLinearColor(FColor::FromHex(TEXT("#D62443"))), 1.0f))
    .SetHovered(FSlateRoundedBoxBrush(FLinearColor(FColor::FromHex(TEXT("#FF5E7A"))), 6.0f, FLinearColor(FColor::FromHex(TEXT("#FF3B5C"))), 1.5f))
    .SetPressed(FSlateRoundedBoxBrush(FLinearColor(FColor::FromHex(TEXT("#D62443"))), 6.0f, FLinearColor(FColor::FromHex(TEXT("#A6132C"))), 2.0f))
    .SetNormalForeground(FLinearColor::White)
    .SetHoveredForeground(FLinearColor(0.9f, 0.9f, 0.9f, 1.f))
    .SetPressedForeground(FLinearColor(0.7f, 0.7f, 0.7f, 1.f))
    .SetNormalPadding(FMargin(10.0f, 6.0f))
    .SetPressedPadding(FMargin(10.0f, 7.0f, 10.0f, 5.0f));

    StyleSet->Set("Box3DEditor.SupportButton", SupportButtonStyle);

    return StyleSet;
}


const ISlateStyle& FBox3DEditorStyle::Get()
{
    return *StyleInstance;
}

#undef IMAGE_BRUSH