#ifndef SCENT_HASH_MAP_HPP
#define SCENT_HASH_MAP_HPP

#include "types.hpp"
#include "utils.hpp"
#include "alloc.hpp"
#include "hash.hpp"
#include "pair_ref.hpp"

namespace scent
{
    template <class Key, class Val, class Hash>
    struct Hash_Map final
    {
    private:
        struct Ctrl {
            /**
             *
             */
            Key key;

            /**
             *
             */
            u32 dist;

            /**
             *
             */
            u32 hash;
        };

        struct Body {
            /**
             *
             */
            Val val;
        };

        /**
         *
         */
        Ctrl* _ctrl = 0;

        /**
         *
         */
        Body* _body = 0;

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
        Hash_Map();

        /**
         *
         */
        Hash_Map(Alloc& alloc, u32 size);

        /**
         *
         */
        void
        drop(Alloc& alloc);

        /**
         *
         */
        void
        clear();

        /**
         *
         */
        u32
        size() const;

        /**
         *
         */
        u32
        values() const;

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
        Pair_Ref<const Key, const Val>
        find(const Key& key) const;

        /**
         *
         */
        Pair_Ref<const Key, Val>
        find(const Key& key);

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
    };
} // scent

#include "hash_map.inl"

#endif // SCENT_HASH_MAP_HPP
