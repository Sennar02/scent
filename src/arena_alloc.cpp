#include <string.h>

#include "arena_alloc.hpp"

namespace scent
{
    Arena_Alloc::Arena_Alloc() {}

    Arena_Alloc::Arena_Alloc(void* pntr, u32 size)
    {
        init(pntr, size);
    }

    void
    Arena_Alloc::init(void* pntr, u32 size)
    {
        _pntr = (i8*) pntr;

        if ( _pntr != 0 ) {
            _last = 0;
            _next = _pntr;
            _size = size;

            memset(_pntr, 0, _size);
        }
    }

    void
    Arena_Alloc::drop()
    {
        _pntr = 0;
        _last = 0;
        _next = 0;
        _size = 0;
    }

    u32
    Arena_Alloc::size() const
    {
        return _size;
    }

    u32
    Arena_Alloc::next(u8 align) const
    {
        u32 diff =
            next_aligned(_next, align) - _pntr;

        return _size - diff;
    }

    void
    Arena_Alloc::reset()
    {
        _last = 0;
        _next = _pntr;

        memset(_pntr, 0, _size);
    }

    i8*
    Arena_Alloc::acquire(i8* pntr, u32 size, u8 align)
    {
        i8* next = next_aligned(_next, align);

        if ( size == 0 ) return pntr;

        if ( next + size <= _pntr + _size ) {
            _next = next + size;
            _last = next;
            pntr  = next;

            memset(pntr, 0, size);
        }

        return pntr;
    }

    i8*
    Arena_Alloc::resize(i8* pntr, u32 size)
    {
        i8* next = 0;

        if ( _last != pntr || _last == 0 )
            return next;

        if ( pntr + size <= _pntr + _size ) {
            next = pntr + size;

            if ( next > _next )
                memset(_next, 0, next - _next);

            _next = next;
            next  = pntr;
        }

        return next;
    }

    void
    Arena_Alloc::release(i8*)
    {}
} // scent
