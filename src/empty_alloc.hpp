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
        u32
        next(u8 align) const;

        /**
         *
         */
        void
        reset();

        /**
         *
         */
        i8*
        acquire(u32 size, u8 align);

        /**
         *
         */
        i8*
        resize(i8* pntr, u32 size);

        /**
         *
         */
        void
        release(i8* pntr);
    };
} // scent

#endif // SCENT_EMPTY_ALLOC_HPP
