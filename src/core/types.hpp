#ifndef CORE_TYPES_HPP
#define CORE_TYPES_HPP

#include <stdint.h>
#include <stddef.h>

#include "assert.hpp"

namespace core
{
    using uarch = size_t;
    using upntr = uintptr_t;
    using u64   = uint64_t;
    using u32   = uint32_t;
    using u16   = uint16_t;
    using u8    = uint8_t;

    using ipntr = intptr_t;
    using i64   = int64_t;
    using i32   = int32_t;
    using i16   = int16_t;
    using i8    = char;

    using f64 = double;
    using f32 = float;

    static const u8 ALGN_MAX = 16u;
    static const u8 ALGN_MIN = 1u;

    static const uarch SIZE_UARCH = sizeof(uarch);
    static const uarch SIZE_UPNTR = sizeof(upntr);
    static const uarch SIZE_U64   = sizeof(u64);
    static const uarch SIZE_U32   = sizeof(u32);
    static const uarch SIZE_U16   = sizeof(u16);
    static const uarch SIZE_U8    = sizeof(u8);

    static const u8 ALGN_UARCH = alignof(uarch);
    static const u8 ALGN_UPNTR = alignof(upntr);
    static const u8 ALGN_U64   = alignof(u64);
    static const u8 ALGN_U32   = alignof(u32);
    static const u8 ALGN_U16   = alignof(u16);
    static const u8 ALGN_U8    = alignof(u8);

    COMPILE_ASSERT(SIZE_U64 == 8u, "Invalid type size");
    COMPILE_ASSERT(SIZE_U32 == 4u, "Invalid type size");
    COMPILE_ASSERT(SIZE_U16 == 2u, "Invalid type size");
    COMPILE_ASSERT(SIZE_U8  == 1u, "Invalid type size");

    COMPILE_ASSERT(ALGN_U64 == 8u, "Invalid type alignment");
    COMPILE_ASSERT(ALGN_U32 == 4u, "Invalid type alignment");
    COMPILE_ASSERT(ALGN_U16 == 2u, "Invalid type alignment");
    COMPILE_ASSERT(ALGN_U8  == 1u, "Invalid type alignment");

    static const uarch SIZE_IPNTR = sizeof(ipntr);
    static const uarch SIZE_I64   = sizeof(i64);
    static const uarch SIZE_I32   = sizeof(i32);
    static const uarch SIZE_I16   = sizeof(i16);
    static const uarch SIZE_I8    = sizeof(i8);

    static const u8 ALGN_IPNTR = alignof(ipntr);
    static const u8 ALGN_I64   = alignof(i64);
    static const u8 ALGN_I32   = alignof(i32);
    static const u8 ALGN_I16   = alignof(i16);
    static const u8 ALGN_I8    = alignof(i8);

    COMPILE_ASSERT(SIZE_I64 == 8u, "Invalid type size");
    COMPILE_ASSERT(SIZE_I32 == 4u, "Invalid type size");
    COMPILE_ASSERT(SIZE_I16 == 2u, "Invalid type size");
    COMPILE_ASSERT(SIZE_I8  == 1u, "Invalid type size");

    COMPILE_ASSERT(ALGN_I64 == 8u, "Invalid type alignment");
    COMPILE_ASSERT(ALGN_I32 == 4u, "Invalid type alignment");
    COMPILE_ASSERT(ALGN_I16 == 2u, "Invalid type alignment");
    COMPILE_ASSERT(ALGN_I8  == 1u, "Invalid type alignment");

    static const uarch SIZE_F64 = sizeof(f64);
    static const uarch SIZE_F32 = sizeof(f32);

    static const u8 ALGN_F64 = alignof(f64);
    static const u8 ALGN_F32 = alignof(f32);

    COMPILE_ASSERT(SIZE_F64 == 8u, "Invalid type size");
    COMPILE_ASSERT(SIZE_F32 == 4u, "Invalid type size");

    COMPILE_ASSERT(ALGN_F64 == 8u, "Invalid type alignment");
    COMPILE_ASSERT(ALGN_F32 == 4u, "Invalid type alignment");
} // namespace core

#endif // CORE_TYPES_HPP
