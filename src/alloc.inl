#include "alloc.hpp"

namespace scent
{
    template <class Val>
    Val*
    alloc_acquire(Alloc* alloc, u32 size)
    {
        u32 bytes = sizeof(Val) * size;
        u8  align = alignof(Val);

        if ( alloc == 0 ) return 0;

        return (Val*) alloc->acquire(
            bytes, align
        );
    }

    template <class Val>
    Val*
    alloc_resize(Alloc* alloc, void* pntr, u32 size)
    {
        u32 bytes = sizeof(Val) * size;

        if ( alloc == 0 ) return 0;

        return (Val*) alloc->resize(
            (i8*) pntr, bytes
        );
    }

    template <class Val>
    void
    alloc_release(Alloc* alloc, void* pntr)
    {
        if ( alloc != 0 )
            alloc->release((i8*) pntr);
    }
} // scent
