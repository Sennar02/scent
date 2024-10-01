#include <malloc.h>
#include <string.h>

#include "arena.hpp"

namespace gr
{
    byte*
    forw_align(byte* pntr, isize align)
    {
        gr_run_assert(align != 0 && (align & (align - 1)) == 0,
            "The alignment must be a power of two");

        usize value = (usize) pntr;
        isize delta = -value & (align - 1);

        return pntr + delta;
    }

    Arena
    arena_init(isize size)
    {
        Arena self = {0};

        gr_run_assert(size >= 0, "The size must be non negative");

        self.head = (byte*) malloc(size + SIZE_ARENA);

        if ( self.head != 0 ) {
            self.tail = self.head + size;
            self.curr = self.head;
        }

        return self;
    }

    void
    arena_drop(Arena* _self)
    {
        auto& self = *_self;

        self.head = 0;
        self.tail = 0;
        self.curr = 0;
        self.next = 0;
    }

    byte*
    arena_alloc_impl(Arena* _self, isize align, isize size, isize count)
    {
        auto& self = *_self;

        byte* pntr = 0;
        byte* curr = forw_align(self.curr, align);

        isize fill = curr - self.curr;
        isize diff = self.tail - self.head;

        if ( diff >= size * count + fill ) {
            self.curr = curr + size;
            pntr      = curr;

            memset(curr, 0, size);
        }

        return pntr;

    }

    byte*
    arena_alloc(Arena* _self, isize align, isize size, isize count)
    {
        gr_run_assert(align > 0, "The alignment must be positive");
        gr_run_assert(size  > 0, "The size must be positive");

        return 0;
    }

    void
    arena_reset(Arena* _self)
    {
        auto& self = *_self;

        self.curr = self.head;
    }
} // namespace gr
