#include <malloc.h>
#include <stdio.h>

#include <core/arena.hpp>
#include <core/buff.hpp>

namespace gr
{
    byte*
    base_error_func(void* ctxt, Arena* arena, Arena_Error error)
    {
        gr_exec_expect(ctxt  == 0, "The context must not exist");
        gr_exec_expect(arena != 0, "The arena must exist");

        auto& self = *arena;

        fprintf(stderr,
            "\x1b[31m[ERROR]\x1b[0m error %u, %s:\n"
            "\x1b[31m[ERROR]\x1b[0m     %s\n"
            "\x1b[31m[ERROR]\x1b[0m\n"
            "\x1b[31m[ERROR]\x1b[0m from arena 0x%lx:\n"
            "\x1b[31m[ERROR]\x1b[0m     grow_factor = %f\n",
            error,
            ARENA_ERROR_TITLE[error].data,
            ARENA_ERROR_DESCR[error].data,
            (usize) arena, self.grow_factor);

        return 0;
    }

    byte*
    arena_error(Arena* arena, Arena_Error error)
    {
        gr_exec_expect(arena != 0, "The arena must exist");

        auto& self = *arena;
        auto* func = self.error_func;

        if ( error != ARENA_ERROR_NONE && func != 0 )
            return (*func)(self.error_ctxt, arena, error);

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
    arena_node_from(byte* block, isize bytes)
    {
        gr_exec_expect(block != 0, "The block must exist");
        gr_exec_expect(bytes >= 0, "The bytes must be positive or zero");

        Arena_Node self;

        self.head = block;
        self.tail = block + bytes;
        self.curr = block;

        return self;
    }

    byte*
    arena_node_alloc(Arena_Node* node, isize align, isize width, isize items)
    {
        gr_exec_expect(node  != 0, "The node must exist");
        gr_exec_expect(align  > 0, "The alignment must be positive");
        gr_exec_expect(width  > 0, "The width must be positive");

        if ( items <= 0 ) return 0;

        auto& self = *node;
        byte* curr = forw_align(self.curr, align);
        byte* resl = 0;

        gr_exec_expect(align > 0 && (((usize) curr) & (align - 1)) == 0,
            "The result is not aligned properly");

        isize avail = self.tail - curr;
        isize extra = curr - self.curr;

        if ( items <= (avail - extra) / width ) {
            auto buff = buff_from(curr, 0, width * items);

            self.curr = curr + width * items;
            resl      = curr;

            buff_fill(&buff, 0);
        }

        return resl;
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
        gr_exec_expect(bytes >= 0, "The bytes must be positive or zero");

        auto& self = *arena;

        if ( bytes <= 0 ) return 0;

        if ( bytes <= MAX_ISIZE - WIDTH_ARENA_NODE ) {
            byte* block = alloc_request(&self.allocator,
                ALIGN_ARENA_NODE, bytes + WIDTH_ARENA_NODE, 1);

            auto* node = (Arena_Node*) block;
            auto* resl = block + WIDTH_ARENA_NODE;

            if ( node != 0 )
                *node = arena_node_from(resl, bytes);

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

    Arena
    arena_init(isize width, isize items, f32 grow_factor)
    {
        gr_exec_expect(width > 0, "The width must be positive");

        Arena self;

        self.allocator   = base_alloc();
        self.error_func  = &base_error_func;
        self.grow_factor = ARENA_GROW_BASE;

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
        self.error_func  = 0;
        self.error_ctxt  = 0;
        self.list        = 0;
        self.grow_factor = ARENA_GROW_BASE;
    }

    byte*
    arena_alloc(Arena* arena, isize align, isize width, isize items)
    {
        gr_exec_expect(arena != 0, "The arena must exist");
        gr_exec_expect(align  > 0, "The alignment must be positive");
        gr_exec_expect(width  > 0, "The width must be positive");

        auto& self = *arena;
        auto* node = self.list;

        byte* resl = arena_node_alloc(node, align, width, items);

        while ( resl == 0 ) {
            if ( self.grow_factor == ARENA_GROW_NONE )
                return arena_error(arena, ARENA_ERROR_LIMITED_GROWTH);

            isize bytes = node->tail - node->head;
            isize grown = 0;

            if ( bytes <= (isize) ((f32) MAX_ISIZE / self.grow_factor) )
                grown = (isize) (bytes * self.grow_factor);

            if ( node->next == 0 ) {
                if ( items > grown / width && grown <= bytes )
                    return arena_error(arena, ARENA_ERROR_LIMITED_GROWTH);

                node->next = arena_attach(arena, grown);

                if ( node->next == 0 )
                    return arena_error(arena, ARENA_ERROR_NO_MORE_MEMORY);
            }

            node = node->next;
            resl = arena_node_alloc(node, align, width, items);
        }

        return resl;
    }

    byte*
    arena_resize(Arena* arena, byte* block, isize align, isize width, isize items)
    {
        byte* resl = arena_alloc(arena, align, width, items);
        isize size = width * items;

        if ( resl != 0 && block != 0 ) {
            auto  bufd = buff_from(resl,     0, size);
            auto  bufs = buff_from(block, size, size);

            buff_copy(&bufd, &bufs);

            gr_exec_expect(bufd.error == BUFF_ERROR_NONE,
                "The operation must succeed");
        }

        return resl;
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

    Arena_Error_Func*
    arena_set_error_func(Arena* arena, Arena_Error_Func* func)
    {
        gr_exec_expect(arena != 0, "The arena must exist");

        auto& self = *arena;
        auto* temp = self.error_func;

        self.error_func = func;

        return temp;
    }

    void*
    arena_set_error_ctxt(Arena* arena, void* ctxt)
    {
        gr_exec_expect(arena != 0, "The arena must exist");

        auto& self = *arena;
        auto* temp = self.error_ctxt;

        self.error_ctxt = (byte*) ctxt;

        return ctxt;
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
