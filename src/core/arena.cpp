#include <malloc.h>
#include <string.h>

#include "arena.hpp"

namespace core
{
    static const u32 SIZE_BLOCK = sizeof(Block);

    Arena::Arena() {}

    Arena::Arena(u32 size)
    {
        init(size);
    }

    void
    Arena::init(u32 size)
    {
        RUNTIME_ASSERT(_head == 0, "The region has already been initialized");

        i8* pntr = (i8*) malloc(size + SIZE_BLOCK);

        if ( pntr != 0 ) {
            _head = (Block*) pntr;

            memset(pntr, 0, size + SIZE_BLOCK);

            _head->base = pntr + SIZE_BLOCK;
            _head->curs = pntr + SIZE_BLOCK;
            _head->size = size;
        }
    }

    void
    Arena::drop()
    {
        // todo(trakot_02): implement.
    }

    i8*
    Arena::alloc(u32 size, u8 align)
    {
        RUNTIME_ASSERT(_head != 0, "The arena does not exist");

        auto node = _head;
        i8*  curs = align_forw(node->curs, align);

        while ( curs + size > node->base + node->size ) {
            if ( node->next == 0 ) {
                i8* pntr = malloc(node->size * 2 + SIZE_BLOCK);

                memset(pntr, 0, node->size * 2 + SIZE_BLOCK);

                node->next = (Block*) pntr;

                node = node->next;
            }
        }




/*
        auto node = this;
        // todo(trakot_02): apply alignment.
        i8*  curs = _curs;
        i8*  pntr = 0;

        while ( curs + size > node->_tail ) {
            if ( node->_next == 0 ) {
                u32  diff = node->_tail - node->_head;
                auto next = new Arena(diff * 2u);

                node->_next = next;
            }

            node = node->_next;
            // todo(trakot_02): apply alignment.
            curs = node->_curs;
        }

        node->_curs = curs + size;
        pntr        = curs;

        memset(pntr, 0, size);

        return pntr;
        */
    }

    void
    Arena::reset()
    {
        // todo(trakot_02): implement.
    }
} // namespace core
