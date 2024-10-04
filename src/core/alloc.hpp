#ifndef GR_CORE_ALLOC_HPP
#define GR_CORE_ALLOC_HPP

#include "expect.hpp"
#include "types.hpp"

namespace gr
{
    //
    //
    //
    using Request_Func = byte*
        (void* ctxt, isize align, isize width, isize items);

    //
    //
    //
    using Release_Func = void
        (void* ctxt, byte* block, isize width, isize items);

    struct Alloc {
        //
        //
        //
        byte* request_func = 0;

        //
        //
        //
        byte* release_func = 0;

        //
        //
        //
        byte* alloc_ctxt = 0;
    };

    static const isize WIDTH_ALLOC = gr_type_width(Alloc);
    static const isize ALIGN_ALLOC = gr_type_align(Alloc);

    gr_expectc(WIDTH_ALLOC == 3 * WIDTH_ISIZE, "Unexpected type width");
    gr_expectc(ALIGN_ALLOC == 1 * ALIGN_ISIZE, "Unexpected type alignment");

    //
    //
    //
    byte*
    alloc_request(Alloc* self, isize align, isize width, isize items);

    //
    //
    //
    void
    alloc_release(Alloc* self, byte* block, isize width, isize items);

    //
    //
    //
    Alloc
    base_alloc_init();
} // namespace gr

#endif // GR_CORE_ALLOC_HPP
