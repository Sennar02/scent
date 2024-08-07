#ifndef SCENT_EMPTY_ALLOC_HPP
#define SCENT_EMPTY_ALLOC_HPP

#include "alloc.hpp"

namespace scent
{
    struct Empty_Alloc final
        : public Alloc
    {
        /**
         *
         */
        i8*
        reserve(u32 items, u32 bytes, u8 align);

        /**
         *
         */
        i8*
        release(i8* pntr);
    };
} // scent

#endif // SCENT_EMPTY_ALLOC_HPP
