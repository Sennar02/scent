#include <core/buff.hpp>

namespace gr
{
    Buff
    buff_from(byte* block, isize bytes, isize limit)
    {
        gr_exec_expect(0 <= bytes && bytes <= limit,
            "The bytes must be in range");

        gr_exec_expect(block != 0, "The pointer must exist");

        Buff self;

        self.head = block;

        if ( self.head != 0 ) {
            self.tail = self.head + limit;
            self.curr = self.head + bytes;
        }

        return self;
    }

    Buff
    buff_copy(Buff* buff, Buff* other)
    {
        gr_exec_expect(buff  != 0, "The buffer must exist");
        gr_exec_expect(other != 0, "The other buffer must exist");

        auto& self  = *buff;
        isize avail = self.tail - self.curr;
        isize bytes = other->curr - other->head;

        if ( bytes <= avail ) {
            for ( isize i = 0; i < bytes; i += 1 )
                self.curr[i] = other->head[i];

            self.curr += bytes;
        } else
            self.error |= BUFF_ERROR_OVERFLOW;

        return self;
    }

    Buff
    buff_empty(Buff* buff)
    {
        gr_exec_expect(buff != 0, "The buffer must exist");

        auto& self = *buff;

        self.curr  = self.head;
        self.error = BUFF_ERROR_NONE;

        return self;
    }

    Buff
    buff_fill(Buff* buff, byte value)
    {
        gr_exec_expect(buff != 0, "The buffer must exist");

        auto& self  = *buff;
        isize bytes = self.tail - self.curr;

        for ( isize i = 0; i < bytes; i += 1 )
            self.curr[i] = value;

        self.curr  = self.tail;
        self.error = BUFF_ERROR_NONE;

        return self;
    }
} // namespace gr
