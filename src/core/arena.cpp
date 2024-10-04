#include <malloc.h>
#include <string.h>
#include <stdio.h>

#include "arena.hpp"

namespace gr
{
    byte*
    forw_align(byte* pntr, isize align)
    {
        gr_expect(align != 0 && (align & (align - 1)) == 0,
            "The alignment must be a power of two");

        usize value = (usize) pntr;
        usize negat = ~value + 1;

        align = align - 1;

        return pntr + (negat & align);
    }

    byte*
    base_error_func(void* ctxt, Arena* arena, isize error)
    {
        gr_expect(arena != 0, "The arena must exist");
        gr_expect(ctxt  == 0, "The context must not exist");

        f32 grow_factor = arena->grow_factor;

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
    arena_node_init(byte* block, isize bytes)
    {
        gr_expect(block != 0, "The pointer must exist");
        gr_expect(bytes  > 0, "The size must be positive");

        Arena_Node self;

        self.head = block;

        if ( self.head != 0 ) {
            self.tail = self.head + bytes;
            self.curr = self.head;
        }

        return self;
    }

    void
    arena_node_drop(Arena_Node* node)
    {
        gr_expect(node != 0, "The node must exist");

        auto& self = *node;

        self.head = 0;
        self.tail = 0;
        self.curr = 0;
        self.next = 0;
    }

    byte*
    arena_node_alloc(Arena_Node* node, isize align, isize width, isize items)
    {
        gr_expect(node  != 0, "The node must exist");
        gr_expect(align  > 0, "The alignment must be positive");
        gr_expect(width  > 0, "The width must be positive");

        auto& self = *node;

        byte* pntr = 0;
        byte* curr = forw_align(self.curr, align);

        gr_expect(align != 0 && ((usize) curr & (align - 1)) == 0,
            "The result is not aligned properly");

        isize avail = self.tail - self.head;
        isize extra = curr - self.curr;

        if ( items <= (avail - extra) / width ) {
            self.curr = curr + width * items;
            pntr      = curr;

            memset(curr, 0, width * items);
        }

        return pntr;
    }

    void
    arena_node_reset(Arena_Node* node)
    {
        gr_expect(node != 0, "The node must exist");

        auto& self = *node;

        self.curr = self.head;
    }

    Arena_Node*
    arena_attach(Arena* arena, isize bytes)
    {
        gr_expect(arena != 0, "The arena must exist");
        gr_expect(bytes  > 0, "The size must be positive");

        auto& self = *arena;

        if ( bytes <= MAX_ISIZE - WIDTH_ARENA_NODE ) {
            byte* pntr = alloc_request(&self.allocator,
                ALIGN_ARENA_NODE, bytes + WIDTH_ARENA_NODE, 1);

            auto* node  = (Arena_Node*) pntr;
            auto* block = pntr + WIDTH_ARENA_NODE;

            if ( node != 0 )
                *node = arena_node_init(block, bytes);

            return node;
        }

        return 0;
    }

    void
    arena_detach(Arena* arena, Arena_Node* node)
    {
        gr_expect(arena != 0, "The arena must exist");
        gr_expect(node  != 0, "The node must exist");

        auto& self  = *arena;
        isize bytes = (isize) (node->tail - node->head);

        alloc_release(&self.allocator,
            (byte*) node, bytes + WIDTH_ARENA_NODE, 1);
    }

    byte*
    arena_error(Arena* arena, isize error)
    {
        gr_expect(arena != 0, "The arena must exist");

        auto& self = *arena;
        auto* func = (Arena_Error_Func*) self.error_func;

        if ( self.error_func != 0 && error != 0 )
            return (*func)(self.error_ctxt, arena, error - 1);

        return 0;
    }

    Arena
    arena_init(isize width, isize items, f32 grow_factor)
    {
        Arena self;
        byte* pntr = 0;

        gr_expect(grow_factor >= 0.0f,
            "The grow factor must be positive or zero");

        gr_expect(width > 0, "The width must be positive");

        self.allocator  = base_alloc_init();
        self.error_func = (byte*) &base_error_func;

        if ( items <= MAX_ISIZE / width ) {
            self.list = arena_attach(&self, width * items);

            if ( self.list != 0 )
                self.grow_factor = grow_factor;
        }

        return self;
    }

    void
    arena_drop(Arena* arena)
    {
        gr_expect(arena != 0, "The arena must exist");

        auto& self = *arena;
        auto* node = self.list;
        auto* temp = node;

        while ( node != 0 ) {
            temp = node;
            node = node->next;

            arena_detach(arena, temp);
        }

        self.allocator   = {};
        self.list        = 0;
        self.grow_factor = 0.0f;
        self.error_func  = 0;
        self.error_ctxt  = 0;
    }

    byte*
    arena_alloc(Arena* arena, isize align, isize width, isize items)
    {
        gr_expect(arena != 0, "The arena must exist");
        gr_expect(align  > 0, "The alignment must be positive");
        gr_expect(width  > 0, "The width must be positive");

        auto& self = *arena;
        auto* node = self.list;

        byte* pntr = arena_node_alloc(node, align, width, items);

        while ( pntr == 0 ) {
            if ( self.grow_factor == ARENA_GROW_NONE )
                return arena_error(arena, ARENA_ERROR_UNABLE_TO_GROW);

            isize bytes = node->tail - node->head;
            isize grown = 0;

            if ( bytes <= (isize) (MAX_ISIZE / self.grow_factor) )
                grown = (isize) (bytes * self.grow_factor);

            if ( node->next == 0 ) {
                if ( items > grown / width && grown <= bytes )
                    return arena_error(arena, ARENA_ERROR_UNABLE_TO_GROW);

                node->next = arena_attach(arena, grown);

                if ( node->next == 0 )
                    return arena_error(arena, ARENA_ERROR_NO_MORE_MEMORY);
            }

            node = node->next;
            pntr = arena_node_alloc(node, align, width, items);
        }

        return pntr;
    }

    void
    arena_reset(Arena* arena)
    {
        gr_expect(arena != 0, "The arena must exist");

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
        gr_expect(arena != 0, "The arena must exist");

        auto& self = *arena;
        auto* temp = self.error_func;

        self.error_func = (byte*) func;
        self.error_ctxt = (byte*) ctxt;

        return (Arena_Error_Func*) temp;
    }

    Alloc
    arena_set_allocator(Arena* arena, Alloc allocator)
    {
        gr_expect(arena != 0, "The arena must exist");

        auto& self = *arena;
        auto  temp = self.allocator;

        self.allocator = allocator;

        return temp;
    }
} // namespace gr
