#ifndef GR_CORE_ARENA_HPP
#define GR_CORE_ARENA_HPP

#include "expect.hpp"
#include "types.hpp"
#include "alloc.hpp"

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
        Arena_Node* next = 0;
    };

    struct Arena {
        //
        //
        //
        Alloc allocator;

        //
        //
        //
        Arena_Node* list = 0;

        //
        //
        //
        f32 grow_factor = 0;

        //
        //
        //
        byte* error_func = 0;

        //
        //
        //
        byte* error_ctxt = 0;
    };

    //
    //
    //
    using Arena_Error_Func = byte*
        (void* ctxt, Arena* self, isize error);

    static const isize WIDTH_ARENA_NODE = gr_type_width(Arena_Node);
    static const isize WIDTH_ARENA      = gr_type_width(Arena);

    gr_expectc(WIDTH_ARENA_NODE == 4 * WIDTH_ISIZE,               "Unexpected type width");
    gr_expectc(WIDTH_ARENA      == 4 * WIDTH_ISIZE + WIDTH_ALLOC, "Unexpected type width");

    static const isize ALIGN_ARENA_NODE = gr_type_align(Arena_Node);
    static const isize ALIGN_ARENA      = gr_type_align(Arena);

    gr_expectc(ALIGN_ARENA_NODE == 1 * ALIGN_ISIZE, "Unexpected type alignment");
    gr_expectc(ALIGN_ARENA      == 1 * ALIGN_ISIZE, "Unexpected type alignment");

    static const f32 ARENA_GROW_NONE = 0.0f;

    static const isize ARENA_ERROR_NO_MORE_MEMORY = 1;
    static const isize ARENA_ERROR_UNABLE_TO_GROW = 2;

    static const isize ARENA_ERROR_COUNT =
        ARENA_ERROR_UNABLE_TO_GROW;

    static const byte* ARENA_ERROR_NAME[] = {
        "ARENA_ERROR_NO_MORE_MEMORY",
        "ARENA_ERROR_UNABLE_TO_GROW",
    };

    static const byte* ARENA_ERROR_TITLE[] = {
        "The system has run out of memory",
        "The request can't be satisfied because the arena's grow factor is too low",
    };

    byte*
    base_error_func(void* ctxt, Arena* arena, isize error);

    //
    //
    //
    Arena_Node
    arena_node_init(byte* block, isize bytes);

    //
    //
    //
    void
    arena_node_drop(Arena_Node* self);

    //
    //
    //
    byte*
    arena_node_alloc(Arena_Node* self, isize aling, isize width, isize items);

    //
    //
    //
    void
    arena_node_reset(Arena_Node* self);

    //
    //
    //
    Arena
    arena_init(isize width, isize items, f32 grow_factor);

    //
    //
    //
    void
    arena_drop(Arena* self);

    //
    //
    //
    byte*
    arena_alloc(Arena* self, isize align, isize width, isize items);

    //
    //
    //
    void
    arena_reset(Arena* self);

    //
    //
    //
    Arena_Error_Func*
    arena_set_error_func(Arena* self, void* ctxt, Arena_Error_Func* func);

    //
    //
    //
    Alloc
    arena_set_allocator(Arena* self, Alloc allocator);
} // namespace gr

#endif // GR_CORE_ARENA_HPP
