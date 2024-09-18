#include "slice.hpp"

namespace scent
{
    template <class Val>
    Slice<Val>::Slice() {}

    template <class Val>
    Slice<Val>::Slice(Val* pntr, u32 size)
    {
        init(pntr, size);
    }

    template <class Val>
    void
    Slice<Val>::init(Val* pntr, u32 size)
    {
        if ( pntr == 0 || size == 0 )
            return;

        _pntr = pntr;
        _size = size;
    }

    template <class Val>
    void
    Slice<Val>::drop()
    {
        _pntr = 0;
        _size = 0;
    }

    template <class Val>
    u32
    Slice<Val>::size() const
    {
        return _size;
    }

    template <class Val>
    const Val&
    Slice<Val>::operator[](u32 index) const
    {
        assert(index < _size && "Index out of bounds");

        return _pntr[index];
    }

    template <class Val>
    Val&
    Slice<Val>::operator[](u32 index)
    {
        assert(index < _size && "Index out of bounds");

        return _pntr[index];
    }
} // scent
