#ifndef SCENT_ARR_LIST_HPP
#define SCENT_ARR_LIST_HPP

#include "types.hpp"
#include "alloc.hpp"
#include "item_ref.hpp"

namespace scent
{
    template <class Val>
    struct Arr_List final
    {
    private:
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
        Arr_List();

        /**
         *
         */
        Arr_List(Alloc& alloc, u32 size);

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
        Item_Ref<const Val>
        find(u32 index) const;

        /**
         *
         */
        Item_Ref<Val>
        find(u32 index);

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
    };
} // scent

#include "arr_list.inl"

#endif // SCENT_ARR_LIST_HPP
