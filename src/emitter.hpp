#ifndef SCENT_EMITTER_HPP
#define SCENT_EMITTER_HPP

#include "types.hpp"
#include "alloc.hpp"
#include "array_list.hpp"
#include "invoker.hpp"

namespace scent
{
    template <class Sig>
    using Handler = Invoker<void (Sig)>;

    template <class Sig>
    struct Emitter
    {
    private:
        /**
         *
         */
        Array_List<Handler<Sig>> _list;

    public:
        /**
         *
         */
        Emitter();

        /**
         *
         */
        Emitter(Alloc& alloc, u32 size);

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
        bool
        attach(void (*fptr) (Sig));

        /**
         *
         */
        template <class Ctx>
        bool
        attach(void (*fptr) (Ctx&, Sig), Ctx& self);

        /**
         *
         */
        template <class Ctx>
        bool
        attach(void (*fptr) (const Ctx&, Sig), Ctx& self);

        /**
         *
         */
        void
        emit(const Sig& signal) const;
    };
} // scent

#include "emitter.inl"

#endif // SCENT_EMITTER_HPP
