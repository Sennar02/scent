#ifndef SCENT_ARENA_ALLOC_HPP
#define SCENT_ARENA_ALLOC_HPP

#include "alloc.hpp"

namespace scent
{
    struct Arena_Alloc final
        : public Alloc
    {
    private:
        /**
         *
         */
        i8* _base = 0;

        /**
         *
         */
        i8* _next = 0;

        /**
         *
         */
        u32 _size = 0;

    public:
        /**
         *
         */
        Arena_Alloc(u32 bytes);

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

#endif // SCENT_ARENA_ALLOC_HPP
