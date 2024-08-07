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
        bool
        exists() const;

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
        val() const;

        /**
         *
         */
        Val&
        val();
    };
} // scent

#include "pair_ref.inl"

#endif // SCENT_PAIR_REF_HPP
