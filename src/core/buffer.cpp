#include "buffer.hpp"

namespace gr
{
    Buffer
    buffer_from(byte* block, isize bytes, isize state)
    {
        gr_exec_expect(block != 0, "The pointer must exist");

        Buffer self;

        if ( bytes <= 0 ) return self;

        self.head = block;

        if ( self.head != 0 ) {
            self.tail = self.head + bytes;
            self.curr = self.head;

            if ( state & BUFFER_STATE_FULL )
                self.curr = self.tail;

            self.state = state;
            self.error = BUFFER_ERROR_NONE;
        }

        return self;
    }

    Buffer
    buffer_copy(Buffer* buffer, Buffer* other)
    {
        gr_exec_expect(buffer != 0, "The buffer must exist");
        gr_exec_expect(other  != 0, "The other buffer must exist");

        auto& self  = *buffer;
        isize avail = self.tail - self.curr;
        isize bytes = other->curr - other->head;

        if ( bytes <= avail ) {
            if ( bytes == avail )
                self.state |= BUFFER_STATE_FULL;

            for ( isize i = 0; i < bytes; i += 1 )
                self.curr[i] = other->head[i];

            self.curr += bytes;
        } else
            self.error |= BUFFER_ERROR_OVERFLOW;

        return self;
    }

    Buffer
    buffer_empty(Buffer* buffer, byte value)
    {
        gr_exec_expect(buffer != 0, "The buffer must exist");

        auto& self  = *buffer;
        isize bytes = self.curr - self.head;

        for ( isize i = 0; i < bytes; i += 1 )
            self.head[i] = value;

        self.curr   = self.head;
        self.state &= ~BUFFER_STATE_FULL;
        self.error  = BUFFER_ERROR_NONE;

        return self;
    }

    Buffer
    buffer_fill(Buffer* buffer, byte value)
    {
        gr_exec_expect(buffer != 0, "The buffer must exist");

        auto& self  = *buffer;
        isize bytes = self.tail - self.curr;

        for ( isize i = 0; i < bytes; i += 1 )
            self.curr[i] = value;

        self.curr   = self.tail;
        self.state |= BUFFER_STATE_FULL;
        self.error  = BUFFER_ERROR_NONE;

        return self;
    }
} // namespace gr
