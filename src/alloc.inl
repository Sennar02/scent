#include "alloc.hpp"

namespace scent
{
    template <class Val>
    Val*
    typed_acquire(Alloc* alloc, Val* pntr, u32 size)
    {
        u32 bytes = sizeof(Val) * size;
        u8  align = alignof(Val);

        if ( alloc == 0 ) return pntr;

        return (Val*) alloc->acquire(
            (i8*) pntr, bytes, align
        );
    }

    template <class Val>
    Val*
    typed_resize(Alloc* alloc, Val* pntr, u32 size)
    {
        u32 bytes = sizeof(Val) * size;

        if ( alloc == 0 ) return 0;

        return (Val*) alloc->resize(
            (i8*) pntr, bytes
        );
    }

    template <class Val>
    void
    typed_release(Alloc* alloc, Val* pntr)
    {
        if ( alloc != 0 )
            alloc->release((i8*) pntr);
    }
} // scent
