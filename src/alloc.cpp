#include <assert.h>

#include "alloc.hpp"

namespace scent
{
    bool
    is_pow_2(uptr value)
    {
        uptr error = value & (value - 1u);

        return error == 0 && value != 0;
    }

    i8*
    next_aligned(void* memory, u8 align)
    {
        assert(is_pow_2(align) != 0 && "Alignment is not a power of two");

        uptr value = (uptr) memory;
        uptr error = value & (align - 1u);

        error = (error != 0) * (align - error);

        return (i8*) (value + error);
    }

    i8*
    null_if(void* memory, bool state)
    {
        uptr value = (uptr) memory;

        value = (state == 0) * value;

        return (i8*) value;
    }
} // scent
