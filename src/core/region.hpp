#ifndef CORE_REGION_HPP
#define CORE_REGION_HPP

#include "assert.hpp"
#include "types.hpp"
#include "buffer.hpp"

namespace core
{
    struct Buffer_Node;

    struct Region
    {
    private:
        /**
         *
         */
        Buffer_Node* _list = 0;

        /**
         *
         */
        f32 _grow = 0.0f;

    public:
        /**
         *
         */
        Region();

        /**
         *
         */
        Region(uarch size, f32 grow = 1.0f);

        /**
         *
         */
        void
        init(uarch size, f32 grow = 1.0f);

        /**
         *
         */
        void
        drop();

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

#endif // CORE_REGION_HPP
