#ifndef SCENT_INVOKER_HPP
#define SCENT_INVOKER_HPP

#include "types.hpp"

namespace scent
{
    template <class... Pack>
    struct Invoker;

    template <class Res, class... Args>
    struct Invoker<Res(Args...)>
    {
    private:
        /**
         *
         */
        i8* _fptr = 0;

        /**
         *
         */
        i8* _self = 0;

    public:
        /**
         *
         */
        Invoker();

        /**
         *
         */
        Invoker(Res (*fptr) (Args...));

        /**
         *
         */
        template <class Ctx>
        Invoker(Res (*fptr) (Ctx&, Args...), Ctx& self);

        /**
         *
         */
        template <class Ctx>
        Invoker(Res (*fptr) (const Ctx&, Args...), Ctx& self);

        /**
         *
         */
        void
        init(Res (*fptr) (Args...));

        /**
         *
         */
        template <class Ctx>
        void
        init(Res (*fptr) (Ctx&, Args...), Ctx& self);

        /**
         *
         */
        template <class Ctx>
        void
        init(Res (*fptr) (const Ctx&, Args...), Ctx& self);

        /**
         *
         */
        void
        drop();

        /**
         *
         */
        Res
        call(Args... args) const;

        /**
         *
         */
        Res
        operator()(Args... args) const;
    };
} // scent

#include "invoker.inl"

#endif // SCENT_INVOKER_HPP
