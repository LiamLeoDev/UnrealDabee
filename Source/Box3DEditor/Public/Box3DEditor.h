// Copyright (c) 2026 LiamLeo

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FBox3DEditorModule : public IModuleInterface
{
public:

    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
private:
    void HandleMapOpened(const FString& Filename, bool bAsTemplate);
    FDelegateHandle MapOpenedHandle;

    void HandlePostUndoRedo();
    FDelegateHandle PostUndoRedoDelegateHandle;


    void RegisterMenus();
    static TSharedRef<class SWidget> GenerateMenuContent();
    
    static void ShowProfile();
    static bool IsShowProfile();

    static void ShowCounter();
    static bool IsShowCounter();
    
    static FReply OnDiscordClicked();
    static FReply OpenSupportClicked();
};