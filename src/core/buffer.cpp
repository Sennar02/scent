#include <string.h>

#include "buffer.hpp"

namespace gr
{
    Buffer
    buffer_init(byte* block, isize bytes)
    {
        gr_exec_expect(block != 0, "The pointer must exist");
        gr_exec_expect(bytes  > 0, "The size must be positive");

        Buffer self;

        self.head = block;

        if ( self.head != 0 ) {
            self.tail = self.head + bytes;
            self.curr = self.head;
        }

        return self;
    }

    Buffer
    buffer_write(Buffer* buffer, byte* data, isize bytes)
    {
        gr_exec_expect(buffer != 0, "The buffer must exist");

        auto& self  = *buffer;
        isize avail = self.tail - self.curr;

        if ( bytes <= avail ) {
            memcpy(self.curr, data, bytes);

            self.curr += bytes;
        }

        return self;
    }
} // namespace gr
