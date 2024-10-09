#ifndef GR_CORE_ARENA_HPP
#define GR_CORE_ARENA_HPP

#include <core/types.hpp>
#include <core/alloc.hpp>
#include <core/array.hpp>
#include <core/str8.hpp>

namespace gr
{
    struct Arena_Node;
    struct Arena;

    enum Arena_Error {
        ARENA_ERROR_NONE           = 0,
        ARENA_ERROR_NO_MORE_MEMORY = 1,
        ARENA_ERROR_LIMITED_GROWTH = 2,

        ARENA_ERROR_COUNT = ARENA_ERROR_LIMITED_GROWTH,
    };

    static const Array<Str8> ARENA_ERROR_TITLE = (const Str8[]) {
        "ARENA_ERROR_NO_MORE_MEMORY",
        "ARENA_ERROR_LIMITED_GROWTH",
    };

    static const Array<Str8> ARENA_ERROR_DESCR = (const Str8[]) {
        "The allocators has run out of memory",
        "The arena's grow factor is too low to satisfy the request",
    };

    static const f32 ARENA_GROW_NONE = 0.0f;
    static const f32 ARENA_GROW_BASE = 2.0f;

    //
    //
    //
    using Arena_Error_Func = byte*
        (void* ctxt, Arena* arena, Arena_Error error);

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
        byte* (*error_func)
            (void* ctxt, Arena* arena, Arena_Error error) = 0;

        //
        //
        //
        byte* error_ctxt = 0;

        //
        //
        //
        Arena_Node* list = 0;

        //
        //
        //
        f32 grow_factor = 0;
    };

    static const isize WIDTH_ARENA = gr_type_width(Arena);
    static const isize ALIGN_ARENA = gr_type_align(Arena);

    //
    //
    //
    byte*
    forw_align(byte* pntr, isize align);

    //
    //
    //
    Arena_Node
    arena_node_from(byte* block, isize bytes);

    //
    //
    //
    byte*
    arena_node_alloc(Arena_Node* node, isize aling, isize width, isize items);

    //
    // todo(trakot02): Maybe specify where to reset?
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
    Arena_Error_Func*
    arena_set_error_func(Arena* arena, Arena_Error_Func* func);

    //
    //
    //
    void*
    arena_set_error_ctxt(Arena* arena, void* ctxt);

    //
    //
    //
    Alloc
    arena_set_allocator(Arena* arena, Alloc allocator);
} // namespace gr

#endif // GR_CORE_ARENA_HPP
