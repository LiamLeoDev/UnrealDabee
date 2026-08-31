// Copyright (c) 2026 LiamLeo

#include "Box3DEditor.h"

#include "Editor.h"
#include "Editor/EditorEngine.h"
#include "Engine/World.h"
#include "Box3DStaticCollisionSubsystem.h"
#include "Box3DWorldSubsystem.h"

#include "ToolMenus.h"
#include "ToolMenuSection.h"
#include "ToolMenuEntry.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "HAL/PlatformProcess.h"

#include "Box3DEditorStyle.h"

#include "Widgets/Input/SButton.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "FBox3DEditorModule"

void FBox3DEditorModule::StartupModule()
{
    MapOpenedHandle = FEditorDelegates::OnMapOpened.AddRaw(this, &FBox3DEditorModule::HandleMapOpened);
    PostUndoRedoDelegateHandle = FEditorDelegates::PostUndoRedo.AddRaw(this, &FBox3DEditorModule::HandlePostUndoRedo);

    FBox3DEditorStyle::Initialize();
    UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FBox3DEditorModule::RegisterMenus));
}

void FBox3DEditorModule::ShutdownModule()
{   
    FEditorDelegates::OnMapOpened.Remove(MapOpenedHandle);
    FEditorDelegates::PostUndoRedo.Remove(PostUndoRedoDelegateHandle);

    FBox3DEditorStyle::Shutdown();
	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);
}

void FBox3DEditorModule::HandleMapOpened(const FString& Filename, bool bAsTemplate)
{
    if (GEditor)
    {
        if (UWorld* EditorWorld = GEditor->GetEditorWorldContext().World())
        {
            if(UBox3DStaticCollisionSubsystem* Subsystem = EditorWorld->GetSubsystem<UBox3DStaticCollisionSubsystem>())
            {
                Subsystem->ScanExistingActors();
            }
        }
    }
}

void FBox3DEditorModule::HandlePostUndoRedo()
{
    if (GEditor)
    {
        if (UWorld* EditorWorld = GEditor->GetEditorWorldContext().World())
        {
            if(UBox3DStaticCollisionSubsystem* Subsystem = EditorWorld->GetSubsystem<UBox3DStaticCollisionSubsystem>())
            {
                Subsystem->DoUndoAndRedo();
            }
        }
    }
}




void FBox3DEditorModule::RegisterMenus()
{
    FToolMenuOwnerScoped OwnerScoped(this);
    if( UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar"))
    {
        FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Box3D");
        FToolMenuEntry Entry = FToolMenuEntry::InitComboButton(
            "Box3DToolbarMenu",
            FUIAction(),
            FOnGetContent::CreateStatic(&FBox3DEditorModule::GenerateMenuContent),
            LOCTEXT("Box3DMenuLabel", "Box3D"),
            LOCTEXT("Box3DMenuTooltip", "Box3D support, help and debug options"),
            FSlateIcon(FBox3DEditorStyle::GetStyleSetName(), "Box3DEditor.ToolbarIcon")
        );
        Entry.StyleNameOverride = "CalloutToolbar";
        Section.AddEntry(Entry);
    }
}

TSharedRef<SWidget> FBox3DEditorModule::GenerateMenuContent()
{
	FMenuBuilder MenuBuilder(true, nullptr);
	MenuBuilder.BeginSection("Box3DSupport", LOCTEXT("Box3DHelpAndSupportSection", "Support"));
	{
		MenuBuilder.AddWidget(
            SNew(SBox)
            .HAlign(HAlign_Fill)
            .Padding(FMargin(2.0f, 2.0f))
            [
                SNew(SButton)
                .ButtonStyle(&FBox3DEditorStyle::Get()
                .GetWidgetStyle<FButtonStyle>("Box3DEditor.DiscordButton"))
                .Cursor(EMouseCursor::Hand)
                .HAlign(HAlign_Fill)
                .OnClicked_Static(&FBox3DEditorModule::OnDiscordClicked)
                [
                    SNew(SHorizontalBox)
                    + SHorizontalBox::Slot()
                    .AutoWidth()
                    .VAlign(VAlign_Center)
                    [
                        SNew(SImage)
                        .Image(FSlateIcon(FBox3DEditorStyle::GetStyleSetName(), "Box3DEditor.DiscordIcon").GetIcon())
                    ] 
                    + SHorizontalBox::Slot()
                    .AutoWidth()
                    .VAlign(VAlign_Center)
                    .Padding(FMargin(6.0f, 0.0f, 0.0f, 0.0f))[SNew(STextBlock).Text(LOCTEXT("DiscordLabel", "Get Help"))]
                ]
            ],
            FText::GetEmpty(),
            true,
            false
        );

        MenuBuilder.AddWidget(
            SNew(SBox)
            .HAlign(HAlign_Fill)
            .Padding(FMargin(2.0f, 2.0f))
            [
                SNew(SButton)
                .ButtonStyle(&FBox3DEditorStyle::Get().GetWidgetStyle<FButtonStyle>("Box3DEditor.SupportButton"))
                .Cursor(EMouseCursor::Hand)
                .HAlign(HAlign_Fill)
                .OnClicked_Static(&FBox3DEditorModule::OpenSupportClicked)
                [
                    SNew(SHorizontalBox)
                    + SHorizontalBox::Slot()
                    .AutoWidth()
                    .VAlign(VAlign_Center)
                    [
                        SNew(SImage)
                        .Image(FSlateIcon(FBox3DEditorStyle::GetStyleSetName(), "Box3DEditor.HeartIcon").GetIcon())
                    ] 
                    + SHorizontalBox::Slot()
                    .AutoWidth()
                    .VAlign(VAlign_Center)
                    .Padding(FMargin(6.0f, 0.0f, 0.0f, 0.0f))[SNew(STextBlock).Text(LOCTEXT("DiscordLabel", "Support Development"))]
                ]
            ],
            FText::GetEmpty(),
            true,
            false
        );
	}

	MenuBuilder.EndSection();

	MenuBuilder.BeginSection("Box3DDebug", LOCTEXT("Box3DDebugSection", "Debug"));
	{
		MenuBuilder.AddMenuEntry(
			LOCTEXT("Box3DShowStatsLabel", "Show Profiling"),
			LOCTEXT("Box3DShowStatsTooltip", "Toggle Box3D Profiling on screen"),
			FSlateIcon(),
			FUIAction(
				FExecuteAction::CreateStatic(&FBox3DEditorModule::ShowProfile),
				FCanExecuteAction(),
				FIsActionChecked::CreateStatic(&FBox3DEditorModule::IsShowProfile)
			),
			NAME_None,
			EUserInterfaceActionType::ToggleButton
		);

		MenuBuilder.AddMenuEntry(
			LOCTEXT("Box3DForceAssertsLabel", "Show Counters"),
			LOCTEXT("Box3DForceAssertsTooltip", "Toggle Box3D World Counters on screen"),
			FSlateIcon(),
			FUIAction(
				FExecuteAction::CreateStatic(&FBox3DEditorModule::ShowCounter),
				FCanExecuteAction(),
				FIsActionChecked::CreateStatic(&FBox3DEditorModule::IsShowCounter)
			),
			NAME_None,
			EUserInterfaceActionType::ToggleButton
		);
	}
	MenuBuilder.EndSection();
	return MenuBuilder.MakeWidget();
}
FReply FBox3DEditorModule::OnDiscordClicked()
{
	FPlatformProcess::LaunchURL(TEXT("https://discord.gg/FyPv32WmHE"), nullptr, nullptr);
	return FReply::Handled();
}
FReply FBox3DEditorModule::OpenSupportClicked()
{
    FPlatformProcess::LaunchURL(TEXT("https://github.com/LiamLeoDev/UnrealDabee"), nullptr, nullptr);
    return FReply::Handled();
}

void FBox3DEditorModule::ShowProfile()
{
	UBox3DWorldSubsystem::EnableProfile = !UBox3DWorldSubsystem::EnableProfile;
}

bool FBox3DEditorModule::IsShowProfile()
{
	return UBox3DWorldSubsystem::EnableProfile;
}

void FBox3DEditorModule::ShowCounter()
{
	UBox3DWorldSubsystem::EnableCounters = !UBox3DWorldSubsystem::EnableCounters;
}

bool FBox3DEditorModule::IsShowCounter()
{
    return UBox3DWorldSubsystem::EnableCounters;
}
#undef LOCTEXT_NAMESPACE
IMPLEMENT_MODULE(FBox3DEditorModule, Box3DEditor)