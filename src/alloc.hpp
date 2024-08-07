#ifndef SCENT_ALLOC_HPP
#define SCENT_ALLOC_HPP

#include "types.hpp"

namespace scent
{
    /**
     *
     */
    i8*
    next_aligned(i8* memory, u8 align);

    /**
     *
     */
    i8*
    null_if(i8* memory, bool state);

    struct Alloc
    {
        /**
         *
         */
        virtual i8*
        reserve(u32 items, u32 bytes, u8 align) = 0;

        /**
         *
         */
        virtual i8*
        release(i8* pntr) = 0;
    };

    /**
     *
     */
    template <class Val>
    Val*
    reserve(Alloc& alloc, u32 items);

    /**
     *
     */
    template <class Val>
    Val*
    release(Alloc& alloc, Val* pntr);
} // scent

#include "alloc.inl"

#endif // SCENT_ALLOC_HPP
