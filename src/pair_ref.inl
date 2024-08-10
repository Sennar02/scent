#include "pair_ref.hpp"

namespace scent
{
    template <class Key, class Val>
    Pair_Ref<Key, Val>::Pair_Ref() {}

    template <class Key, class Val>
    Pair_Ref<Key, Val>::Pair_Ref(Key& key, Val& val)
    {
        init(key, val);
    }

    template <class Key, class Val>
    void
    Pair_Ref<Key, Val>::init(Key& key, Val& val)
    {
        _key = &key;
        _val = &val;
    }

    template <class Key, class Val>
    void
    Pair_Ref<Key, Val>::drop()
    {
        _key = 0;
        _val = 0;
    }

    template <class Key, class Val>
    bool
    Pair_Ref<Key, Val>::exists() const
    {
        return _key != 0;
    }

    template <class Key, class Val>
    const Key&
    Pair_Ref<Key, Val>::key() const
    {
        assert(_key != 0 && "Key does not exist");

        return *_key;
    }

    template <class Key, class Val>
    Key&
    Pair_Ref<Key, Val>::key()
    {
        assert(_key != 0 && "Key does not exist");

        return *_key;
    }

    template <class Key, class Val>
    const Val&
    Pair_Ref<Key, Val>::val() const
    {
        assert(_val != 0 && "Val does not exist");

        return *_val;
    }

    template <class Key, class Val>
    Val&
    Pair_Ref<Key, Val>::val()
    {
        assert(_val != 0 && "Val does not exist");

        return *_val;
    }
} // scent
