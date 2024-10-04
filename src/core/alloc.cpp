#include <malloc.h>

#include "alloc.hpp"

namespace gr
{
    byte*
    alloc_request(Alloc* alloc, isize align, isize width, isize items)
    {
        gr_expect(alloc != 0, "The allocator must exist");
        gr_expect(align  > 0, "The alignment must be positive");
        gr_expect(width  > 0, "The width must be positive");

        auto& self = *alloc;

        return ((Request_Func*) self.request_func)
            (self.alloc_ctxt, align, width, items);
    }

    void
    alloc_release(Alloc* alloc, byte* block, isize width, isize items)
    {
        gr_expect(alloc != 0, "The allocator must exist");
        gr_expect(width  > 0, "The width must be positive");

        auto& self = *alloc;

        return ((Release_Func*) self.release_func)
            (self.alloc_ctxt, block, width, items);
    }

    byte*
    base_request(void* ctxt, isize align, isize width, isize items)
    {
        gr_expect(ctxt == 0, "The context must not exist");

        return (byte*) calloc(items, width);
    }

    void
    base_release(void* ctxt, byte* block, isize width, isize items)
    {
        gr_expect(ctxt == 0, "The context must not exist");

        free(block);
    }

    Alloc
    base_alloc_init()
    {
        Alloc self;

        self.request_func = (byte*) &base_request;
        self.release_func = (byte*) &base_release;

        return self;
    }
} // namespace gr
