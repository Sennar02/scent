#ifndef SCENT_ARRAY_MAP_HPP
#define SCENT_ARRAY_MAP_HPP

#include "types.hpp"
#include "utils.hpp"
#include "slice.hpp"
#include "alloc.hpp"
#include "hash.hpp"
#include "pair_ref.hpp"

namespace scent
{
    template <class Key, class Val, class Hash>
    struct Array_Map final
    {
    public:
        /**
         *
         */
        Alloc* _alloc = 0;

        /**
         *
         */
        u32* _indx = 0;

        /**
         *
         */
        u32* _hash = 0;

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
        Array_Map();

        /**
         *
         */
        Array_Map(Alloc& alloc, u32 size);

        /**
         *
         */
        void
        init(Alloc& alloc, u32 size);

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
        insert(const Key& key, const Val& val);

        /**
         *
         */
        bool
        update(const Key& key, const Val& val);

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

#include "array_map.inl"

#endif // SCENT_ARRAY_MAP_HPP
