#ifndef GR_CORE_ALLOC_HPP
#define GR_CORE_ALLOC_HPP

#include <core/types.hpp>

namespace gr
{
    struct Alloc {
        //
        //
        //
        byte* (*request_func)
            (void* ctxt, isize align, isize width, isize items) = 0;

        //
        //
        //
        void (*release_func)
            (void* ctxt, byte* block, isize width, isize items) = 0;

        //
        //
        //
        byte* ctxt = 0;
    };

    static const isize WIDTH_ALLOC = gr_type_width(Alloc);
    static const isize ALIGN_ALLOC = gr_type_align(Alloc);

    //
    //
    //
    byte*
    alloc_request(Alloc* alloc, isize align, isize width, isize items);

    //
    //
    //
    void
    alloc_release(Alloc* alloc, byte* block, isize width, isize items);

    //
    //
    //
    Alloc
    base_alloc();
} // namespace gr

#endif // GR_CORE_ALLOC_HPP
