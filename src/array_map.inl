#include "array_map.hpp"

namespace scent
{
    template <class Key, class Val, class Hash>
    Array_Map<Key, Val, Hash>::Array_Map() {}

    template <class Key, class Val, class Hash>
    Array_Map<Key, Val, Hash>::Array_Map(Alloc& alloc, u32 size)
    {
        init(alloc, size);
    }

    template <class Key, class Val, class Hash>
    void
    Array_Map<Key, Val, Hash>::init(Alloc& alloc, u32 size)
    {
        _alloc = &alloc;
        _indx  = reserve<u32>(*_alloc, size);
        _hash  = reserve<u32>(*_alloc, size);
        _head  = reserve<Key>(*_alloc, size);
        _body  = reserve<Val>(*_alloc, size);

        if ( _indx == 0 || _hash == 0 || _head == 0 || _body == 0 ) {
            release(*_alloc, _body);
            release(*_alloc, _head);
            release(*_alloc, _hash);
            release(*_alloc, _indx);

            _alloc = 0;
        } else
            _size  = size;
    }

    template <class Key, class Val, class Hash>
    void
    Array_Map<Key, Val, Hash>::drop()
    {
        release(*_alloc, _body);
        release(*_alloc, _head);
        release(*_alloc, _hash);
        release(*_alloc, _indx);

        _alloc = 0;
        _indx  = 0;
        _hash  = 0;
        _head  = 0;
        _body  = 0;
        _size  = 0;
        _count = 0;
    }

    template <class Key, class Val, class Hash>
    void
    Array_Map<Key, Val, Hash>::reset()
    {
        for ( u32 i = 0; i < _size; i += 1 )
            _indx[i] = 0;

        _count = 0;
    }

    template <class Key, class Val, class Hash>
    u32
    Array_Map<Key, Val, Hash>::size() const
    {
        return _size;
    }

    template <class Key, class Val, class Hash>
    u32
    Array_Map<Key, Val, Hash>::count() const
    {
        return _count;
    }

    template <class Key, class Val, class Hash>
    Slice<const Key>
    Array_Map<Key, Val, Hash>::keys() const
    {
        return {_head, _count};
    }

    template <class Key, class Val, class Hash>
    Slice<const Val>
    Array_Map<Key, Val, Hash>::values() const
    {
        return {_body, _count};
    }

    template <class Key, class Val, class Hash>
    Slice<Val>
    Array_Map<Key, Val, Hash>::values()
    {
        return {_body, _count};
    }

    template <class Key, class Val, class Hash>
    bool
    Array_Map<Key, Val, Hash>::is_empty() const
    {
        return _count == 0;
    }

    template <class Key, class Val, class Hash>
    bool
    Array_Map<Key, Val, Hash>::isnt_empty() const
    {
        return _count != 0;
    }

    template <class Key, class Val, class Hash>
    bool
    Array_Map<Key, Val, Hash>::is_full() const
    {
        return _count == _size;
    }

    template <class Key, class Val, class Hash>
    bool
    Array_Map<Key, Val, Hash>::isnt_full() const
    {
        return _count != _size;
    }

    template <class Key, class Val, class Hash>
    bool
    Array_Map<Key, Val, Hash>::insert(const Key& key, const Val& val)
    {
        if ( _count == _size ) return false;

        u32 hash = Hash::get(key) % _size;
        u32 temp = _count;

        if ( _indx[hash] != 0 ) return false;

        _count += 1;

        _indx[hash] = _count;
        _hash[temp] = hash;
        _head[temp] = key;
        _body[temp] = val;

        return true;
    }

    template <class Key, class Val, class Hash>
    bool
    Array_Map<Key, Val, Hash>::update(const Key& key, const Val& val)
    {
        u32 hash = Hash::get(key) % _size;
        u32 temp = _count;
        u32 indx = _indx[hash] - 1;

        if ( _indx[hash] != 0 ) {
            if ( !Hash::eql(key, _head[indx]) )
                return false;

            _body[indx] = val;
        } else {
            if ( _count == _size ) return false;

            _count += 1;

            _indx[hash] = _count;
            _hash[temp] = hash;
            _head[temp] = key;
            _body[temp] = val;
        }

        return true;
    }

    template <class Key, class Val, class Hash>
    bool
    Array_Map<Key, Val, Hash>::remove(const Key& key)
    {
        if ( _count == 0 ) return false;

        u32 hash = Hash::get(key) % _size;
        u32 indx = _indx[hash] - 1;
        u32 temp = _count - 1;

        if ( _indx[hash] == 0 ) return false;

        if ( Hash::eql(key, _head[indx]) ) {
            _count -= 1;

            temp = _hash[_count];

            _indx[temp] = indx + 1;
            _indx[hash] = 0;
            _hash[indx] = _hash[_count];
            _head[indx] = _head[_count];
            _body[indx] = _body[_count];

            return true;
        }

        return false;
    }

    template <class Key, class Val, class Hash>
    Pair_Ref<const Key, const Val>
    Array_Map<Key, Val, Hash>::operator[](const Key& key) const
    {
        if ( _count == 0 ) return {};

        u32 hash = Hash::get(key) % _size;
        u32 indx = _indx[hash] - 1;

        if ( _indx[hash] != 0 ) {
            if ( Hash::eql(key, _head[indx]) )
                return {key, _body[indx]};
        }

        return {};
    }

    template <class Key, class Val, class Hash>
    Pair_Ref<const Key, Val>
    Array_Map<Key, Val, Hash>::operator[](const Key& key)
    {
        if ( _count == 0 ) return {};

        u32 hash = Hash::get(key) % _size;
        u32 indx = _indx[hash] - 1;

        if ( _indx[hash] != 0 ) {
            if ( Hash::eql(key, _head[indx]) )
                return {key, _body[indx]};
        }

        return {};
    }
} // scent
