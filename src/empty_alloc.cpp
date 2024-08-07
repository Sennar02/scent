#include "empty_alloc.hpp"

namespace scent
{
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
