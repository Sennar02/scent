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
        for ( u32 i = 0; i < _size; i += 1u )
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
        Ctrl ctrl = {1u, _count};
        u32  help = 0;
        bool swpd = false;

        for ( u32 i = 0; i < _size; i += 1u ) {
            u32 iter = (hash + i) % _size;
            u32 indx = _ctrl[iter].indx;

            if ( _ctrl[iter].dist == 0 ) {
                if ( swpd == false ) help = iter;

                _ctrl[iter] = ctrl;

                _indx[_count] = help;
                _head[_count] = key;
                _body[_count] = val;

                _count += 1u;

                break;
            }

            if ( iter == _indx[indx] ) {
                if ( Ctx::equals(_head[indx], key) )
                    return false;
            }

            if ( _ctrl[iter].dist < ctrl.dist ) {
                swap(_ctrl[iter], ctrl);

                if ( swpd == false ) {
                    help = _indx[indx];
                    swpd = true;
                }

                _indx[ctrl.indx] += 1u;
                _indx[ctrl.indx] %= _size;
            }

            ctrl.dist += 1u;
        }

        return true;
    }

    template <class Key, class Val, class Ctx>
    bool
    Robin_Map<Key, Val, Ctx>::update(const Key& key, const Val& val)
    {
        if ( _count == _size ) return false;

        u32  hash = Ctx::hash(key);
        Ctrl ctrl = {1u, _count};
        u32  help = 0;
        bool swpd = false;

        for ( u32 i = 0; i < _size; i += 1u ) {
            u32 iter = (hash + i) % _size;
            u32 indx = _ctrl[iter].indx;

            if ( _ctrl[iter].dist == 0 ) {
                if ( swpd == false ) help = iter;

                _ctrl[iter] = ctrl;

                _indx[_count] = help;
                _head[_count] = key;
                _body[_count] = val;

                _count += 1u;

                break;
            }

            if ( iter == _indx[indx] ) {
                if ( Ctx::equals(_head[indx], key) ) {
                    _body[indx] = val;

                    break;
                }
            }

            if ( _ctrl[iter].dist < ctrl.dist ) {
                swap(_ctrl[iter], ctrl);

                if ( swpd == false ) {
                    help = _indx[indx];
                    swpd = true;
                }

                _indx[ctrl.indx] += 1u;
                _indx[ctrl.indx] %= _size;
            }

            ctrl.dist += 1u;
        }

        return true;
    }

    template <class Key, class Val, class Ctx>
    bool
    Robin_Map<Key, Val, Ctx>::remove(const Key& key)
    {
        if ( _count == 0 ) return false;

        u32 hash = Ctx::hash(key);
        u32 iter = 0;

        for ( u32 i = 0; i < _size; i += 1u ) {
            iter = (hash + i) % _size;

            if ( _ctrl[iter].dist < i ) return false;

            u32 indx = _ctrl[iter].indx;

            if ( iter == _indx[indx] ) {
                if ( Ctx::equals(_head[indx], key) ) {
                    _count -= 1u;

                    u32 last = _indx[_count];

                    swap(_body[indx], _body[_count]);
                    swap(_head[indx], _head[_count]);
                    swap(_indx[indx], _indx[_count]);

                    _ctrl[last].indx = indx;

                    break;
                }
            }
        }

        for ( u32 i = 0; i < _size; i += 1u ) {
            u32 next = (iter + 1u) % _size;
            u32 indx = _ctrl[next].indx;

            if ( _ctrl[next].dist < 2u ) break;

            _ctrl[iter] = _ctrl[next];
            _ctrl[iter].dist -= 1u;

            _indx[indx] += _size;
            _indx[indx] -= 1u;
            _indx[indx] %= _size;

            iter = next;
        }

        _ctrl[iter].dist = 0;

        return true;
    }

    template <class Key, class Val, class Ctx>
    Pair_Ref<const Key, const Val>
    Robin_Map<Key, Val, Ctx>::find(const Key& key) const
    {
        if ( _count == 0 ) return {};

        u32 hash = Ctx::hash(key);

        for ( u32 i = 0; i < _size; i += 1u ) {
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
    Robin_Map<Key, Val, Ctx>::find(const Key& key)
    {
        if ( _count == 0 ) return {};

        u32 hash = Ctx::hash(key);

        for ( u32 i = 0; i < _size; i += 1u ) {
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
    const Val&
    Robin_Map<Key, Val, Ctx>::operator[](const Key& key) const
    {
        assert(_count != 0 && "Unknown key");

        u32 hash = Ctx::hash(key);
        u32 iter = 0;
        u32 indx = 0;

        for ( u32 i = 0; i < _size; i += 1u ) {
            iter = (hash + i) % _size;
            indx = _ctrl[iter].indx;

            assert(_ctrl[iter].dist < i && "Unknown key");

            if ( iter == _indx[indx] ) {
                if ( Ctx::equals(_head[indx], key) )
                    break;
            }
        }

        return {key, _body[indx]};
    }

    template <class Key, class Val, class Ctx>
    Val&
    Robin_Map<Key, Val, Ctx>::operator[](const Key& key)
    {
        assert(_count != 0 && "Unknown key");

        u32 hash = Ctx::hash(key);
        u32 iter = 0;
        u32 indx = 0;

        for ( u32 i = 0; i < _size; i += 1u ) {
            iter = (hash + i) % _size;
            indx = _ctrl[iter].indx;

            assert(_ctrl[iter].dist < i && "Unknown key");

            if ( iter == _indx[indx] ) {
                if ( Ctx::equals(_head[indx], key) )
                    break;
            }
        }

        return {key, _body[indx]};
    }
} // scent
