#ifndef GR_CORE_TYPES_HPP
#define GR_CORE_TYPES_HPP

#include <stdint.h>

#include "assert.hpp"

#define gr_type_size(type) \
    sizeof(type)

#define gr_type_align(type) \
    alignof(type)

namespace gr
{
    using usize = uintptr_t;
    using u64   = uint64_t;
    using u32   = uint32_t;
    using u16   = uint16_t;
    using u8    = uint8_t;

    using isize = intptr_t;
    using i64   = int64_t;
    using i32   = int32_t;
    using i16   = int16_t;
    using i8    = int8_t;

    using f64 = double;
    using f32 = float;

    using byte = char;

    static const isize ALIGN_MAX = 16u;
    static const isize ALIGN_MIN = 1u;

    static const isize SIZE_USIZE = gr_type_size(usize);
    static const isize SIZE_U64   = gr_type_size(u64);
    static const isize SIZE_U32   = gr_type_size(u32);
    static const isize SIZE_U16   = gr_type_size(u16);
    static const isize SIZE_U8    = gr_type_size(u8);

    static const isize ALIGN_USIZE = gr_type_align(usize);
    static const isize ALIGN_U64   = gr_type_align(u64);
    static const isize ALIGN_U32   = gr_type_align(u32);
    static const isize ALIGN_U16   = gr_type_align(u16);
    static const isize ALIGN_U8    = gr_type_align(u8);

    gr_cpl_assert(SIZE_U64 == 8u, "Invalid type size");
    gr_cpl_assert(SIZE_U32 == 4u, "Invalid type size");
    gr_cpl_assert(SIZE_U16 == 2u, "Invalid type size");
    gr_cpl_assert(SIZE_U8  == 1u, "Invalid type size");

    gr_cpl_assert(ALIGN_U64 == 8u, "Invalid type alignment");
    gr_cpl_assert(ALIGN_U32 == 4u, "Invalid type alignment");
    gr_cpl_assert(ALIGN_U16 == 2u, "Invalid type alignment");
    gr_cpl_assert(ALIGN_U8  == 1u, "Invalid type alignment");

    static const isize SIZE_ISIZE = gr_type_size(isize);
    static const isize SIZE_I64   = gr_type_size(i64);
    static const isize SIZE_I32   = gr_type_size(i32);
    static const isize SIZE_I16   = gr_type_size(i16);
    static const isize SIZE_I8    = gr_type_size(i8);

    static const isize ALIGN_ISIZE = gr_type_align(isize);
    static const isize ALIGN_I64   = gr_type_align(i64);
    static const isize ALIGN_I32   = gr_type_align(i32);
    static const isize ALIGN_I16   = gr_type_align(i16);
    static const isize ALIGN_I8    = gr_type_align(i8);

    gr_cpl_assert(SIZE_I64 == 8u, "Invalid type size");
    gr_cpl_assert(SIZE_I32 == 4u, "Invalid type size");
    gr_cpl_assert(SIZE_I16 == 2u, "Invalid type size");
    gr_cpl_assert(SIZE_I8  == 1u, "Invalid type size");

    gr_cpl_assert(ALIGN_I64 == 8u, "Invalid type alignment");
    gr_cpl_assert(ALIGN_I32 == 4u, "Invalid type alignment");
    gr_cpl_assert(ALIGN_I16 == 2u, "Invalid type alignment");
    gr_cpl_assert(ALIGN_I8  == 1u, "Invalid type alignment");

    static const isize SIZE_F64 = gr_type_size(f64);
    static const isize SIZE_F32 = gr_type_size(f32);

    static const isize ALIGN_F64 = gr_type_align(f64);
    static const isize ALIGN_F32 = gr_type_align(f32);

    gr_cpl_assert(SIZE_F64 == 8u, "Invalid type size");
    gr_cpl_assert(SIZE_F32 == 4u, "Invalid type size");

    gr_cpl_assert(ALIGN_F64 == 8u, "Invalid type alignment");
    gr_cpl_assert(ALIGN_F32 == 4u, "Invalid type alignment");

    static const isize SIZE_BYTE  = gr_type_size(byte);

    static const isize ALIGN_BYTE = gr_type_align(byte);

    gr_cpl_assert(SIZE_BYTE  == 1u, "Invalid type size");

    gr_cpl_assert(ALIGN_BYTE == 1u, "Invalid type size");
} // namespace gr

#endif // GR_CORE_TYPES_HPP
