#ifndef GR_CORE_ALLOC_HPP
#define GR_CORE_ALLOC_HPP

#include "assert.hpp"
#include "types.hpp"

namespace gr
{
    using Request_Func = byte*
        (void* ctxt, isize align, isize size, isize count);

    using Release_Func = void
        (void* ctxt, byte* pntr, isize size, isize count);

    struct Alloc {
        //
        //
        //
        byte* request_func;

        //
        //
        //
        byte* release_func;

        //
        //
        //
        byte* alloc_ctxt;
    };

    static const isize SIZE_ALLOC = gr_type_size(Alloc);

    gr_cpl_assert(SIZE_ALLOC == 3 * SIZE_ISIZE, "Unexpected type size");

    static const isize ALIGN_ALLOC = gr_type_align(Alloc);

    gr_cpl_assert(ALIGN_ALLOC == 1 * ALIGN_ISIZE, "Unexpected type alignment");

    byte*
    base_request(void* ctxt, isize align, isize size, isize count);

    void
    base_release(void* ctxt, byte* pntr, isize size, isize count);

    Alloc
    base_alloc_init();

    byte*
    alloc_request(Alloc* self, isize align, isize size, isize count);

    void
    alloc_release(Alloc* self, byte* pntr, isize size, isize count);
} // namespace gr

#endif // GR_CORE_ALLOC_HPP
