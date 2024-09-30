#include <string.h>

#include "buffer.hpp"

namespace core
{
    Buffer::Buffer() {}

    Buffer::Buffer(i8* pntr, uarch size)
    {
        init(pntr, size);
    }

    void
    Buffer::init(i8* pntr, uarch size)
    {
        RUNTIME_ASSERT(_base == 0, "The buffer was already initialized");

        _base = pntr;

        if ( _base != 0 ) {
            _curr = _base;
            _size = size;
        }
    }

    void
    Buffer::drop()
    {
        _base = 0;
        _curr = 0;
        _size = 0;
    }

    uarch
    Buffer::size() const
    {
        return _size;
    }

    i8*
    Buffer::require(uarch size, u8 align)
    {
        i8* curr = align_forw(_curr, align);
        i8* pntr = 0;

        if ( size == 0 ) return pntr;

        if ( curr + size <= _base + _size) {
            _curr = curr + size;
            pntr  = curr;

            memset(pntr, 0, size);
        }

        return pntr;
    }

    void
    Buffer::reset()
    {
        _curr = _base;
    }
} // namespace core
