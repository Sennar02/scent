#include <assert.h>

#include "alloc.hpp"

namespace scent
{
    i8*
    next_aligned(i8* memory, u8 align)
    {
        assert(align  != 0 && "Alignment is zero");

        uptr pntr = (uptr) memory;
        uptr diff = pntr % align;

        diff = (diff != 0) * (align - diff);

        return (i8*) (pntr + diff);
    }

    i8*
    null_if(i8* memory, bool state)
    {
        uptr pntr = (uptr) memory;
        uptr fact = !state;

        return (i8*) (pntr * fact);
    }
} // scent
