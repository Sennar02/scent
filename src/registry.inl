#include "registry.hpp"

namespace scent
{
    template <class Val>
    Registry<Val>::Registry() {}

    template <class Val>
    Registry<Val>::Registry(Alloc& alloc, u32 size)
    {
        init(alloc, size);
    }

    template <class Val>
    void
    Registry<Val>::init(Alloc& alloc, u32 size)
    {
        _ctrl.init(alloc, size);
        _body.init(alloc, size);

        _head  = 0;
        _count = 0;
    }

    template <class Val>
    void
    Registry<Val>::init_loader(Loader<Val>& loader)
    {
        _loadr = &loader;
    }

    template <class Val>
    void
    Registry<Val>::drop()
    {
        _body.drop();
        _ctrl.drop();

        _head  = 0;
        _count = 0;
    }

    template <class Val>
    Handle<Val>
    Registry<Val>::acquire(const i8* name)
    {
        Val value = _loadr->load(name);
        u32 index = _body.count();
        u32 iter  = 1u;

        if ( _count != 0 ) {
            index = extr(_head, _ctrl[_head].next);
            iter  = _ctrl[index].iter;

            _body[index]  = value;
            _count       -= 1u;
        } else {
            Ctl ctrl = {index, iter};

            if ( _ctrl.push_tail(ctrl)  == false ||
                 _body.push_tail(value) == false )
                return {};
        }

        return {*this, index + 1u, iter};
    }

    template <class Val>
    void
    Registry<Val>::release(Handle<Val>& handle)
    {
        u32 index = handle.desc() - 1u;

        if ( index < _body.count() ) {
            if ( _ctrl[index].iter != handle.iter() )
                return;

            _loadr->unload(_body[index]);

           _ctrl[index].iter += 1u;

            if ( _ctrl[index].iter != 0 ) {
                swap(_head, _ctrl[index].next);

                _count += 1u;
            }
        }
    }

    template <class Val>
    Item_Ref<const Val>
    Registry<Val>::find(Handle<Val>& handle) const
    {
        u32 index = handle.desc() - 1u;

        if ( index < _body.count() ) {
            if ( _ctrl[index].iter == handle.iter() )
                return {_body[index]};
        }

        return {};
    }

    template <class Val>
    Item_Ref<Val>
    Registry<Val>::find(Handle<Val>& handle)
    {
        u32 index = handle.desc() - 1u;

        if ( index < _body.count() ) {
            if ( _ctrl[index].iter == handle.iter() )
                return {_body[index]};
        }

        return {};
    }
} // scent
