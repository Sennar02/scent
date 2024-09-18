#include "alloc.hpp"

namespace scent
{
    template <class Val>
    Val*
    alloc_acquire(Alloc* alloc, u32 size)
    {
        i8* resl = 0;

        if ( alloc != 0 ) {
            u32 bytes = sizeof(Val) * size;
            u8  align = alignof(Val);

            resl = alloc->acquire(bytes, align);
        }

        return (Val*) resl;
    }

    template <class Val>
    Val*
    alloc_resize(Alloc* alloc, void* pntr, u32 size)
    {
        i8* addr = (i8*) pntr;
        i8* resl = 0;

        if ( alloc != 0 ) {
            u32 bytes = sizeof(Val) * size;

            resl = alloc->resize(addr, bytes);
        }

        return (Val*) resl;
    }

    template <class Val>
    void
    alloc_release(Alloc* alloc, void* pntr)
    {
        i8* addr = (i8*) pntr;

        if ( alloc != 0 )
            alloc->release(addr);
    }
} // scent
