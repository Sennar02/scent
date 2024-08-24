#include <assert.h>

#include "alloc.hpp"

namespace scent
{
    bool
    is_pow_2(u32 value)
    {
        u32 diff =
            (value & (value - 1));

        return value != 0 && diff == 0;
    }

    i8*
    next_aligned(void* memory, u8 align)
    {
        assert(is_pow_2(align) != 0 && "Alignment is not a power of two");

        uptr pntr = (uptr) memory;
        uptr diff = pntr & (align - 1);

        diff = (diff != 0) * (align - diff);

        return (i8*) (pntr + diff);
    }

    i8*
    null_if(void* memory, bool state)
    {
        uptr pntr = (uptr) memory;
        uptr fact = !state;

        return (i8*) (pntr * fact);
    }
} // scent
