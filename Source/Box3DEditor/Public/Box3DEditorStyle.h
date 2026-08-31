// Copyright (c) 2026 LiamLeo

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

class FBox3DEditorStyle
{
public:
    static void Initialize();
    static void Shutdown();

    static const ISlateStyle& Get();
    static FName GetStyleSetName();

private:
    static TSharedRef<class FSlateStyleSet> Create();
    static TSharedPtr<class FSlateStyleSet> StyleInstance;
};