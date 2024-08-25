#include <assert.h>

#include "alloc.hpp"

namespace scent
{
    bool
    is_pow_2(u32 value)
    {
        u32 error = (value & (value - 1));

        return value != 0 &&
               error == 0;
    }

    i8*
    next_aligned(void* memory, u8 align)
    {
        assert(is_pow_2(align) != 0 && "Alignment is not a power of two");

        uptr value = (uptr) memory;
        uptr error = value & (align - 1);

        error = (error != 0) * (align - error);

        return (i8*) (value + error);
    }

    i8*
    null_if(void* memory, bool state)
    {
        uptr value = (uptr) memory;

        return (i8*) (
            (state == 0) * value
        );
    }
} // scent
