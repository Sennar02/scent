#ifndef SCENT_SLICE_HPP
#define SCENT_SLICE_HPP

#include <assert.h>

#include "types.hpp"

namespace scent
{
    template <class Val>
    struct Slice
    {
    private:
        /**
         *
         */
        Val* _pntr = 0;

        /**
         *
         */
        u32 _size = 0;

    public:
        /**
         *
         */
        Slice();

        /**
         *
         */
        Slice(Val* pntr, u32 size);

        /**
         *
         */
        void
        init(Val* pntr, u32 size);

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
        const Val&
        operator[](u32 index) const;

        /**
         *
         */
        Val&
        operator[](u32 index);
    };
} // scent

#include "slice.inl"

#endif // SCENT_SLICE_HPP
