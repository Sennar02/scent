#include <malloc.h>
// todo(trakot02): remove.
#include <stdio.h>

#include "region.hpp"

namespace core
{
    struct Buffer_Node
        : public Buffer
    {
    public:
        Buffer_Node* next;
    };

    static const uarch SIZE_BUFFER_NODE = sizeof(Buffer_Node);

    Buffer_Node*
    buffer_node_init(uarch size)
    {
        i8*  pntr = (i8*) calloc(1, size + SIZE_BUFFER_NODE);
        auto node = (Buffer_Node*) pntr;

        if ( node != 0 )
            node->init(pntr + SIZE_BUFFER_NODE, size);

        return node;
    }

    void
    buffer_node_drop(Buffer_Node* node)
    {
        for ( auto n = node ; n != 0; n = n->next )
            free(n);
    }

    Region::Region() {}

    Region::Region(uarch size, f32 grow)
    {
        init(size, grow);
    }

    void
    Region::init(uarch size, f32 grow)
    {
        RUNTIME_ASSERT(_list == 0, "The arena was already initialized");

        _list = buffer_node_init(size);

        if ( _list != 0 )
            _grow = 1.0f + grow;
    }

    void
    Region::drop()
    {
        buffer_node_drop(_list);

        _list = 0;
        _grow = 0.0f;
    }

    i8*
    Region::require(uarch size, u8 align)
    {
        auto node = _list;
        i8*  pntr = node->require(size, align);

        // todo(trakot02): remove.
        printf("0x%lx, %lu\n", (uarch) node, node->size());

        while ( pntr == 0 ) {
            if ( node->next == 0 ) {
                node->next = buffer_node_init((uarch) (node->size() * _grow));

                if ( node->next == 0 )
                    return 0;
            }

            node = node->next;
            pntr = node->require(size, align);

            // todo(trakot02): remove.
            printf("0x%lx, %lu\n", (uarch) node, node->size());
        }

        return pntr;
    }

    void
    Region::reset()
    {
        for ( auto n = _list; n != 0; n = n->next)
            n->reset();
    }
} // namespace core
