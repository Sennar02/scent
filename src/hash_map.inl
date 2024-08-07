#include "hash_map.hpp"

namespace scent
{
    template <class Key, class Val, class Hash>
    Hash_Map<Key, Val, Hash>::Hash_Map() {}

    template <class Key, class Val, class Hash>
    Hash_Map<Key, Val, Hash>::Hash_Map(Alloc& alloc, u32 size)
    {
        _ctrl = reserve<Ctrl>(alloc, size);
        _body = reserve<Body>(alloc, size);

        if ( _ctrl == 0 || _body == 0 ) {
            _body = release(alloc, _body);
            _ctrl = release(alloc, _ctrl);
        } else
            _size = size;
    }

    template <class Key, class Val, class Hash>
    void
    Hash_Map<Key, Val, Hash>::drop(Alloc& alloc)
    {
        _body = release(alloc, _body);
        _ctrl = release(alloc, _ctrl);

        if ( _ctrl == 0 && _body == 0 ) {
            _size  = 0;
            _count = 0;
        }
    }

    template <class Key, class Val, class Hash>
    void
    Hash_Map<Key, Val, Hash>::clear()
    {
        for ( u32 i = 0; i < _size; i += 1 )
            _ctrl[i].dist = 0;

        _count = 0;
    }

    template <class Key, class Val, class Hash>
    u32
    Hash_Map<Key, Val, Hash>::size() const
    {
        return _size;
    }

    template <class Key, class Val, class Hash>
    u32
    Hash_Map<Key, Val, Hash>::values() const
    {
        return _count;
    }

    template <class Key, class Val, class Hash>
    bool
    Hash_Map<Key, Val, Hash>::is_empty() const
    {
        return _count == 0;
    }

    template <class Key, class Val, class Hash>
    bool
    Hash_Map<Key, Val, Hash>::isnt_empty() const
    {
        return _count != 0;
    }

    template <class Key, class Val, class Hash>
    bool
    Hash_Map<Key, Val, Hash>::is_full() const
    {
        return _count == _size;
    }

    template <class Key, class Val, class Hash>
    bool
    Hash_Map<Key, Val, Hash>::isnt_full() const
    {
        return _count != _size;
    }

    template <class Key, class Val, class Hash>
    Pair_Ref<const Key, const Val>
    Hash_Map<Key, Val, Hash>::find(const Key& key) const
    {
        if ( _count == 0 ) return {};

        u32 hash = Hash::get(key);
        u32 indx = 0;

        for ( u32 i = 0; i < _size; i += 1 ) {
            indx = (hash + i) % _size;

            if ( _ctrl[indx].dist > i ) {
                if ( hash == _ctrl[indx].hash ) {
                    if ( Hash::eql(_ctrl[indx].key, key) )
                        break;
                }
            } else
                return {};
        }

        return {key, _body[indx].val};
    }

    template <class Key, class Val, class Hash>
    Pair_Ref<const Key, Val>
    Hash_Map<Key, Val, Hash>::find(const Key& key)
    {
        if ( _count == 0 ) return {};

        u32 hash = Hash::get(key);
        u32 indx = 0;

        for ( u32 i = 0; i < _size; i += 1 ) {
            indx = (hash + i) % _size;

            if ( _ctrl[indx].dist > i ) {
                if ( hash == _ctrl[indx].hash ) {
                    if ( Hash::eql(_ctrl[indx].key, key) )
                        break;
                }
            } else
                return {};
        }

        return {key, _body[indx].val};
    }

    template <class Key, class Val, class Hash>
    bool
    Hash_Map<Key, Val, Hash>::insert(const Key& key, const Val& val)
    {
        if ( _count == _size ) return false;

        u32  hash = Hash::get(key);
        u32  indx = 0;
        Ctrl ctrl = {key, 1, hash};
        Body body = {val};

        for ( u32 i = 0; i < _size; i += 1 ) {
            indx = (hash + i) % _size;

            if ( _ctrl[indx].dist != 0 ) {
                if ( hash == _ctrl[indx].hash ) {
                    if ( Hash::eql(_ctrl[indx].key, ctrl.key) )
                        break;
                }

                if ( _ctrl[indx].dist < ctrl.dist ) {
                    swap(_ctrl[indx], ctrl);
                    swap(_body[indx], body);
                }

                ctrl.dist += 1;
            } else {
                _ctrl[indx] = ctrl;
                _count += 1;

                break;
            }
        }

        _body[indx] = body;

        return true;
    }

    template <class Key, class Val, class Hash>
    bool
    Hash_Map<Key, Val, Hash>::remove(const Key& key)
    {
        if ( _count == 0 ) return false;

        u32 hash = Hash::get(key);
        u32 indx = 0;

        for ( u32 i = 0; i < _size; i += 1 ) {
            indx = (hash + i) % _size;

            if ( _ctrl[indx].dist > i ) {
                if ( hash == _ctrl[indx].hash ) {
                    if ( Hash::eql(_ctrl[indx].key, key) )
                        break;
                }
            } else
                return false;
        }

        for ( u32 i = 0; i < _size; i += 1 ) {
            u32 next = (indx + 1) % _size;

            if ( _ctrl[next].dist > 1 ) {
                _ctrl[next].dist -= 1;

                _ctrl[indx] = _ctrl[next];
                _body[indx] = _body[next];
            } else
                break;

            indx = next;
        }

        _ctrl[indx].dist = 0;
        _count -= 1;

        return true;
    }
} // scent
