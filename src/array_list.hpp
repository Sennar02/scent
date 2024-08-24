#ifndef SCENT_ARRAY_LIST_HPP
#define SCENT_ARRAY_LIST_HPP

#include "types.hpp"
#include "slice.hpp"
#include "alloc.hpp"
#include "item_ref.hpp"

namespace scent
{
    template <class Val>
    struct Array_List final
    {
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
        Val* _pntr = 0;

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
        Array_List();

        /**
         *
         */
        Array_List(Alloc& alloc, u32 size);

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
         * Ordered insert.
         */
        bool
        insert(u32 index, const Val& val);

        /**
         * Swapping insert.
         */
        bool
        push(u32 index, const Val& val);

        /**
         * Ordered remove.
         */
        bool
        remove(u32 index);

        /**
         * Swapping remove.
         */
        bool
        pull(u32 index);

        /**
         *
         */
        Item_Ref<const Val>
        operator[](u32 index) const;

        /**
         *
         */
        Item_Ref<Val>
        operator[](u32 index);
    };
} // scent

#include "array_list.inl"

#endif // SCENT_ARRAY_LIST_HPP
