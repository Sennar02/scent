#include <malloc.h>

#include "arena_alloc.hpp"

namespace scent
{
    Arena_Alloc::Arena_Alloc(u32 size)
    {
        i8* pntr = (i8*) calloc(1, size);

        if ( pntr != 0 ) {
            _base = pntr;
            _next = pntr;
            _size = size;
        }
    }

    i8*
    Arena_Alloc::reserve(u32 items, u32 bytes, u8 align)
    {
        u32 left = _size - (_next - _base);
        u32 size = items * bytes;

        i8* next = next_aligned(_next, align);
        i8* pntr = 0;

        if ( size <= left ) {
            next += size;

            pntr  =  _next;
            _next = next;
        }

        return pntr;
    }

    i8*
    Arena_Alloc::release(i8* pntr)
    {
        if ( pntr == _base )
            _next = _base;

        return null_if(pntr,
            pntr == _base || pntr == 0
        );
    }
} // scent
