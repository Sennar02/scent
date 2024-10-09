#ifndef GR_CORE_BUFF_HPP
#define GR_CORE_BUFF_HPP

#include <core/types.hpp>

namespace gr
{
    enum Buff_Error {
        BUFF_ERROR_NONE     = 0,
        BUFF_ERROR_OVERFLOW = 1,

        BUFF_ERROR_COUNT = BUFF_ERROR_OVERFLOW,
    };

    struct Buff {
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
        isize error = BUFF_ERROR_NONE;
    };

    static const isize WIDTH_BUFF = gr_type_width(Buff);
    static const isize ALIGN_BUFF = gr_type_align(Buff);

    //
    //
    //
    Buff
    buff_from(byte* data, isize bytes, isize limit);

    //
    //
    //
    Buff
    buff_copy(Buff* buff, Buff* other);

    //
    //
    //
    Buff
    buff_empty(Buff* buff);

    //
    //
    //
    Buff
    buff_fill(Buff* buff, byte value);
} // namespace gr

#endif // GR_CORE_BUFF_HPP
