#ifndef GR_CORE_SLICE_HPP
#define GR_CORE_SLICE_HPP

#include <core/types.hpp>
#include <core/arena.hpp>
#include <core/array.hpp>
#include <core/buff.hpp>

namespace gr
{
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
    template <class Val>
    Slice<Val>
    slice_copy(Slice<Val>* other, Arena* arena);

    //
    //
    //
    template <class Val>
    Slice<Val>
    slice_empty(Slice<Val>* slice);

    //
    //
    //
    template <class Val>
    Slice<Val>
    slice_fill(Slice<Val>* slice, const Val& value);

    //
    //
    //
    template <class Val>
    Slice<Val>
    slice_resize(Slice<Val>* slice, Arena* arena, isize items);

    //
    //
    //
    template <class Val>
    Slice<Val>
    slice_insert(Slice<Val>* slice, Arena* arena, isize index, isize items, const Val& value);

    //
    //
    //
    template <class Val>
    Slice<Val>
    slice_insert(Slice<Val>* slice, Arena* arena, isize index, const Array<Val>& array);

    //
    //
    //
    template <class Val>
    Slice<Val>
    slice_insert(Slice<Val>* slice, Arena* arena, isize index, Slice<Val>* other);

    //
    //
    //
    template <class Val>
    Slice<Val>
    slice_remove(Slice<Val>* slice, isize index, isize items);

    //
    //
    //
    template <class Val>
    Slice<Val>
    slice_push(Slice<Val>* slice, Arena* arena, isize index, isize items, const Val& value);

    //
    //
    //
    template <class Val>
    Slice<Val>
    slice_push(Slice<Val>* slice, Arena* arena, isize index, const Array<Val>& array);

    //
    //
    //
    template <class Val>
    Slice<Val>
    slice_push(Slice<Val>* slice, Arena* arena, isize index, Slice<Val>* other);

    //
    //
    //
    template <class Val>
    Slice<Val>
    slice_pull(Slice<Val>* slice, isize index, isize items);

    //
    //
    // Implementation.
    //
    //

    template <class Val>
    const Val&
    Slice<Val>::operator[](isize index) const
    {
        gr_exec_expect(0 < index && index <= items,
            "The index must be in range");

        return data[index - 1];
    }

    template <class Val>
    Val&
    Slice<Val>::operator[](isize index)
    {
        gr_exec_expect(0 < index && index <= items,
            "The index must be in range");

        return data[index - 1];
    }

    template <class Val>
    Slice<Val>
    slice_copy(Slice<Val>* other, Arena* arena)
    {
        static const isize WIDTH_VAL = gr_type_width(Val);
        static const isize ALIGN_VAL = gr_type_align(Val);

        gr_exec_expect(other != 0, "The other slice must exist");

        Slice<Val> self;

        byte* data = arena_alloc(arena,
            ALIGN_VAL, WIDTH_VAL, other->limit);

        if ( data != 0 ) {
            isize bytes = WIDTH_VAL * other->items;
            auto  bufd  = buff_from(data, 0, bytes);
            auto  bufs  = buff_from((byte*) other->data,
                bytes, bytes);

            buff_copy(&bufd, &bufs);

            gr_exec_expect(bufd.error == BUFF_ERROR_NONE,
                "The operation must succeed");

            self.data  = (Val*) data;
            self.items = other->items;
            self.limit = other->limit;
        }

        return self;
    }

    template <class Val>
    Slice<Val>
    slice_empty(Slice<Val>* slice)
    {
        gr_exec_expect(slice != 0, "The slice must exist");

        auto& self = *slice;

        self.items = 0;

        return self;
    }

    template <class Val>
    Slice<Val>
    slice_fill(Slice<Val>* slice, const Val& value)
    {
        gr_exec_expect(slice != 0, "The slice must exist");

        auto& self = *slice;

        for ( isize i = self.items; i < self.limit; i += 1 )
            self.data[i] = value;

        return self;
    }

    template <class Val>
    Slice<Val>
    slice_resize(Slice<Val>* slice, Arena* arena, isize items)
    {
        static const isize WIDTH_VAL = gr_type_width(Val);
        static const isize ALIGN_VAL = gr_type_align(Val);

        gr_exec_expect(slice != 0, "The slice must exist");

        auto& self = *slice;
        auto* data = (byte*) self.data;

        if ( self.limit >= items ) return self;

        Slice<Val> resl = {};

        data = arena_resize(arena, data,
            ALIGN_VAL, WIDTH_VAL, items);

        if ( data != 0 ) {
            resl.data  = (Val*) data;
            resl.items = self.items;
            resl.limit = items;
        }

        return resl;
    }

    template <class Val>
    Slice<Val>
    slice_insert(Slice<Val>* slice, Arena* arena, isize index, isize items, const Val& value)
    {
        gr_exec_expect(slice != 0, "The slice must exist");

        auto& self  = *slice;
        auto  resl  = self;
        isize extra = gr_max(resl.limit, items);

        if ( index < 1 || index - 1 > resl.items || items < 1 )
            return resl;

        index = index - 1;

        if ( resl.limit - items < resl.items ) {
            if ( MAX_ISIZE - extra < resl.limit || arena == 0 )
                return resl;

            resl = slice_resize(slice, arena, resl.limit + extra);

            if ( resl.data == 0 )
                return resl;
        }

        for ( isize i = resl.items - 1; i >= index; i -= 1 )
            resl.data[i + items] = resl.data[i];

        for ( isize i = 0; i < items; i += 1 )
            resl.data[i + index] = value;

        resl.items += items;

        return resl;
    }

    template <class Val>
    Slice<Val>
    slice_insert(Slice<Val>* slice, Arena* arena, isize index, const Array<Val>& array)
    {
        gr_exec_expect(slice != 0, "The slice must exist");

        auto& self  = *slice;
        auto  resl  = self;
        isize items = array.items;
        isize extra = gr_max(resl.limit, items);

        if ( index < 1 || index - 1 > resl.items || items < 1 )
            return resl;

        index = index - 1;

        if ( resl.limit - items < resl.items ) {
            if ( MAX_ISIZE - extra < resl.limit || arena == 0 )
                return resl;

            resl = slice_resize(slice, arena, resl.limit + extra);

            if ( resl.data == 0 )
                return resl;
        }

        for ( isize i = resl.items - 1; i >= index; i -= 1 )
            resl.data[i + items] = resl.data[i];

        for ( isize i = 0; i < items; i += 1 )
            resl.data[i + index] = array[i + 1];

        resl.items += items;

        return resl;
    }

    template <class Val>
    Slice<Val>
    slice_insert(Slice<Val>* slice, Arena* arena, isize index, Slice<Val>* other)
    {
        gr_exec_expect(slice != 0, "The slice must exist");
        gr_exec_expect(other != 0, "The other slice must exist");

        auto& self  = *slice;
        auto  resl  = self;
        isize items = other->items;
        isize extra = gr_max(resl.limit, items);

        if ( index < 1 || index - 1 > resl.items || items < 1 )
            return resl;

        index = index - 1;

        if ( resl.limit - items < resl.items ) {
            if ( MAX_ISIZE - extra < resl.limit || arena == 0 )
                return resl;

            resl = slice_resize(slice, arena, resl.limit + extra);

            if ( resl.data == 0 )
                return resl;
        }

        for ( isize i = resl.items - 1; i >= index; i -= 1 )
            resl.data[i + items] = resl.data[i];

        for ( isize i = 0; i < items; i += 1 )
            resl.data[i + index] = other->data[i];

        resl.items += items;

        return resl;
    }

    template <class Val>
    Slice<Val>
    slice_remove(Slice<Val>* slice, isize index, isize items)
    {
        gr_exec_expect(slice != 0, "The slice must exist");

        auto& self = *slice;

        if ( items < 1 || items > self.items ) return self;
        if ( index < 1 || index > self.items ) return self;

        index       = index - 1;
        self.items -= items;

        for ( isize i = index; i <= self.items; i += 1 )
            self.data[i] = self.data[i + items];

        return self;
    }

    template <class Val>
    Slice<Val>
    slice_push(Slice<Val>* slice, Arena* arena, isize index, isize items, const Val& value)
    {
        gr_exec_expect(slice != 0, "The slice must exist");

        auto& self  = *slice;
        auto  resl  = self;
        isize extra = gr_max(resl.limit, items);

        if ( index < 1 || index - 1 > resl.items || items < 1 )
            return resl;

        index = index - 1;

        if ( resl.limit - items < resl.items ) {
            if ( MAX_ISIZE - extra < resl.limit || arena == 0 )
                return resl;

            resl = slice_resize(slice, arena, resl.limit + extra);

            if ( resl.data == 0 )
                return resl;
        }

        for ( isize i = 0; i < items; i += 1 ) {
            isize j = items - i - 1;

            resl.data[j + resl.items] = resl.data[i + index];
            resl.data[i + index]      = value;
        }

        resl.items += items;

        return resl;
    }

    template <class Val>
    Slice<Val>
    slice_push(Slice<Val>* slice, Arena* arena, isize index, const Array<Val>& array)
    {
        gr_exec_expect(slice != 0, "The slice must exist");

        auto& self  = *slice;
        auto  resl  = self;
        isize items = array.items;
        isize extra = gr_max(resl.limit, items);

        if ( index < 1 || index - 1 > resl.items || items < 1 )
            return resl;

        index = index - 1;

        if ( resl.limit - items < resl.items ) {
            if ( MAX_ISIZE - extra < resl.limit || arena == 0 )
                return resl;

            resl = slice_resize(slice, arena, resl.limit + extra);

            if ( resl.data == 0 )
                return resl;
        }

        for ( isize i = 0; i < items; i += 1 ) {
            isize j = items - i - 1;

            resl.data[j + resl.items] = resl.data[i + index];
            resl.data[i + index]      = array[i + 1];
        }

        resl.items += items;

        return resl;
    }

    template <class Val>
    Slice<Val>
    slice_push(Slice<Val>* slice, Arena* arena, isize index, Slice<Val>* other)
    {
        gr_exec_expect(slice != 0, "The slice must exist");
        gr_exec_expect(other != 0, "The other slice must exist");

        auto& self  = *slice;
        auto  resl  = self;
        isize items = other->items;
        isize extra = gr_max(resl.limit, items);

        if ( index < 1 || index - 1 > resl.items || items < 1 )
            return resl;

        index = index - 1;

        if ( resl.limit - items < resl.items ) {
            if ( MAX_ISIZE - extra < resl.limit || arena == 0 )
                return resl;

            resl = slice_resize(slice, arena, resl.limit + extra);

            if ( resl.data == 0 )
                return resl;
        }

        for ( isize i = 0; i < items; i += 1 ) {
            isize j = items - i - 1;

            resl.data[j + resl.items] = resl.data[i + index];
            resl.data[i + index]      = other->data[i];
        }

        resl.items += items;

        return resl;
    }

    template <class Val>
    Slice<Val>
    slice_pull(Slice<Val>* slice, isize index, isize items)
    {
        gr_exec_expect(slice != 0, "The slice must exist");

        auto& self = *slice;

        if ( items < 1 || items > self.items ) return self;
        if ( index < 1 || index > self.items ) return self;

        index       = index - 1;
        self.items -= items;

        for ( isize i = 0; i < items; i += 1 ) {
            isize j = items - i - 1;

            self.data[i + index] = self.data[j + self.items];
        }

        return self;
    }
} // namespace gr

#endif // GR_CORE_SLICE_HPP
