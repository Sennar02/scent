#ifndef GR_CORE_SLICE_HPP
#define GR_CORE_SLICE_HPP

#include "expect.hpp"
#include "types.hpp"

namespace gr
{
    template <class Val, isize Len>
    struct Array {
        //
        //
        //
        static const isize items = Len;

        //
        //
        //
        Val data[Len];

        //
        //
        //
        const Val&
        operator[](isize index) const;

        //
        //
        //
        Val&
        operator[](isize index);
    };

    template <class Val>
    struct Slice {
        //
        //
        //
        Val* data = 0;

        //
        //
        //
        isize items = 0;

        //
        //
        //
        isize limit = 0;

        //
        //
        //
        const Val&
        operator[](isize index) const;

        //
        //
        //
        Val&
        operator[](isize index);
    };

    //
    //
    //
    template <class Val, isize Len>
    Slice<Val>
    slice_from(Array<Val, Len>* array);

    //
    //
    //
    template <class Val, isize Len>
    Slice<const Val>
    slice_from(const Array<Val, Len>* array);

    //
    //
    //
    template <class Val>
    Slice<Val>
    slice_init(Arena* arena, isize size);

    //
    //
    //
    template <class Val>
    void
    slice_drop(Slice<Val>* self);

    //
    //
    //
    template <class Val>
    void
    slice_clear(Slice<Val>* self);
} // namespace gr

#include "slice.inl"

#endif // GR_CORE_SLICE_HPP
