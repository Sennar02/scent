#ifndef CORE_ARENA_HPP
#define CORE_ARENA_HPP

#include "assert.hpp"
#include "types.hpp"

namespace core
{
    struct Block
    {
    public:
        Block* next;
        i8*    base;
        u32    curs;
        u32    size;
    };

    struct Arena
    {
    private:
        /**
         *
         */
        Block* _head = 0;

    public:
        /**
         *
         */
        Arena();

        /**
         *
         */
        Arena(u32 size);

        /**
         *
         */
        void
        init(u32 size);

        /**
         *
         */
        void
        drop();

        /**
         *
         */
        i8*
        alloc(u32 size, u8 align);

        /**
         *
         */
        void
        reset();
    };
} // namespace core

#endif // CORE_ARENA_HPP
