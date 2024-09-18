#ifndef SCENT_REGISTRY_HPP
#define SCENT_REGISTRY_HPP

#include "types.hpp"
#include "alloc.hpp"
#include "array_list.hpp"
#include "loader.hpp"
#include "handle.hpp"
#include "utils.hpp"

namespace scent
{
    template <class Val>
    struct Registry
    {
    private:
        struct Ctl {
            u32 next;
            u32 iter;

            // todo(trakot): Reference counting?
        };

        Loader<Val>* _loadr = 0;

        Array_List<Ctl> _ctrl;
        Array_List<Val> _body;

        u32 _head  = 0;
        u32 _count = 0;

    public:
        Registry();

        Registry(Alloc& alloc, u32 size);

        void
        init(Alloc& alloc, u32 size);

        void
        init_loader(Loader<Val>& loader);

        void
        drop();

        /**
         * Loads a resource.
         */
        Handle<Val>
        acquire(const i8* name);

        /**
         * Unloads a resource.
         */
        void
        release(Handle<Val>& handle);

        /**
         * Retrieves an already loaded resource.
         */
        Item_Ref<const Val>
        find(Handle<Val>& handle) const;

        /**
         * Retrieves an already loaded resource.
         */
        Item_Ref<Val>
        find(Handle<Val>& handle);
    };
} // scent

#include "registry.inl"

#endif // SCENT_REGISTRY_HPP
