// Copyright (c) 2026 LiamLeo

#pragma once

#include "CoreMinimal.h"
#include "Misc/AssertionMacros.h"


#ifndef BOX3D_ENABLE_ENSURES
    #define BOX3D_ENABLE_ENSURES 0
#endif


#ifndef BOX3D_FORCE_ENSURES_IN_SHIPPING
    #define BOX3D_FORCE_ENSURES_IN_SHIPPING 0
#endif


#define BOX3D_ENSURES_ACTIVE \
    (BOX3D_ENABLE_ENSURES && (!UE_BUILD_SHIPPING || BOX3D_FORCE_ENSURES_IN_SHIPPING))

#if BOX3D_ENSURES_ACTIVE

    #define B3_ENSURE(Expr)                                         ensure(Expr)
    #define B3_ENSURE_MSG(Expr, Fmt, ...)                           ensureMsgf(Expr, Fmt, ##__VA_ARGS__)
    #define B3_ENSURE_ALWAYS(Expr)                                  ensureAlways(Expr)
    #define B3_ENSURE_ALWAYS_MSG(Expr, Fmt, ...)                    ensureAlwaysMsgf(Expr, Fmt, ##__VA_ARGS__)
    #define B3_ENSURE_RET(Expr, RetVal)                      if (!ensure(Expr)) { return RetVal; }
    #define B3_ENSURE_MSG_RET(Expr, RetVal, Fmt, ...)        if (!ensureMsgf(Expr, Fmt, ##__VA_ARGS__)) { return RetVal; }
    #define B3_ENSURE_ALWAYS_RET(Expr, RetVal)               if (!ensureAlways(Expr)) { return RetVal; }
    #define B3_ENSURE_ALWAYS_MSG_RET(Expr, RetVal, Fmt, ...) if (!ensureAlwaysMsgf(Expr, Fmt, ##__VA_ARGS__)) { return RetVal; }

#else

    #define B3_ENSURE(Expr)
    #define B3_ENSURE_MSG(Expr, Fmt, ...)
    #define B3_ENSURE_ALWAYS(Expr)
    #define B3_ENSURE_ALWAYS_MSG(Expr, Fmt, ...)

    #define B3_ENSURE_RET(Expr, RetVal)
    #define B3_ENSURE_MSG_RET(Expr, RetVal, Fmt, ...)
    #define B3_ENSURE_ALWAYS_RET(Expr, RetVal)
    #define B3_ENSURE_ALWAYS_MSG_RET(Expr, RetVal, Fmt, ...)

#endif