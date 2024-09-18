#include "channel.hpp"

namespace scent
{
    template <class Msg>
    Channel<Msg>::Channel() {}

    template <class Msg>
    Channel<Msg>::Channel(Alloc& alloc, u32 size)
    {
        init(alloc, size);
    }

    template <class Msg>
    void
    Channel<Msg>::init(Alloc& alloc, u32 size)
    {
        _pure.init(alloc, size);
        _tied.init(alloc, size);
    }

    template <class Msg>
    void
    Channel<Msg>::drop()
    {
        _tied.drop();
        _pure.drop();
    }

    template <class Msg>
    bool
    Channel<Msg>::attach(void (*fptr) (Msg))
    {
        Pure func = {(i8*) fptr};

        if ( fptr != 0 )
            return _pure.push_tail(func);

        return false;
    }

    template <class Msg>
    template <class Ctx>
    bool
    Channel<Msg>::attach(Ctx& self, void (*fptr) (Ctx&, Msg))
    {
        Tied func = {(i8*) fptr, (i8*) &self};

        if ( fptr != 0 )
            return _tied.push_tail(func);

        return false;
    }

    template <class Msg>
    template <class Ctx>
    bool
    Channel<Msg>::attach(const Ctx& self, void (*fptr) (const Ctx&, Msg))
    {
        Tied func = {(i8*) fptr, (i8*) &self};

        if ( fptr != 0 )
            return _tied.push_tail(func);

        return false;
    }

    template <class Msg>
    void
    Channel<Msg>::send(const Msg& message) const
    {
        using Tied_Func = void (i8&, Msg);
        using Pure_Func = void (Msg);

        auto tied = _tied.values();

        for ( u32 i = 0; i < tied.size(); i += 1u )
            ((Tied_Func*) tied[i].fptr)(*tied[i].self, message);

        auto pure = _pure.values();

        for ( u32 i = 0; i < pure.size(); i += 1u )
            ((Pure_Func*) pure[i].fptr)(message);
    }
} // scent
