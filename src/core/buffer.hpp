#ifndef CORE_BUFFER_HPP
#define CORE_BUFFER_HPP

#include "assert.hpp"
#include "types.hpp"
#include "memory.hpp"

namespace core
{
    struct Buffer
    {
    private:
        /**
         *
         */
        i8* _base = 0;

        /**
         *
         */
        i8* _curr = 0;

        /**
         *
         */
        uarch _size = 0;

    public:
        /**
         *
         */
        Buffer();

        /**
         *
         */
        Buffer(i8* pntr, uarch size);

        /**
         *
         */
        void
        init(i8* pntr, uarch size);

        /**
         *
         */
        void
        drop();

        /**
         *
         */
        uarch
        size() const;

        /**
         *
         */
        i8*
        require(uarch size, u8 align);

        /**
         *
         */
        void
        reset();
    };
} // namespace core

#endif // CORE_BUFFER_HPP
