#ifndef GR_CORE_BUFFER_HPP
#define GR_CORE_BUFFER_HPP

#include "types.hpp"

namespace gr
{
    enum Buffer_State {
        BUFFER_STATE_BASE = 0,
        BUFFER_STATE_FULL = 1,

        BUFFER_STATE_COUNT = BUFFER_STATE_FULL,
    };

    enum Buffer_Error {
        BUFFER_ERROR_NONE     = 0,
        BUFFER_ERROR_OVERFLOW = 1,

        BUFFER_ERROR_COUNT = BUFFER_ERROR_OVERFLOW,
    };

    struct Buffer {
        //
        //
        //
        byte* head = 0;

        //
        //
        //
        byte* tail = 0;

        //
        //
        //
        byte* curr = 0;

        //
        //
        //
        isize state = 0;

        //
        //
        //
        isize error = 0;
    };

    static const isize WIDTH_BUFFER = gr_type_width(Buffer);
    static const isize ALIGN_BUFFER = gr_type_align(Buffer);

    //
    //
    //
    Buffer
    buffer_from(byte* data, isize bytes, isize state = BUFFER_STATE_BASE);

    //
    //
    //
    Buffer
    buffer_copy(Buffer* buffer, Buffer* other);

    //
    //
    //
    Buffer
    buffer_empty(Buffer* buffer, byte value);

    //
    //
    //
    Buffer
    buffer_fill(Buffer* buffer, byte value);
} // namespace gr

#endif // GR_CORE_BUFFER_HPP
