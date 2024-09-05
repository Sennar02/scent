#ifndef SCENT_APPLICATION_HPP
#define SCENT_APPLICATION_HPP

#include "window.hpp"
#include "item_ref.hpp"

namespace scent
{
    struct Application
    {
    private:
        Window _wndw;
        bool   _actv = false;

    public:
        Application();

        void
        init();

        void
        drop();

        Item_Ref<Window>
        get_window(const i8* title, Vec2<u32> size);

        bool
        update();
    };
} // scent

#endif // SCENT_APPLICATION_HPP
