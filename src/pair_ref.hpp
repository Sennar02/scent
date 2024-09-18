#ifndef SCENT_PAIR_REF_HPP
#define SCENT_PAIR_REF_HPP

#include <assert.h>

namespace scent
{
    template <class Key, class Val>
    struct Pair_Ref final
    {
    private:
        /**
         *
         */
        Key* _key = 0;

        /**
         *
         */
        Val* _val = 0;

    public:
        /**
         *
         */
        Pair_Ref();

        /**
         *
         */
        Pair_Ref(Key& key, Val& val);

        /**
         *
         */
        void
        init(Key& key, Val& val);

        /**
         *
         */
        void
        drop();

        /**
         *
         */
        bool
        is_valid() const;

        /**
         *
         */
        const Key&
        key() const;

        /**
         *
         */
        Key&
        key();

        /**
         *
         */
        const Val&
        value() const;

        /**
         *
         */
        Val&
        value();
    };
} // scent

#include "pair_ref.inl"

#endif // SCENT_PAIR_REF_HPP
