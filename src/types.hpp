#ifndef SCENT_TYPES_HPP
#define SCENT_TYPES_HPP

#include <stdint.h>
#include <stddef.h>

namespace scent
{
    using uptr = uintptr_t;
    using u64  = uint64_t;
    using u32  = uint32_t;
    using u16  = uint16_t;
    using u8   = uint8_t;

    static_assert(alignof(uptr) == alignof(size_t), "Unsupported");
    static_assert(alignof(u64)  ==               8, "Unsupported");
    static_assert(alignof(u32)  ==               4, "Unsupported");
    static_assert(alignof(u16)  ==               2, "Unsupported");
    static_assert(alignof(u8)   ==               1, "Unsupported");

    static_assert(sizeof(uptr) == sizeof(size_t), "Unsupported");
    static_assert(sizeof(u64)  ==              8, "Unsupported");
    static_assert(sizeof(u32)  ==              4, "Unsupported");
    static_assert(sizeof(u16)  ==              2, "Unsupported");
    static_assert(sizeof(u8)   ==              1, "Unsupported");

    using iptr = intptr_t;
    using i64  = int64_t;
    using i32  = int32_t;
    using i16  = int16_t;
    using i8   = char;

    static_assert(alignof(iptr) == alignof(size_t), "Unsupported");
    static_assert(alignof(i64)  ==               8, "Unsupported");
    static_assert(alignof(i32)  ==               4, "Unsupported");
    static_assert(alignof(i16)  ==               2, "Unsupported");
    static_assert(alignof(i8)   ==               1, "Unsupported");

    static_assert(sizeof(iptr) == sizeof(size_t), "Unsupported");
    static_assert(sizeof(i64)  ==              8, "Unsupported");
    static_assert(sizeof(i32)  ==              4, "Unsupported");
    static_assert(sizeof(i16)  ==              2, "Unsupported");
    static_assert(sizeof(i8)   ==              1, "Unsupported");

    using f64 = double;
    using f32 = float;

    static_assert(alignof(f64) == 8, "Unsupported");
    static_assert(alignof(f32) == 4, "Unsupported");

    static_assert(sizeof(f64) == 8, "Unsupported");
    static_assert(sizeof(f32) == 4, "Unsupported");

    template <class Key>
    struct Hash;

    template <class Val>
    struct Arr_List;

    template <class Key, class Val, class Hash = Hash<Key>>
    struct Hash_Map;
} // scent

#endif // SCENT_TYPES_HPP
