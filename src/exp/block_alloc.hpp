#ifndef SCENT_BLOCK_ALLOC_HPP
#define SCENT_BLOCK_ALLOC_HPP

#include "alloc.hpp"

namespace scent
{
    struct Block_Alloc final
        : public Alloc
    {
    public:
        /**
         *
         */
        i8* _pntr = 0;

        /**
         *
         */
        void** _list = 0;

        /**
         *
         */
        u32 _size = 0;

        /**
         *
         */
        u32 _unit = 0;

        /**
         *
         */
        u32 _fill = 0;

        /**
         *
         */
        u32 _count = 0;

    public:
        /**
         *
         */
        Block_Alloc();

        /**
         *
         */
        Block_Alloc(void* pntr, u32 size, u32 unit, u8 align);

        /**
         *
         */
        void
        init(void* pntr, u32 size, u32 unit, u8 align);

        /**
         *
         */
        void
        drop();

        /**
         *
         */
        u32
        size() const;

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
        reserve(u32 size, u8 align = 1);

        /**
         *
         */
        void
        release(i8* pntr);
    };
} // scent

#endif // SCENT_BLOCK_ALLOC_HPP
