#ifndef GR_CORE_ARENA_HPP
#define GR_CORE_ARENA_HPP

#include "types.hpp"

namespace gr
{
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

    static const isize SIZE_ARENA_NODE  = gr_type_size(Arena_Node);
    static const isize ALIGN_ARENA_NODE = gr_type_align(Arena_Node);

    gr_cpl_assert(SIZE_ARENA_NODE  == 4 * SIZE_ISIZE, "Unexpected type size");
    gr_cpl_assert(ALIGN_ARENA_NODE == 1 * SIZE_ISIZE, "Unexpected type alignment");

    struct Arena {
        //
        //
        //
        Arena_Node* list;

        //
        //
        //
        f32 grow;
    };

    static const isize SIZE_ARENA  = gr_type_size(Arena);
    static const isize ALIGN_ARENA = gr_type_align(Arena);

    gr_cpl_assert(SIZE_ARENA  == 2 * SIZE_ISIZE, "Unexpected type size");
    gr_cpl_assert(ALIGN_ARENA == 1 * SIZE_ISIZE, "Unexpected type alignment");

    //
    //
    //
    byte*
    forw_align(byte* pntr, isize align);

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
} // namespace gr

#endif // GR_CORE_ARENA_HPP
