// Copyright (c) 2026 LiamLeo

#pragma once

#include "CoreMinimal.h"
#include "Box3DTypes.h"

namespace Box3DRecording
{
    BOX3DWRAPPER_API FB3RecordingHandle CreateRecording(int ByteCapacity);
    BOX3DWRAPPER_API void StartRecording(const FB3WorldHandle& WorldHandle,const FB3RecordingHandle& RecordingHandle);
    BOX3DWRAPPER_API void StopRecording(const FB3WorldHandle& WorldHandle);
    BOX3DWRAPPER_API bool SaveRecordingToFile(const FB3RecordingHandle& RecordingHandle,const FString& Path);
    BOX3DWRAPPER_API void DestroyRecording(FB3RecordingHandle& RecordingHandle);   
} 

#define B3RECORD Box3DRecording