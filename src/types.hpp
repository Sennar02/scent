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

    static const u32 BYTES_ARCH = sizeof(size_t);
    static const u8  ALIGN_ARCH = alignof(size_t);

    static const u8 ALIGN_MAX = 16u;
    static const u8 ALIGN_MIN = 1u;

    static const u32 BYTES_UPTR = sizeof(uptr);
    static const u32 BYTES_U64  = sizeof(u64);
    static const u32 BYTES_U32  = sizeof(u32);
    static const u32 BYTES_U16  = sizeof(u16);
    static const u32 BYTES_U8   = sizeof(u8);

    static_assert(BYTES_UPTR == BYTES_ARCH, "Unsupported");
    static_assert(BYTES_U64  ==         8u, "Unsupported");
    static_assert(BYTES_U32  ==         4u, "Unsupported");
    static_assert(BYTES_U16  ==         2u, "Unsupported");
    static_assert(BYTES_U8   ==         1u, "Unsupported");

    static const u8 ALIGN_UPTR = alignof(uptr);
    static const u8 ALIGN_U64  = alignof(u64);
    static const u8 ALIGN_U32  = alignof(u32);
    static const u8 ALIGN_U16  = alignof(u16);
    static const u8 ALIGN_U8   = alignof(u8);

    static_assert(ALIGN_UPTR == ALIGN_ARCH, "Unsupported");
    static_assert(ALIGN_U64  ==         8u, "Unsupported");
    static_assert(ALIGN_U32  ==         4u, "Unsupported");
    static_assert(ALIGN_U16  ==         2u, "Unsupported");
    static_assert(ALIGN_U8   ==         1u, "Unsupported");

    using iptr = intptr_t;
    using i64  = int64_t;
    using i32  = int32_t;
    using i16  = int16_t;
    using i8   = char;

    static const u32 BYTES_IPTR = sizeof(iptr);
    static const u32 BYTES_I64  = sizeof(i64);
    static const u32 BYTES_I32  = sizeof(i32);
    static const u32 BYTES_I16  = sizeof(i16);
    static const u32 BYTES_I8   = sizeof(i8);

    static_assert(BYTES_IPTR == BYTES_ARCH, "Unsupported");
    static_assert(BYTES_I64  ==         8u, "Unsupported");
    static_assert(BYTES_I32  ==         4u, "Unsupported");
    static_assert(BYTES_I16  ==         2u, "Unsupported");
    static_assert(BYTES_I8   ==         1u, "Unsupported");

    static const u8 ALIGN_IPTR = alignof(iptr);
    static const u8 ALIGN_I64  = alignof(i64);
    static const u8 ALIGN_I32  = alignof(i32);
    static const u8 ALIGN_I16  = alignof(i16);
    static const u8 ALIGN_I8   = alignof(i8);

    static_assert(ALIGN_IPTR == ALIGN_ARCH, "Unsupported");
    static_assert(ALIGN_I64  ==         8u, "Unsupported");
    static_assert(ALIGN_I32  ==         4u, "Unsupported");
    static_assert(ALIGN_I16  ==         2u, "Unsupported");
    static_assert(ALIGN_I8   ==         1u, "Unsupported");

    using f64 = double;
    using f32 = float;

    static const u32 BYTES_F64 = sizeof(f64);
    static const u32 BYTES_F32 = sizeof(f32);

    static_assert(BYTES_F64 == 8u, "Unsupported");
    static_assert(BYTES_F32 == 4u, "Unsupported");

    static const u8 ALIGN_F64 = alignof(f64);
    static const u8 ALIGN_F32 = alignof(f32);

    static_assert(ALIGN_F64 == 8u, "Unsupported");
    static_assert(ALIGN_F32 == 4u, "Unsupported");

    struct Alloc;
    struct Empty_Alloc;
    struct Arena_Alloc;

    template <class Val>
    struct Item_Ref;

    template <class Key, class Val>
    struct Pair_Ref;

    template <class Val>
    struct Slice;

    template <class Key>
    struct Hash_Ctx;

    /**
     * Cresce allargando il puntatore o copiando gli elementi.
     */
    template <class Val>
    struct Array_List;

    /**
     * Cresce ricalcolando tutti gli hash. Gestisce le collisioni
     * con la tecnica Robin Hood.
     */
    template <class Key, class Val, class Ctx = Hash_Ctx<Key>>
    struct Robin_Map;
} // scent

#endif // SCENT_TYPES_HPP
