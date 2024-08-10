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
        _alloc = &alloc;
        _pntr  = reserve<Val>(*_alloc, size);

        if ( _pntr == 0 )
            _alloc = 0;
        else
            _size  = size;
    }

    template <class Val>
    void
    Array_List<Val>::drop()
    {
        release(*_alloc, _pntr);

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
    Array_List<Val>::insert(u32 index, const Val& val)
    {
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
