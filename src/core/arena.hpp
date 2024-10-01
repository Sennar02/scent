#ifndef GR_CORE_ARENA_HPP
#define GR_CORE_ARENA_HPP

#include "types.hpp"

namespace gr
{
    struct Arena {
        byte*  head;
        byte*  tail;
        byte*  curr;
        Arena* next;
    };

    static const isize SIZE_ARENA = gr_type_size(Arena);
    static const isize ALIGN_ARENA = gr_type_align(Arena);

    Arena
    arena_init(isize size);

    void
    arena_drop(Arena* self);

    byte*
    arena_alloc(Arena* self, isize align, isize size, isize count);

    void
    arena_reset(Arena* self);
} // namespace gr

#endif // GR_CORE_ARENA_HPP
