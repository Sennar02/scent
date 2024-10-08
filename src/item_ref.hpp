#ifndef SCENT_ITEM_REF_HPP
#define SCENT_ITEM_REF_HPP

#include <assert.h>

namespace scent
{
    template <class Val>
    struct Item_Ref final
    {
    private:
        /**
         *
         */
        Val* _val = 0;

    public:
        /**
         *
         */
        Item_Ref();

        /**
         *
         */
        Item_Ref(Val& val);

        /**
         *
         */
        void
        init(Val& val);

        /**
         *
         */
        void
        drop();

        /**
         *
         */
        bool
        exists() const;

        /**
         *
         */
        const Val&
        val() const;

        /**
         *
         */
        Val&
        val();
    };
} // scent

#include "item_ref.inl"

#endif // SCENT_ITEM_REF_HPP
