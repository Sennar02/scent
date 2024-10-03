#include <malloc.h>

#include "alloc.hpp"

namespace gr
{
    byte*
    base_request(void* ctxt, isize align, isize size, isize count)
    {
        gr_run_assert(ctxt == 0, "The context must not exist");

        return (byte*) calloc(count, size);
    }

    void
    base_release(void* ctxt, byte* pntr, isize size, isize count)
    {
        gr_run_assert(ctxt == 0, "The context must not exist");

        free(pntr);
    }

    Alloc
    base_alloc_init()
    {
        Alloc self = {0};

        self.request_func = (byte*) &base_request;
        self.release_func = (byte*) &base_release;
        self.alloc_ctxt   = 0;

        return self;
    }

    byte*
    alloc_request(Alloc* alloc, isize align, isize size, isize count)
    {
        gr_run_assert(alloc != 0, "The allocator must exist");
        gr_run_assert(align  > 0, "The alignment must be positive");
        gr_run_assert(size   > 0, "The size must be positive");

        auto& self = *alloc;

        return ((Request_Func*) self.request_func)
            (self.alloc_ctxt, align, size, count);
    }

    void
    alloc_release(Alloc* alloc, byte* pntr, isize size, isize count)
    {
        gr_run_assert(alloc != 0, "The allocator must exist");
        gr_run_assert(size   > 0, "The size must be positive");

        auto& self = *alloc;

        return ((Release_Func*) self.release_func)
            (self.alloc_ctxt, pntr, size, count);
    }
} // namespace gr
