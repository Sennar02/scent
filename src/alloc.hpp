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
        acquire(i8* pntr, u32 size, u8 align) = 0;

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
    typed_acquire(Alloc* alloc, Val* pntr, u32 size);

    /**
     *
     */
    template <class Val>
    Val*
    typed_resize(Alloc* alloc, Val* pntr, u32 size);

    /**
     *
     */
    template <class Val>
    void
    typed_release(Alloc* alloc, Val* pntr);
} // scent

#include "alloc.inl"

#endif // SCENT_ALLOC_HPP
