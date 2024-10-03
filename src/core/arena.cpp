#include <malloc.h>
#include <string.h>
#include <stdio.h>

#include "arena.hpp"

namespace gr
{
    byte*
    forw_align(byte* pntr, isize align)
    {
        gr_run_assert(align != 0 && (align & (align - 1)) == 0,
            "The alignment must be a power of two");

        usize value = (usize) pntr;
        usize negat = ~value + 1;

        align = align - 1;

        return pntr + (negat & align);
    }

    byte*
    base_error_func(void* ctxt, Arena* arena, isize error)
    {
        gr_run_assert(arena != 0, "The arena must exist");
        gr_run_assert(ctxt  == 0, "The context must not exist");

        f32   grow_factor = arena->grow_factor;

        fprintf(stderr,
            "\x1b[31m[ERROR]\x1b[0m from arena 0x%llx error %lli, %s:\n"
            "\x1b[31m[ERROR]\x1b[0m     %s\n"
            "\x1b[31m[ERROR]\x1b[0m\n"
            "\x1b[31m[ERROR]\x1b[0m grow_factor = %f\n",
            (usize) arena, error, ARENA_ERROR_NAME[error],
            ARENA_ERROR_TITLE[error], grow_factor);

        return 0;
    }

    Arena_Node
    arena_node_init(byte* pntr, isize size)
    {
        gr_run_assert(pntr != 0, "The pointer must exist");
        gr_run_assert(size  > 0, "The size must be positive");

        Arena_Node self = {0};

        self.head = pntr;
        self.next = 0;

        if ( self.head != 0 ) {
            self.tail = self.head + size;
            self.curr = self.head;
        }

        return self;
    }

    void
    arena_node_drop(Arena_Node* node)
    {
        gr_run_assert(node != 0, "The node must exist");

        auto& self = *node;

        self.head = 0;
        self.tail = 0;
        self.curr = 0;
        self.next = 0;
    }

    isize
    arena_node_size(Arena_Node* node)
    {
        gr_run_assert(node != 0, "The node must exist");

        auto& self = *node;

        return (isize) (self.tail - self.head);
    }

    byte*
    arena_node_alloc(Arena_Node* node, isize align, isize size, isize count)
    {
        gr_run_assert(node  != 0, "The node must exist");
        gr_run_assert(align  > 0, "The alignment must be positive");
        gr_run_assert(size   > 0, "The size must be positive");

        auto& self = *node;

        byte* pntr = 0;
        byte* curr = forw_align(self.curr, align);

        gr_run_assert(align != 0 && ((usize) curr & (align - 1)) == 0,
            "The result is not aligned properly");

        isize diff = self.tail - self.head;
        isize fill = curr - self.curr;

        if ( count <= (diff - fill) / size ) {
            self.curr = curr + size * count;
            pntr      = curr;

            memset(curr, 0, size * count);
        }

        return pntr;
    }

    void
    arena_node_reset(Arena_Node* node)
    {
        gr_run_assert(node != 0, "The node must exist");

        auto& self = *node;

        self.curr = self.head;
    }

    Arena_Node*
    arena_attach(Arena* arena, isize size)
    {
        gr_run_assert(arena != 0, "The arena must exist");

        auto& self = *arena;

        if ( size <= MAX_ISIZE - SIZE_ARENA_NODE ) {
            byte* temp = alloc_request(&self.allocator,
                ALIGN_ARENA_NODE, size + SIZE_ARENA_NODE, 1);

            auto* node = (Arena_Node*)temp;
            auto* pntr = temp + SIZE_ARENA_NODE;

            if ( node != 0 )
                *node = arena_node_init(pntr, size);

            return node;
        }

        return 0;
    }

    void
    arena_detach(Arena* arena, Arena_Node* node)
    {
        gr_run_assert(arena != 0, "The arena must exist");
        gr_run_assert(node  != 0, "The node must exist");

        auto& self = *arena;
        isize size = (isize) (node->tail - node->head);

        alloc_release(&self.allocator,
            (byte*) node, size + SIZE_ARENA_NODE, 1);
    }

    byte*
    arena_error(Arena* arena, isize error)
    {
        gr_run_assert(arena != 0, "The arena must exist");

        auto& self = *arena;
        auto* func = (Arena_Error_Func*) self.error_func;

        if ( self.error_func != 0 && error != 0 )
            return (*func)(self.error_ctxt, arena, error - 1);

        return 0;
    }

    Arena
    arena_init(isize size, isize count, f32 grow_factor)
    {
        Arena self = {0};
        byte* pntr = 0;

        gr_run_assert(grow_factor >= 0.0f,
            "The grow factor must be positive or zero");

        gr_run_assert(size > 0, "The size must be positive");

        self.allocator  = base_alloc_init();
        self.error_func = (byte*) &base_error_func;
        self.error_ctxt = 0;

        if ( count <= MAX_ISIZE / size ) {
            self.list = arena_attach(&self, size * count);

            if ( self.list != 0 )
                self.grow_factor = grow_factor;
        }

        return self;
    }

    void
    arena_drop(Arena* arena)
    {
        gr_run_assert(arena != 0, "The arena must exist");

        auto& self = *arena;
        auto* node = self.list;
        auto* temp = node;

        while ( node != 0 ) {
            temp = node;
            node = node->next;

            arena_detach(arena, temp);
        }

        self.list        = 0;
        self.grow_factor = 0.0f;
    }

    byte*
    arena_alloc(Arena* arena, isize align, isize size, isize count)
    {
        gr_run_assert(arena != 0, "The arena must exist");
        gr_run_assert(align  > 0, "The alignment must be positive");
        gr_run_assert(size   > 0, "The size must be positive");

        auto& self = *arena;
        auto* node = self.list;

        byte* pntr = arena_node_alloc(node, align, size, count);

        while ( pntr == 0 ) {
            if ( self.grow_factor == ARENA_GROW_NONE )
                return arena_error(arena, ARENA_ERROR_UNABLE_TO_GROW);

            isize diff = node->tail - node->head;
            isize grow = 0;

            if ( diff <= (isize) (MAX_ISIZE / self.grow_factor) )
                grow = (isize) (diff * self.grow_factor);

            if ( node->next == 0 ) {
                if ( count > grow / size && grow <= diff )
                    return arena_error(arena, ARENA_ERROR_UNABLE_TO_GROW);

                node->next = arena_attach(arena, grow);

                if ( node->next == 0 )
                    return arena_error(arena, ARENA_ERROR_NO_MORE_MEMORY);
            }

            node = node->next;
            pntr = arena_node_alloc(node, align, size, count);
        }

        return pntr;
    }

    void
    arena_reset(Arena* arena)
    {
        gr_run_assert(arena != 0, "The arena must exist");

        auto& self = *arena;
        auto* node = self.list;
        auto* temp = node;

        while ( node != 0 ) {
            temp = node;
            node = node->next;

            arena_node_reset(temp);
        }
    }

    Arena_Error_Func*
    arena_set_error_func(Arena* arena, void* ctxt, Arena_Error_Func* func)
    {
        gr_run_assert(arena != 0, "The arena must exist");

        auto& self = *arena;
        auto* temp = self.error_func;

        self.error_func = (byte*) func;
        self.error_ctxt = (byte*) ctxt;

        return (Arena_Error_Func*) temp;
    }

    Alloc
    arena_set_allocator(Arena* arena, Alloc allocator)
    {
        gr_run_assert(arena != 0, "The arena must exist");

        auto& self = *arena;
        auto  temp = self.allocator;

        self.allocator = allocator;

        return temp;
    }
} // namespace gr
