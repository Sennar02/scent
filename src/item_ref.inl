#include "item_ref.hpp"

namespace scent
{
    template <class Val>
    Item_Ref<Val>::Item_Ref() {}

    template <class Val>
    Item_Ref<Val>::Item_Ref(Val& val)
    {
        _val = &val;
    }

    template <class Val>
    bool
    Item_Ref<Val>::exists() const
    {
        return _val != 0;
    }

    template <class Val>
    const Val&
    Item_Ref<Val>::val() const
    {
        assert(_val != 0 && "Val does not exist");

        return *_val;
    }

    template <class Val>
    Val&
    Item_Ref<Val>::val()
    {
        assert(_val != 0 && "Val does not exist");

        return *_val;
    }
} // scent
