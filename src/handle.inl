#include "handle.hpp"
#include "registry.hpp"

namespace scent
{
    template <class Val>
    Handle<Val>::Handle() {}

    template <class Val>
    Handle<Val>::Handle(Registry<Val>& registry, u32 desc, u32 iter)
    {
        init(registry, desc, iter);
    }

    template <class Val>
    void
    Handle<Val>::init(Registry<Val>& registry, u32 desc, u32 iter)
    {
        if ( _desc != 0 )
            drop();

        _regty = &registry;
        _desc  = desc;
        _iter  = iter;
    }

    template <class Val>
    void
    Handle<Val>::drop()
    {
        if ( _regty != 0 )
            _regty->release(*this);

        _regty = 0;
        _desc  = 0;
        _iter  = 0;
    }

    template <class Val>
    bool
    Handle<Val>::is_valid() const
    {
        return _desc != 0;
    }

    template <class Val>
    u32
    Handle<Val>::desc() const
    {
        return _desc;
    }

    template <class Val>
    u32
    Handle<Val>::iter() const
    {
        return _iter;
    }
    template <class Val>
    const Val&
    Handle<Val>::value() const
    {
        assert(_regty != 0 && "The handle does not exist");

        return _regty->find(*this).value();
    }

    template <class Val>
    Val&
    Handle<Val>::value()
    {
        assert(_regty != 0 && "The handle does not exist");

        return _regty->find(*this).value();
    }
} // scent
