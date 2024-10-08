#include <malloc.h>
#include <stdio.h>

#include "arena.hpp"
#include "buffer.hpp"

namespace gr
{
    byte*
    base_panic_func(void* ctxt, Arena* arena, Arena_Panic panic)
    {
        gr_exec_expect(arena != 0, "The arena must exist");
        gr_exec_expect(ctxt  == 0, "The context must not exist");

        f32 grow_factor = arena->grow_factor;

        fprintf(stderr,
            "\x1b[31m[PANIC]\x1b[0m panic %u, %s:\n"
            "\x1b[31m[PANIC]\x1b[0m     %s\n"
            "\x1b[31m[PANIC]\x1b[0m\n"
            "\x1b[31m[PANIC]\x1b[0m from arena 0x%lx:\n"
            "\x1b[31m[PANIC]\x1b[0m     grow_factor = %f\n",
            panic,
            ARENA_PANIC_TITLE[panic],
            ARENA_PANIC_DESCR[panic],
            (usize) arena, grow_factor);

        return 0;
    }

    byte*
    forw_align(byte* pntr, isize align)
    {
        gr_exec_expect(align > 0 && (align & (align - 1)) == 0,
            "The alignment must be a power of two");

        usize value = (usize) pntr;
        usize negat = ~value + 1;

        align = align - 1;

        return pntr + (negat & align);
    }

    Arena_Node
    arena_node_init(byte* block, isize bytes)
    {
        Arena_Node self;

        if ( bytes <= 0 ) return self;

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
        gr_exec_expect(node != 0, "The node must exist");

        auto& self = *node;

        self.head = 0;
        self.tail = 0;
        self.curr = 0;
        self.next = 0;
    }

    byte*
    arena_node_alloc(Arena_Node* node, isize align, isize width, isize items)
    {
        gr_exec_expect(node  != 0, "The node must exist");
        gr_exec_expect(align  > 0, "The alignment must be positive");
        gr_exec_expect(width  > 0, "The width must be positive");

        auto& self = *node;

        byte* pntr = 0;
        byte* curr = forw_align(self.curr, align);

        gr_exec_expect(align > 0 && (((usize) curr) & (align - 1)) == 0,
            "The result is not aligned properly");

        isize avail = self.tail - curr;
        isize extra = curr - self.curr;

        if ( items <= (avail - extra) / width ) {
            auto buff = buffer_from(curr, width * items);

            self.curr = curr + width * items;
            pntr      = curr;

            buffer_fill(&buff, 0);
        }

        return pntr;
    }

    void
    arena_node_reset(Arena_Node* node)
    {
        gr_exec_expect(node != 0, "The node must exist");

        auto& self = *node;

        self.curr = self.head;
    }

    Arena_Node*
    arena_attach(Arena* arena, isize bytes)
    {
        gr_exec_expect(arena != 0, "The arena must exist");

        auto& self = *arena;

        if ( bytes <= 0 ) return 0;

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
        gr_exec_expect(arena != 0, "The arena must exist");
        gr_exec_expect(node  != 0, "The node must exist");

        auto& self  = *arena;
        isize bytes = (isize) (node->tail - node->head);

        alloc_release(&self.allocator,
            (byte*) node, bytes + WIDTH_ARENA_NODE, 1);
    }

    byte*
    arena_panic(Arena* arena, Arena_Panic panic)
    {
        gr_exec_expect(arena != 0, "The arena must exist");

        auto& self = *arena;
        auto* func = (Arena_Panic_Func*) self.panic_func;

        if ( self.panic_func != 0 && panic != ARENA_PANIC_NONE )
            return (*func)(self.panic_ctxt, arena, panic);

        return 0;
    }

    Arena
    arena_init(isize width, isize items, f32 grow_factor)
    {
        gr_exec_expect(width > 0, "The width must be positive");

        Arena self;
        byte* pntr = 0;

        self.allocator   = base_alloc_init();
        self.grow_factor = ARENA_GROW_BASE;
        self.panic_func  = (byte*) &base_panic_func;

        if ( items <= MAX_ISIZE / width ) {
            self.list = arena_attach(&self, width * items);

            if ( self.list != 0 && grow_factor >= ARENA_GROW_BASE )
                self.grow_factor = grow_factor;
        }

        return self;
    }

    void
    arena_drop(Arena* arena)
    {
        gr_exec_expect(arena != 0, "The arena must exist");

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
        self.grow_factor = ARENA_GROW_BASE;
        self.panic_func  = 0;
        self.panic_ctxt  = 0;
    }

    byte*
    arena_alloc(Arena* arena, isize align, isize width, isize items)
    {
        gr_exec_expect(arena != 0, "The arena must exist");
        gr_exec_expect(align  > 0, "The alignment must be positive");
        gr_exec_expect(width  > 0, "The width must be positive");

        auto& self = *arena;
        auto* node = self.list;

        byte* pntr = arena_node_alloc(node, align, width, items);

        while ( pntr == 0 ) {
            if ( self.grow_factor == ARENA_GROW_NONE )
                return arena_panic(arena, ARENA_PANIC_LIMITED_GROWTH);

            isize bytes = node->tail - node->head;
            isize grown = 0;

            if ( bytes <= (isize) ((f32) MAX_ISIZE / self.grow_factor) )
                grown = (isize) (bytes * self.grow_factor);

            if ( node->next == 0 ) {
                if ( items > grown / width && grown <= bytes )
                    return arena_panic(arena, ARENA_PANIC_LIMITED_GROWTH);

                node->next = arena_attach(arena, grown);

                if ( node->next == 0 )
                    return arena_panic(arena, ARENA_PANIC_NO_MORE_MEMORY);
            }

            node = node->next;
            pntr = arena_node_alloc(node, align, width, items);
        }

        return pntr;
    }

    byte*
    arena_resize(Arena* arena, byte* block, isize align, isize width, isize items)
    {
        byte* pntr = arena_alloc(arena, align, width, items);

        if ( pntr != 0 && block != 0 ) {
            auto bufd = buffer_from(pntr,  width * items);
            auto bufs = buffer_from(block, width * items,
                BUFFER_STATE_FULL);

            buffer_copy(&bufd, &bufs);

            gr_exec_expect(bufd.error == BUFFER_ERROR_NONE,
                "The operation must succeed");
        }

        return pntr;
    }

    void
    arena_reset(Arena* arena)
    {
        gr_exec_expect(arena != 0, "The arena must exist");

        auto& self = *arena;
        auto* node = self.list;
        auto* temp = node;

        while ( node != 0 ) {
            temp = node;
            node = node->next;

            arena_node_reset(temp);
        }
    }

    Arena_Panic_Func*
    arena_set_panic_func(Arena* arena, void* ctxt, Arena_Panic_Func* func)
    {
        gr_exec_expect(arena != 0, "The arena must exist");

        auto& self = *arena;
        auto* temp = self.panic_func;

        self.panic_func = (byte*) func;
        self.panic_ctxt = (byte*) ctxt;

        return (Arena_Panic_Func*) temp;
    }

    Alloc
    arena_set_allocator(Arena* arena, Alloc allocator)
    {
        gr_exec_expect(arena != 0, "The arena must exist");

        auto& self = *arena;
        auto  temp = self.allocator;

        self.allocator = allocator;

        return temp;
    }
} // namespace gr
