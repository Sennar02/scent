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
        i8* _pntr = 0;

        /**
         *
         */
        i8* _last = 0;

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
        Arena_Alloc();

        /**
         *
         */
        Arena_Alloc(void* pntr, u32 size);

        /**
         *
         */
        void
        init(void* pntr, u32 size);

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
        acquire(i8* pntr, u32 size, u8 align);

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

#endif // SCENT_ARENA_ALLOC_HPP
