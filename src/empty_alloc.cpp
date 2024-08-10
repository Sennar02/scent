#include "empty_alloc.hpp"

namespace scent
{
    void
    Empty_Alloc::reset()
    {}

    i8*
    Empty_Alloc::reserve(u32, u32, u8)
    {
        return 0;
    }

    i8*
    Empty_Alloc::release(i8*)
    {
        return 0;
    }
} // scent
