#include "invoker.hpp"

namespace scent
{
    template <class Res, class... Args>
    Invoker<Res (Args...)>::Invoker() {}

    template <class Res, class... Args>
    Invoker<Res (Args...)>::Invoker(Res (*fptr) (Args...))
    {
        init(fptr);
    }

    template <class Res, class... Args>
    template <class Ctx>
    Invoker<Res (Args...)>::Invoker(Res (*fptr) (Ctx&, Args...), Ctx& self)
    {
        init(fptr, self);
    }

    template <class Res, class... Args>
    template <class Ctx>
    Invoker<Res (Args...)>::Invoker(Res (*fptr) (const Ctx&, Args...), Ctx& self)
    {
        init(fptr, self);
    }

    template <class Res, class... Args>
    void
    Invoker<Res (Args...)>::init(Res (*fptr) (Args...))
    {
        if ( fptr == 0 ) return;

        _fptr = (i8*) fptr;
        _self = 0;
    }

    template <class Res, class... Args>
    template <class Ctx>
    void
    Invoker<Res (Args...)>::init(Res (*fptr) (Ctx&, Args...), Ctx& self)
    {
        if ( fptr == 0 ) return;

        _fptr = (i8*) fptr;
        _self = (i8*) &self;
    }

    template <class Res, class... Args>
    template <class Ctx>
    void
    Invoker<Res (Args...)>::init(Res (*fptr) (const Ctx&, Args...), Ctx& self)
    {
        if ( fptr == 0 ) return;

        _fptr = (i8*) fptr;
        _self = (i8*) &self;
    }

    template <class Res, class... Args>
    void
    Invoker<Res (Args...)>::drop()
    {
        _fptr = 0;
        _self = 0;
    }

    template <class Res, class... Args>
    Res
    Invoker<Res (Args...)>::call(Args... args) const
    {
        using Free  = Res (Args...);
        using Bound = Res (i8&, Args...);

        assert(_fptr != 0 && "The invoker does not exist.");

        if ( _self != 0 )
            return ((Bound*) _fptr)(*_self, args...);

        return ((Free*) _fptr)(args...);
    }

    template <class Res, class... Args>
    Res
    Invoker<Res (Args...)>::operator()(Args... args) const
    {
        using Free  = Res (Args...);
        using Bound = Res (i8&, Args...);

        assert(_fptr != 0 && "The invoker does not exist.");

        if ( _self != 0 )
            return ((Bound*) _fptr)(*_self, args...);

        return ((Free*) _fptr)(args...);
    }
} // scent
