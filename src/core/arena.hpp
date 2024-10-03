#ifndef GR_CORE_ARENA_HPP
#define GR_CORE_ARENA_HPP

#include "types.hpp"

namespace gr
{
    //
    //
    //
    byte*
    forw_align(byte* pntr, isize align);

    struct Arena_Node {
        //
        //
        //
        byte* head;

        //
        //
        //
        byte* tail;

        //
        //
        //
        byte* curr;

        //
        //
        //
        Arena_Node* next;
    };

    struct Arena {
        //
        //
        //
        Arena_Node* list;

        //
        //
        //
        byte* func;

        //
        //
        //
        f32 growth;
    };

    //
    //
    //
    using Arena_Error_Func = byte*
        (Arena* self, isize code, const byte* message);

    static const isize SIZE_ARENA_NODE = gr_type_size(Arena_Node);
    static const isize SIZE_ARENA      = gr_type_size(Arena);

    gr_cpl_assert(SIZE_ARENA_NODE == 4 * SIZE_ISIZE, "Unexpected type size");
    gr_cpl_assert(SIZE_ARENA      == 3 * SIZE_ISIZE, "Unexpected type size");

    static const isize ALIGN_ARENA_NODE = gr_type_align(Arena_Node);
    static const isize ALIGN_ARENA      = gr_type_align(Arena);

    gr_cpl_assert(ALIGN_ARENA_NODE == 1 * ALIGN_ISIZE, "Unexpected type alignment");
    gr_cpl_assert(ALIGN_ARENA      == 1 * ALIGN_ISIZE, "Unexpected type alignment");

    static const f32 ARENA_GROWTH_NONE = 0.0f;
    static const f32 ARENA_GROWTH_BASE = 2.0f;

    static const isize ARENA_ERROR_GROWTH_BY_ZERO = 1;
    static const isize ARENA_ERROR_NO_MORE_MEMORY = 2;

    static const isize ARENA_ERROR_COUNT =
        ARENA_ERROR_NO_MORE_MEMORY;

    byte*
    base_error_func(Arena* arena, isize error, const byte* descr);

    static const Arena_Error_Func* BASE_ERROR_FUNC =
        &base_error_func;

    //
    //
    //
    Arena_Node
    arena_node_init(byte* pntr, isize size);

    //
    //
    //
    void
    arena_node_drop(Arena_Node* self);

    //
    //
    //
    byte*
    arena_node_alloc(Arena_Node* self, isize aling, isize size, isize count);

    //
    //
    //
    void
    arena_node_reset(Arena_Node* self);

    //
    //
    //
    Arena
    arena_init(isize size, f32 grow);

    //
    //
    //
    void
    arena_drop(Arena* self);

    //
    //
    //
    byte*
    arena_alloc(Arena* self, isize align, isize size, isize count);

    //
    //
    //
    void
    arena_reset(Arena* self);

    //
    //
    //
    Arena_Error_Func*
    arena_set_error_func(Arena* self, Arena_Error_Func* func);
} // namespace gr

#endif // GR_CORE_ARENA_HPP
