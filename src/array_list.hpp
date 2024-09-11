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
    private:
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
        Array_List(Alloc& alloc, u32 size = 0);

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
        u32
        head() const;

        /**
         *
         */
        u32
        tail() const;

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
        insert(u32 index, const Val& val = {});

        /**
         * Same as insert(0, val).
         */
        bool
        insert_head(const Val& val = {});

        /**
         * Same as insert(count(), val).
         */
        bool
        insert_tail(const Val& val = {});

        /**
         * Swapping insert.
         */
        bool
        push(u32 index, const Val& val = {});

        /**
         * Same as push(0, val).
         */
        bool
        push_head(const Val& val = {});

        /**
         * Same as push(count(), val).
         */
        bool
        push_tail(const Val& val = {});

        /**
         * Ordered remove.
         */
        bool
        remove(u32 index);

        /**
         * Same as remove(0);
         */
        bool
        remove_head();

        /**
         * Same as remove(tail());
         */
        bool
        remove_tail();

        /**
         * Swapping remove.
         */
        bool
        pull(u32 index);

        /**
         * Same as pull(0).
         */
        bool
        pull_head();

        /**
         * Same as pull(tail()).
         */
        bool
        pull_tail();

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
