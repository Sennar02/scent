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
    Pair_Ref<Key, Val>::is_valid() const
    {
        return _key != 0;
    }

    template <class Key, class Val>
    const Key&
    Pair_Ref<Key, Val>::key() const
    {
        assert(_key != 0 && "The key does not exist");

        return *_key;
    }

    template <class Key, class Val>
    Key&
    Pair_Ref<Key, Val>::key()
    {
        assert(_key != 0 && "The key does not exist");

        return *_key;
    }

    template <class Key, class Val>
    const Val&
    Pair_Ref<Key, Val>::value() const
    {
        assert(_val != 0 && "The value does not exist");

        return *_val;
    }

    template <class Key, class Val>
    Val&
    Pair_Ref<Key, Val>::value()
    {
        assert(_val != 0 && "The value does not exist");

        return *_val;
    }
} // scent
