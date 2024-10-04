#include "slice.hpp"

namespace gr
{
    template <class Val, isize Len>
    const Val&
    Array<Val, Len>::operator[](isize index) const
    {
        gr_expect(0 < index && index <= items,
            "The index must be in range");

        return data[index - 1];
    }


    template <class Val, isize Len>
    Val&
    Array<Val, Len>::operator[](isize index)
    {
        gr_expect(0 < index && index <= items,
            "The index must be in range");

        return data[index - 1];
    }

    template <class Val>
    const Val&
    Slice<Val>::operator[](isize index) const
    {
        gr_expect(0 < index && index <= items,
            "The index must be in range");

        return data[index - 1];
    }

    template <class Val>
    Val&
    Slice<Val>::operator[](isize index)
    {
        gr_expect(0 < index && index <= items,
            "The index must be in range");

        return data[index - 1];
    }

    template <class Val, isize Len>
    Slice<Val>
    slice_from(Array<Val, Len>* array)
    {
        Slice<Val> self;

        gr_expect(array != 0, "The array must exist");

        self.data  = array->data;
        self.items = array->items;
        self.limit = array->items;

        return self;
    }

    template <class Val, isize Len>
    Slice<const Val>
    slice_from(const Array<Val, Len>* array)
    {
        Slice<const Val> self;

        gr_expect(array != 0, "The array must exist");

        self.data  = array->data;
        self.items = array->items;
        self.limit = array->items;

        return self;
    }

    template <class Val>
    Slice<Val>
    slice_init(Arena* arena, isize items)
    {
        static const isize WIDTH_VAL = gr_type_width(Val);
        static const isize ALIGN_VAL = gr_type_align(Val);

        Slice<Val> self;

        self.data = (Val*) arena_alloc(arena,
            ALIGN_VAL, WIDTH_VAL, items);

        if ( self.data != 0 ) {
            self.items = items;
            self.limit = items;
        }

        return self;
    }

    template <class Val>
    void
    slice_drop(Slice<Val>* slice)
    {
        gr_expect(slice != 0, "The slice must exist");

        auto& self = *slice;

        self.data  = 0;
        self.items = 0;
        self.limit = 0;
    }

    template <class Val>
    void
    slice_clear(Slice<Val>* slice)
    {
        gr_expect(slice != 0, "The slice must exist");

        auto& self = *slice;

        self.items = 0;
    }
} // namespace gr
