#include <assert.h>
#include <malloc.h>
#include <string.h>

#include "block_alloc.hpp"

namespace scent
{
    Block_Alloc::Block_Alloc() {}

    Block_Alloc::Block_Alloc(void* pntr, u32 size, u32 unit, u8 align)
    {
        init(pntr, size, unit, align);
    }

    void
    Block_Alloc::init(void* pntr, u32 size, u32 unit, u8 align)
    {
        assert(unit >= BYTES_ARCH && "Unit is too small");

        void** node = 0;
        i8*    next = next_aligned(pntr, align);

        _pntr = (i8*) pntr;

        if ( _pntr != 0 ) {
            _size  = size;
            _unit  = unit;
            _fill  = next - _pntr;
            _count = _size / (_unit + _fill);

            memset(_pntr, 0, _size);

            _list  = 0;

            for ( u32 i = 0; i < _count; i += 1 ) {
                node = (void**) next;

                next += (_unit + _fill);

                *node = (void*) _list;
                _list = node;
            }
        }
    }

    void
    Block_Alloc::drop()
    {
        _pntr  = 0;
        _list  = 0;
        _size  = 0;
        _unit  = 0;
        _fill  = 0;
        _count = 0;
    }

    u32
    Block_Alloc::size() const
    {
        return _size;
    }

    u32
    Block_Alloc::next(u8) const
    {
        // todo(trakot): verificare allineamento.

        return (_count != 0) * _unit;
    }

    void
    Block_Alloc::reset()
    {
        void** node = 0;
        i8*    next = _pntr;

        if ( _pntr != 0 ) {
            memset(_pntr, 0, _size);

            _list  = 0;

            for ( u32 i = 0; i < _count; i += 1 ) {
                node = (void**) next;

                next += (_unit + _fill);

                *node = (void*) _list;
                _list = node;
            }
        }
    }

    i8*
    Block_Alloc::reserve(u32 size, u8)
    {
        // todo(trakot): verificare allineamento.

        void** node = _list;
        i8*    pntr = 0;

        if ( _count == 0 ) return pntr;

        if ( size != 0 && size <= _unit ) {
            _list = (void**) *node;
            pntr  = (i8*) node;

            _count -= 1;

            memset(pntr, 0, _unit);
        }

        return pntr;
    }

    void
    Block_Alloc::release(i8*)
    {
        // todo(trakot): implementare la rilevazione di doppie free e il rilascio.
    }
} // scent
