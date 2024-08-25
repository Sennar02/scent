#include "empty_alloc.hpp"

namespace scent
{
    u32
    Empty_Alloc::next(u8) const
    {
        return 0;
    }

    void
    Empty_Alloc::reset()
    {}

    i8*
    Empty_Alloc::acquire(u32, u8)
    {
        return 0;
    }

    i8*
    Empty_Alloc::resize(i8*, u32)
    {
        return 0;
    }

    void
    Empty_Alloc::release(i8*)
    {}
} // scent
