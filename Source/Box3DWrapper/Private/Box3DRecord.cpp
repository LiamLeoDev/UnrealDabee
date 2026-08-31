// Copyright (c) 2026 LiamLeo


#include "Box3DRecord.h"
#include "CoreMinimal.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "Box3DTypes.h"
#include "Box3DAsserts.h"
#include "box3d/box3d.h"
namespace Box3DRecording
{
    FB3RecordingHandle CreateRecording(int ByteCapacity)
    {
        return FB3RecordingHandle(b3CreateRecording(ByteCapacity));
    }
    void StartRecording(const FB3WorldHandle& WorldHandle,const FB3RecordingHandle& RecordingHandle)
    {
        B3_ENSURE_MSG_RET(WorldHandle,, TEXT("StartRecording called with an invlaid World Handle"));
        b3World_StartRecording(WorldHandle.GetID(), RecordingHandle.GetRecording());
    }
    void StopRecording(const FB3WorldHandle& WorldHandle)
    {
        B3_ENSURE_MSG_RET(WorldHandle,, TEXT("StopRecording called with an invlaid World Handle"));
        b3World_StopRecording(WorldHandle.GetID());
    }
    bool SaveRecordingToFile(const FB3RecordingHandle& RecordingHandle,const FString& RecordingPath)
    {
        B3_ENSURE_MSG_RET(RecordingHandle, false, TEXT("SaveRecordingToFile called with an invlaid Recording Handle"));
        B3_ENSURE_MSG_RET(IFileManager::Get().DirectoryExists(*FPaths::GetPath(RecordingPath)), false, TEXT("There is no such directory where this recording file to write to."));
        return b3SaveRecordingToFile(RecordingHandle.GetRecording(), TCHAR_TO_UTF8(*RecordingPath));
    }
    void DestroyRecording(FB3RecordingHandle& RecordingHandle)
    {
        B3_ENSURE_MSG_RET(RecordingHandle,, TEXT("DestroyRecording called with an invlaid Recording Handle"));
        b3DestroyRecording(RecordingHandle.GetRecording());
        RecordingHandle = FB3RecordingHandle(nullptr);
    }
} 