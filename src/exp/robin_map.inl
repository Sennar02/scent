#include "robin_map.hpp"

namespace scent
{
    template <class Key, class Val, class Ctx>
    Robin_Map<Key, Val, Ctx>::Robin_Map() {}

    template <class Key, class Val, class Ctx>
    Robin_Map<Key, Val, Ctx>::Robin_Map(Alloc& alloc, u32 size)
    {
        init(alloc, size);
    }

    template <class Key, class Val, class Ctx>
    void
    Robin_Map<Key, Val, Ctx>::init(Alloc& alloc, u32 size)
    {
        if ( _size != 0 ) drop();

        _alloc = &alloc;
        _ctrl  = alloc_acquire<Ctrl>(_alloc, size);
        _indx  = alloc_acquire<u32>(_alloc, size);
        _head  = alloc_acquire<Key>(_alloc, size);
        _body  = alloc_acquire<Val>(_alloc, size);

        if ( _ctrl == 0 || _indx == 0 || _head == 0 || _body == 0 ) {
            alloc_release<Ctrl>(_alloc, _ctrl);
            alloc_release<u32>(_alloc, _indx);
            alloc_release<Key>(_alloc, _head);
            alloc_release<Val>(_alloc, _body);

            _ctrl = 0;
            _indx = 0;
            _head = 0;
            _body = 0;
        } else
            _size = size;
    }

    template <class Key, class Val, class Ctx>
    void
    Robin_Map<Key, Val, Ctx>::drop()
    {
        alloc_release<Val>(_alloc, _body);
        alloc_release<Key>(_alloc, _head);
        alloc_release<u32>(_alloc, _indx);
        alloc_release<Ctrl>(_alloc, _ctrl);

        _alloc = 0;
        _ctrl  = 0;
        _indx  = 0;
        _head  = 0;
        _body  = 0;
        _size  = 0;
        _count = 0;
    }

    template <class Key, class Val, class Ctx>
    void
    Robin_Map<Key, Val, Ctx>::reset()
    {
        for ( u32 i = 0; i < _size; i += 1 )
            _ctrl[i].dist = 0;

        _count = 0;
    }

    template <class Key, class Val, class Ctx>
    u32
    Robin_Map<Key, Val, Ctx>::size() const
    {
        return _size;
    }

    template <class Key, class Val, class Ctx>
    u32
    Robin_Map<Key, Val, Ctx>::count() const
    {
        return _count;
    }

    template <class Key, class Val, class Ctx>
    Slice<const Key>
    Robin_Map<Key, Val, Ctx>::keys() const
    {
        return {_head, _count};
    }

    template <class Key, class Val, class Ctx>
    Slice<const Val>
    Robin_Map<Key, Val, Ctx>::values() const
    {
        return {_body, _count};
    }

    template <class Key, class Val, class Ctx>
    Slice<Val>
    Robin_Map<Key, Val, Ctx>::values()
    {
        return {_body, _count};
    }

    template <class Key, class Val, class Ctx>
    bool
    Robin_Map<Key, Val, Ctx>::is_empty() const
    {
        return _count == 0;
    }

    template <class Key, class Val, class Ctx>
    bool
    Robin_Map<Key, Val, Ctx>::isnt_empty() const
    {
        return _count != 0;
    }

    template <class Key, class Val, class Ctx>
    bool
    Robin_Map<Key, Val, Ctx>::is_full() const
    {
        return _count == _size;
    }

    template <class Key, class Val, class Ctx>
    bool
    Robin_Map<Key, Val, Ctx>::isnt_full() const
    {
        return _count != _size;
    }

    template <class Key, class Val, class Ctx>
    bool
    Robin_Map<Key, Val, Ctx>::resize(u32)
    {
        return false;
    }

    template <class Key, class Val, class Ctx>
    bool
    Robin_Map<Key, Val, Ctx>::resize(Alloc&, u32)
    {
        return false;
    }

    template <class Key, class Val, class Ctx>
    void
    Robin_Map<Key, Val, Ctx>::rehash()
    {}

    template <class Key, class Val, class Ctx>
    bool
    Robin_Map<Key, Val, Ctx>::insert(const Key& key, const Val& val)
    {
        if ( _count == _size ) return false;

        u32  hash = Ctx::hash(key);
        u32  numb = 0;
        Ctrl ctrl = {1, _count};

        for ( u32 i = 0; i < _size; i += 1 ) {
            u32 iter = (hash + i) % _size;
            u32 indx = _ctrl[iter].indx;

            if ( _ctrl[iter].dist == 0 ) {
                if ( numb != 0 )
                    _indx[_count] = numb - 1;
                else
                    _indx[_count] = iter;

                _head[_count] = key;
                _body[_count] = val;

                _ctrl[iter] = ctrl;

                _count += 1;

                break;
            }

            if ( iter == _indx[indx] ) {
                if ( Ctx::equals(_head[indx], key) )
                    return false;
            }

            if ( _ctrl[iter].dist < ctrl.dist ) {
                swap(_ctrl[iter], ctrl);

                if ( numb == 0 )
                    numb = _indx[indx] + 1;

                _indx[ctrl.indx] += 1;
                _indx[ctrl.indx] %= _size;
            }

            ctrl.dist += 1;
        }

        return true;

        // u32  hash = Ctx::get(key);
        // u32  indx = 0;
        // Ctrl ctrl = {key, 1, hash};
        // Body body = {val};

        // for ( u32 i = 0; i < _size; i += 1 ) {
        //     indx = (hash + i) % _size;

        //     if ( _ctrl[indx].dist != 0 ) {
        //         if ( hash == _ctrl[indx].hash ) {
        //             if ( Ctx::eql(_ctrl[indx].key, ctrl.key) )
        //                 break;
        //         }

        //         if ( _ctrl[indx].dist < ctrl.dist ) {
        //             swap(_ctrl[indx], ctrl);
        //             swap(_body[indx], body);
        //         }

        //         ctrl.dist += 1;
        //     } else {
        //         _ctrl[indx] = ctrl;
        //         _count += 1;

        //         break;
        //     }
        // }

        // _body[indx] = body;

        return true;
    }

    template <class Key, class Val, class Ctx>
    bool
    Robin_Map<Key, Val, Ctx>::remove(const Key&)
    {
        return false;

        // if ( _count == 0 ) return false;

        // u32 hash = Ctx::get(key);
        // u32 indx = 0;

        // for ( u32 i = 0; i < _size; i += 1 ) {
        //     indx = (hash + i) % _size;

        //     if ( _ctrl[indx].dist > i ) {
        //         if ( hash == _ctrl[indx].hash ) {
        //             if ( Ctx::eql(_ctrl[indx].key, key) )
        //                 break;
        //         }
        //     } else
        //         return false;
        // }

        // for ( u32 i = 0; i < _size; i += 1 ) {
        //     u32 next = (indx + 1) % _size;

        //     if ( _ctrl[next].dist > 1 ) {
        //         _ctrl[next].dist -= 1;

        //         _ctrl[indx] = _ctrl[next];
        //         _body[indx] = _body[next];
        //     } else
        //         break;

        //     indx = next;
        // }

        // _ctrl[indx].dist = 0;
        // _count -= 1;

        // return true;
    }

    template <class Key, class Val, class Ctx>
    Pair_Ref<const Key, const Val>
    Robin_Map<Key, Val, Ctx>::operator[](const Key& key) const
    {
        if ( _count == 0 ) return {};

        u32 hash = Ctx::hash(key);

        for ( u32 i = 0; i < _size; i += 1 ) {
            u32 iter = (hash + i) % _size;
            u32 indx = _ctrl[iter].indx;

            if ( _ctrl[iter].dist < i ) break;

            if ( iter == _indx[indx] ) {
                if ( Ctx::equals(_head[indx], key) )
                    return {key, _body[indx]};
            }
        }

        return {};
    }

    template <class Key, class Val, class Ctx>
    Pair_Ref<const Key, Val>
    Robin_Map<Key, Val, Ctx>::operator[](const Key& key)
    {
        if ( _count == 0 ) return {};

        u32 hash = Ctx::hash(key);

        for ( u32 i = 0; i < _size; i += 1 ) {
            u32 iter = (hash + i) % _size;
            u32 indx = _ctrl[iter].indx;

            if ( _ctrl[iter].dist < i ) break;

            if ( iter == _indx[indx] ) {
                if ( Ctx::equals(_head[indx], key) )
                    return {key, _body[indx]};
            }
        }

        return {};
    }
} // scent
