#include "arr_list.hpp"

namespace scent
{
    template <class Val>
    Arr_List<Val>::Arr_List() {}

    template <class Val>
    Arr_List<Val>::Arr_List(Alloc& alloc, u32 size)
    {
        _pntr = reserve<Val>(alloc, size);

        if ( _pntr != 0 )
            _size = size;
    }

    template <class Val>
    void
    Arr_List<Val>::drop(Alloc& alloc)
    {
        _pntr = release(alloc, _pntr);

        if ( _pntr == 0 ) {
            _size  = 0;
            _count = 0;
        }
    }

    template <class Val>
    void
    Arr_List<Val>::clear()
    {
        _count = 0;
    }

    template <class Val>
    u32
    Arr_List<Val>::size() const
    {
        return _size;
    }

    template <class Val>
    u32
    Arr_List<Val>::values() const
    {
        return _count;
    }

    template <class Val>
    bool
    Arr_List<Val>::is_empty() const
    {
        return _count == 0;
    }

    template <class Val>
    bool
    Arr_List<Val>::isnt_empty() const
    {
        return _count != 0;
    }

    template <class Val>
    bool
    Arr_List<Val>::is_full() const
    {
        return _count == _size;
    }

    template <class Val>
    bool
    Arr_List<Val>::isnt_full() const
    {
        return _count != _size;
    }

    template <class Val>
    Item_Ref<const Val>
    Arr_List<Val>::find(u32 index) const
    {
        if ( index < _count )
            return {_pntr[index]};

        return {};
    }

    template <class Val>
    Item_Ref<Val>
    Arr_List<Val>::find(u32 index)
    {
        if ( index < _count )
            return {_pntr[index]};

        return {};
    }

    template <class Val>
    bool
    Arr_List<Val>::insert(u32 index, const Val& val)
    {
        if ( _count == _size ) return false;

        index = (index >  _count) * _count +
                (index <= _count) * index;

        for ( u32 i = _count; i > index; i -= 1 )
            _pntr[i] = _pntr[i - 1];

        _pntr[index] = val;
        _count += 1;

        return true;
    }

    template <class Val>
    bool
    Arr_List<Val>::push(u32 index, const Val& val)
    {
        if ( _count == _size ) return false;

        index = (index >  _count) * _count +
                (index <= _count) * index;

        _pntr[_count] = _pntr[index];
        _pntr[index]  = val;

        _count += 1;

        return true;
    }

    template <class Val>
    bool
    Arr_List<Val>::remove(u32 index)
    {
        if ( _count == 0 ) return false;

        _count -= 1;

        index = (index >  _count) * _count +
                (index <= _count) * index;

        for ( u32 i = index; i < _count; i += 1 )
            _pntr[i] = _pntr[i + 1];

        return true;
    }

    template <class Val>
    bool
    Arr_List<Val>::pull(u32 index)
    {
        if ( _count == 0 ) return false;

        _count -= 1;

        index = (index >  _count) * _count +
                (index <= _count) * index;

        _pntr[index] = _pntr[_count];

        return true;
    }
} // scent
