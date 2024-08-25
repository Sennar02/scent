#ifndef SCENT_ROBIN_MAP_HPP
#define SCENT_ROBIN_MAP_HPP

#include "types.hpp"
#include "slice.hpp"
#include "alloc.hpp"
#include "hash_ctx.hpp"
#include "pair_ref.hpp"

namespace scent
{
    template <class Key, class Val, class Ctx>
    struct Robin_Map final
    {
    private:
        struct Ctrl {
            /**
             *
             */
            u32 dist;

            /**
             *
             */
            u32 indx;
        };

    // TODO(gio): rendi privato.
    // private:
    public:
        /**
         *
         */
        Alloc* _alloc = 0;

        /**
         *
         */
        Ctrl* _ctrl = 0;

        /**
         *
         */
        u32* _indx = 0;

        /**
         *
         */
        Key* _head = 0;

        /**
         *
         */
        Val* _body = 0;

        /**
         *
         */
        u32 _size = 0;

        /**
         *
         */
        u32 _count = 0;

    public:
        /**
         *
         */
        Robin_Map();

        /**
         *
         */
        Robin_Map(Alloc& alloc, u32 size = 0);

        /**
         *
         */
        void
        init(Alloc& alloc, u32 size = 0);

        /**
         *
         */
        void
        drop();

        /**
         *
         */
        void
        reset();

        /**
         *
         */
        u32
        size() const;

        /**
         *
         */
        u32
        count() const;

        /**
         *
         */
        Slice<const Key>
        keys() const;

        /**
         *
         */
        Slice<const Val>
        values() const;

        /**
         *
         */
        Slice<Val>
        values();

        /**
         *
         */
        bool
        is_empty() const;

        /**
         *
         */
        bool
        isnt_empty() const;

        /**
         *
         */
        bool
        is_full() const;

        /**
         *
         */
        bool
        isnt_full() const;

        /**
         *
         */
        bool
        resize(u32 size);

        /**
         *
         */
        bool
        resize(Alloc& alloc, u32 size);

        /**
         *
         */
        void
        rehash();

        /**
         *
         */
        bool
        insert(const Key& key, const Val& val);

        /**
         *
         */
        bool
        remove(const Key& key);

        /**
         *
         */
        Pair_Ref<const Key, const Val>
        operator[](const Key& key) const;

        /**
         *
         */
        Pair_Ref<const Key, Val>
        operator[](const Key& key);
    };
} // scent

#include "robin_map.inl"

#endif // SCENT_ROBIN_MAP_HPP
