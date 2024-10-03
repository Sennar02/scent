#include <malloc.h>
#include <string.h>
#include <stdio.h>

#include "arena.hpp"

namespace gr
{
    static const byte* ARENA_ERROR_ARRAY[] = {
        "GROWTH_BY_ZERO: The arena cannot grow because the next node would be empty",
        "NO_MORE_MEMORY: The arena cannot grow because the system has run out of memory",
    };

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
    base_error_func(Arena* arena, isize error, const byte* descr)
    {
        gr_run_assert(arena != 0, "The arena must exist");
        gr_run_assert(descr != 0, "The error description must exist");

        fprintf(stderr,
            "\x1b[31m[ERROR]\x1b[0m From arena 0x%llx error %lli, %s\n",
            (usize) arena, error, descr);

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

        // todo(trakot_02): detect overflow.
        if ( diff >= size * count + fill ) {
            self.curr = curr + size;
            pntr      = curr;

            memset(curr, 0, size);
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
    arena_attach(isize size)
    {
        // todo(trakot_02): find a prettier implementation.
        // todo(trakot_02): detect overflow.
        auto* node = (Arena_Node*) malloc(size + SIZE_ARENA_NODE);
        byte* pntr = (byte*) node + SIZE_ARENA_NODE;

        if ( node != 0 )
            *node = arena_node_init(pntr, size);

        return node;
    }

    void
    arena_detach(Arena_Node* node)
    {
        gr_run_assert(node != 0, "The node must exist");

        free(node);
    }

    byte*
    arena_error(Arena* arena, isize error)
    {
        gr_run_assert(arena != 0, "The arena must exist");

        auto& self = *arena;

        if ( self.func != 0 && error != 0 ) {
            const byte* descr = ARENA_ERROR_ARRAY[error - 1];

            return ((Arena_Error_Func*) self.func)
                (arena, error, descr);
        }

        return 0;
    }

    Arena
    arena_init(isize size, f32 growth)
    {
        Arena self = {0};
        byte* pntr = 0;

        gr_run_assert(size > 0, "The size must be positive");

        self.list = arena_attach(size);

        if ( self.list != 0 ) {
            self.growth = (growth >= 2.0f) * growth;
            self.func   = (byte*) BASE_ERROR_FUNC;
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

            arena_detach(temp);
        }

        self.list   = 0;
        self.growth = 0.0f;
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
            isize diff = node->tail - node->head;
            // todo(trakot_02): detect overflow.
            isize grow = (isize) (diff * self.growth);

            if ( node->next == 0 ) {
                if ( grow <= 0 )
                    return arena_error(arena, ARENA_ERROR_GROWTH_BY_ZERO);

                node->next = arena_attach(grow);

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
    arena_set_error_func(Arena* arena, Arena_Error_Func* func)
    {
        gr_run_assert(arena != 0, "The arena must exist");

        auto& self = *arena;
        auto* temp = self.func;

        self.func = (byte*) func;

        return (Arena_Error_Func*) temp;
    }
} // namespace gr
