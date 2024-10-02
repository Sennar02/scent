#include "memory.hpp"

namespace gr
{
    template <class Val>
    Val*
    arena_alloc_of(Arena* arena, isize count)
    {
        static const isize SIZE  = gr_type_size(Val);
        static const isize ALIGN = gr_type_align(Val);

        return (Val*) arena_alloc(arena,
            ALIGN, SIZE, count);
    }
} // namespace gr