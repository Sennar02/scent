#include "item_ref.hpp"

namespace scent
{
    template <class Val>
    Item_Ref<Val>::Item_Ref() {}

    template <class Val>
    Item_Ref<Val>::Item_Ref(Val& val)
    {
        init(val);
    }

    template <class Val>
    void
    Item_Ref<Val>::init(Val& val)
    {
        _val = &val;
    }

    template <class Val>
    void
    Item_Ref<Val>::drop()
    {
        _val = 0;
    }

    template <class Val>
    bool
    Item_Ref<Val>::is_valid() const
    {
        return _val != 0;
    }

    template <class Val>
    const Val&
    Item_Ref<Val>::value() const
    {
        assert(_val != 0 && "The value does not exist");

        return *_val;
    }

    template <class Val>
    Val&
    Item_Ref<Val>::value()
    {
        assert(_val != 0 && "The value does not exist");

        return *_val;
    }
} // scent
