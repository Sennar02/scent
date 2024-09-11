#include "emitter.hpp"

namespace scent
{
    template <class Sig>
    Emitter<Sig>::Emitter() {}

    template <class Sig>
    Emitter<Sig>::Emitter(Alloc& alloc, u32 size)
    {
        init(alloc, size);
    }

    template <class Sig>
    void
    Emitter<Sig>::init(Alloc& alloc, u32 size)
    {
        _list.init(alloc, size);
    }

    template <class Sig>
    void
    Emitter<Sig>::drop()
    {
        _list.drop();
    }

    template <class Sig>
    bool
    Emitter<Sig>::attach(void (*fptr) (Sig))
    {
        Handler<Sig> hdlr = {fptr};

        if ( fptr != 0 )
            return _list.push_tail(hdlr);

        return false;
    }

    template <class Sig>
    template <class Ctx>
    bool
    Emitter<Sig>::attach(void (*fptr) (Ctx&, Sig), Ctx& self)
    {
        Handler<Sig> hdlr = {fptr, self};

        if ( fptr != 0 )
            return _list.push_tail(hdlr);

        return false;
    }

    template <class Sig>
    template <class Ctx>
    bool
    Emitter<Sig>::attach(void (*fptr) (const Ctx&, Sig), Ctx& self)
    {
        Handler<Sig> hdlr = {fptr, self};

        if ( fptr != 0 )
            return _list.push_tail(hdlr);

        return false;
    }

    template <class Sig>
    void
    Emitter<Sig>::emit(const Sig& signal) const
    {
        auto slice = _list.values();

        for ( u32 i = 0; i < slice.size(); i += 1u )
            slice[i].call(signal);
    }
} // scent
