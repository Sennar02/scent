#include "array_list.hpp"

namespace scent
{
    template <class Val>
    Array_List<Val>::Array_List() {}

    template <class Val>
    Array_List<Val>::Array_List(Alloc& alloc, u32 size)
    {
        init(alloc, size);
    }

    template <class Val>
    void
    Array_List<Val>::init(Alloc& alloc, u32 size)
    {
        if ( _pntr != 0 ) drop();

        _alloc = &alloc;
        _pntr  = alloc_acquire<Val>(_alloc, size);

        if ( _pntr != 0 )
            _size = size;
    }

    template <class Val>
    void
    Array_List<Val>::drop()
    {
        alloc_release<Val>(_alloc, _pntr);

        _alloc = 0;
        _pntr  = 0;
        _size  = 0;
        _count = 0;
    }

    template <class Val>
    void
    Array_List<Val>::reset()
    {
        _count = 0;
    }

    template <class Val>
    u32
    Array_List<Val>::size() const
    {
        return _size;
    }

    template <class Val>
    u32
    Array_List<Val>::count() const
    {
        return _count;
    }

    template <class Val>
    Slice<const Val>
    Array_List<Val>::values() const
    {
        return {_pntr, _count};
    }

    template <class Val>
    Slice<Val>
    Array_List<Val>::values()
    {
        return {_pntr, _count};
    }

    template <class Val>
    bool
    Array_List<Val>::is_empty() const
    {
        return _count == 0;
    }

    template <class Val>
    bool
    Array_List<Val>::isnt_empty() const
    {
        return _count != 0;
    }

    template <class Val>
    bool
    Array_List<Val>::is_full() const
    {
        return _count == _size;
    }

    template <class Val>
    bool
    Array_List<Val>::isnt_full() const
    {
        return _count != _size;
    }

    template <class Val>
    bool
    Array_List<Val>::resize(u32 size)
    {
        if ( _count > size ) return false;

        Val* pntr = alloc_resize<Val>(_alloc, _pntr, size);

        if ( _pntr != pntr || pntr == 0 )
            pntr = alloc_acquire<Val>(_alloc, size);

        if ( size != 0 && pntr == 0 )
            return false;

        _pntr = pntr;
        _size = size;

        return true;
    }

    template <class Val>
    bool
    Array_List<Val>::resize(Alloc& alloc, u32 size)
    {
        if ( _count > size ) return false;

        Val* pntr = alloc_acquire<Val>(&alloc, size);

        if ( pntr == 0 ) return false;

        for ( u32 i = 0; i < _count; i += 1 )
            pntr[i] = _pntr[i];

        alloc_release<Val>(_alloc, _pntr);

        _alloc = &alloc;
        _pntr  = pntr;
        _size  = size;

        return true;
    }

    template <class Val>
    bool
    Array_List<Val>::insert(u32 index, const Val& val)
    {
        if ( _count == _size )
            resize(_size + _size / 2 + 1);

        if ( _count == _size ) return false;
        if ( _count <  index ) return false;

        for ( u32 i = _count; i > index; i -= 1 )
            _pntr[i] = _pntr[i - 1];

        _pntr[index] = val;
        _count += 1;

        return true;
    }

    template <class Val>
    bool
    Array_List<Val>::push(u32 index, const Val& val)
    {
        if ( _count == _size )
            resize(_size + _size / 2 + 1);

        if ( _count == _size ) return false;
        if ( _count <  index ) return false;

        _pntr[_count] = _pntr[index];
        _pntr[index]  = val;

        _count += 1;

        return true;
    }

    template <class Val>
    bool
    Array_List<Val>::remove(u32 index)
    {
        if ( _count ==     0 ) return false;
        if ( _count <  index ) return false;

        _count -= 1;

        for ( u32 i = index; i < _count; i += 1 )
            _pntr[i] = _pntr[i + 1];

        return true;
    }

    template <class Val>
    bool
    Array_List<Val>::pull(u32 index)
    {
        if ( _count ==     0 ) return false;
        if ( _count <  index ) return false;

        _count -= 1;
        _pntr[index] = _pntr[_count];

        return true;
    }

    template <class Val>
    Item_Ref<const Val>
    Array_List<Val>::operator[](u32 index) const
    {
        if ( index < _count )
            return {_pntr[index]};

        return {};
    }

    template <class Val>
    Item_Ref<Val>
    Array_List<Val>::operator[](u32 index)
    {
        if ( index < _count )
            return {_pntr[index]};

        return {};
    }
} // scent
