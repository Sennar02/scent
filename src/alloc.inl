#include "alloc.hpp"

namespace scent
{
    template <class Val>
    Val*
    reserve(Alloc& alloc, u32 numb)
    {
        void* pntr = alloc.reserve(numb,
            sizeof(Val), alignof(Val)
        );

        return (Val*) pntr;
    }

    template <class Val>
    Val*
    release(Alloc& alloc, Val* pntr)
    {
        return (Val*) alloc.release((i8*) pntr);
    }
} // scent
