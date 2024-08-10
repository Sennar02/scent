#include <malloc.h>

#include "arena_alloc.hpp"

namespace scent
{
    Arena_Alloc::Arena_Alloc() {}

    Arena_Alloc::Arena_Alloc(u32 size)
    {
        init(size);
    }

    void
    Arena_Alloc::init(u32 size)
    {
        _base = (i8*) calloc(1, size);

        if ( _base != 0 ) {
            _next = _base;
            _size = size;
        }
    }

    void
    Arena_Alloc::drop()
    {
        free(_base);

        _base = 0;
        _next = 0;
        _size = 0;
    }

    void
    Arena_Alloc::reset()
    {
        _next = _base;
    }

    i8*
    Arena_Alloc::reserve(u32 numb, u32 unit, u8 align)
    {
        u32 left = _size - (_next - _base);
        u32 size = numb * unit;

        i8* next = next_aligned(_next, align);
        i8* pntr = 0;

        if ( size != 0 && size <= left ) {
            next += size;

            pntr  =  _next;
            _next = next;
        }

        return pntr;
    }

    i8*
    Arena_Alloc::release(i8* pntr)
    {
        return pntr;
    }
} // scent
