#ifndef GR_CORE_BUFFER_HPP
#define GR_CORE_BUFFER_HPP

#include "types.hpp"

namespace gr
{
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
    };

    //
    //
    //
    Buffer
    buffer_init(byte* data, isize bytes);

    //
    //
    //
    Buffer
    buffer_write(Buffer* buffer, byte* data, isize bytes);
} // namespace gr

#endif // GR_CORE_BUFFER_HPP
