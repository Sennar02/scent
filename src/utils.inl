#include "utils.hpp"

namespace scent
{
    template <class Val>
    Val
    extr(Val& v1, const Val& v2)
    {
        Val res = v1;

        v1 = v2;

        return res;
    }

    template <class Val>
    void
    swap(Val& v1, Val& v2)
    {
        v2 = extr(v1, v2);
    }
} // scent
