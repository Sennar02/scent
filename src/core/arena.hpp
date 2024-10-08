#ifndef GR_CORE_ARENA_HPP
#define GR_CORE_ARENA_HPP

#include "types.hpp"
#include "array.hpp"
#include "alloc.hpp"

namespace gr
{
    enum Arena_Panic {
        ARENA_PANIC_NONE           = 0,
        ARENA_PANIC_NO_MORE_MEMORY = 1,
        ARENA_PANIC_LIMITED_GROWTH = 2,

        ARENA_PANIC_COUNT = ARENA_PANIC_LIMITED_GROWTH,
    };

    static const Array<const byte*, ARENA_PANIC_COUNT> ARENA_PANIC_TITLE = {
        "ARENA_PANIC_NO_MORE_MEMORY",
        "ARENA_PANIC_LIMITED_GROWTH",
    };

    static const Array<const byte*, ARENA_PANIC_COUNT> ARENA_PANIC_DESCR = {
        "The allocators has run out of memory",
        "The arena's grow factor is too low to satisfy the request",
    };

    static const f32 ARENA_GROW_NONE = 0.0f;
    static const f32 ARENA_GROW_BASE = 2.0f;

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

    static const isize WIDTH_ARENA_NODE = gr_type_width(Arena_Node);
    static const isize ALIGN_ARENA_NODE = gr_type_align(Arena_Node);

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
        byte* panic_func = 0;

        //
        //
        //
        byte* panic_ctxt = 0;
    };

    static const isize WIDTH_ARENA = gr_type_width(Arena);
    static const isize ALIGN_ARENA = gr_type_align(Arena);

    //
    //
    //
    using Arena_Panic_Func = byte*
        (void* ctxt, Arena* arena, Arena_Panic panic);

    //
    //
    //
    byte*
    forw_align(byte* pntr, isize align);

    //
    //
    //
    Arena_Node
    arena_node_init(byte* block, isize bytes);

    //
    //
    //
    void
    arena_node_drop(Arena_Node* node);

    //
    //
    //
    byte*
    arena_node_alloc(Arena_Node* node, isize aling, isize width, isize items);

    //
    //
    //
    void
    arena_node_reset(Arena_Node* node);

    //
    //
    //
    Arena
    arena_init(isize width, isize items, f32 grow_factor = ARENA_GROW_BASE);

    //
    //
    //
    void
    arena_drop(Arena* arena);

    //
    //
    //
    byte*
    arena_alloc(Arena* arena, isize align, isize width, isize items);

    //
    //
    //
    byte*
    arena_resize(Arena* arena, byte* block, isize align, isize width, isize items);

    //
    //
    //
    void
    arena_reset(Arena* arena);

    //
    //
    //
    Arena_Panic_Func*
    arena_set_panic_func(Arena* arena, void* ctxt, Arena_Panic_Func* func);

    //
    //
    //
    Alloc
    arena_set_allocator(Arena* arena, Alloc allocator);
} // namespace gr

#endif // GR_CORE_ARENA_HPP
