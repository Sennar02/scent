#ifndef SCENT_ALLOC_HPP
#define SCENT_ALLOC_HPP

#include "types.hpp"

namespace scent
{
    /**
     *
     */
    bool
    is_pow_2(u32 value);

    /**
     *
     */
    i8*
    next_aligned(void* memory, u8 align);

    /**
     *
     */
    i8*
    null_if(void* memory, bool state);

    struct Alloc
    {
        /**
         *
         */
        virtual u32
        next(u8 align) const = 0;

        /**
         *
         */
        virtual void
        reset() = 0;

        /**
         *
         */
        virtual i8*
        acquire(u32 size, u8 align) = 0;

        /**
         *
         */
        virtual i8*
        resize(i8* pntr, u32 size) = 0;

        /**
         *
         */
        virtual void
        release(i8* pntr) = 0;
    };

    /**
     *
     */
    template <class Val>
    Val*
    alloc_acquire(Alloc* alloc, u32 size);

    /**
     *
     */
    template <class Val>
    Val*
    alloc_resize(Alloc* alloc, void* pntr, u32 size);

    /**
     *
     */
    template <class Val>
    void
    alloc_release(Alloc* alloc, void* pntr);
} // scent

#include "alloc.inl"

#endif // SCENT_ALLOC_HPP
