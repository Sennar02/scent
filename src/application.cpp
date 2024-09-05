// todo(gio): rimuovere.
#include <stdio.h>

#include <assert.h>
#include <SDL3/SDL.h>

#include "application.hpp"

namespace scent
{
    bool
    update_window(Window& window, SDL_WindowEvent event, Window_Signal::Type type)
    {
        Window_Signal sigl = {type};
        u32           code = event.windowID;

        // todo(trakot):
        // read window from hash_map and update.

        if ( window.code() == code )
            return window.update(sigl);

        return false;
    }

    bool
    update_window_move(Window& window, SDL_WindowEvent event)
    {
        Window_Signal sigl = {Window_Signal::Type::MOVE};
        u32           code = event.windowID;

        sigl.coords = {event.data1, event.data2};

        // todo(trakot):
        // read window from hash_map and update.

        if ( window.code() == code )
            return window.update(sigl);

        return false;
    }

    Application::Application()
    {
        init();
    }

    void
    Application::init()
    {
        if ( SDL_InitSubSystem(SDL_INIT_VIDEO) == true )
            _actv = true;
    }

    void
    Application::drop()
    {
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
    }

    Item_Ref<Window>
    Application::get_window(const i8* title, Vec2<u32> size)
    {
        // todo(trakot):
        // insert (window_code, window) inside hash_map
        // and then if the insertion is successful return
        // a reference.

        _wndw.init(title, size);

        return {_wndw};
    }

    bool
    Application::update()
    {
        SDL_Event event;

        while ( SDL_PollEvent(&event) != 0 ) {
            switch ( event.type ) {
                case SDL_EVENT_WINDOW_SHOWN:
                    _actv &= update_window(_wndw, event.window, Window_Signal::Type::SHOW);
                    break;

                case SDL_EVENT_WINDOW_HIDDEN:
                    _actv &= update_window(_wndw, event.window, Window_Signal::Type::HIDE);
                    break;

                case SDL_EVENT_WINDOW_MOVED:
                    _actv &= update_window_move(_wndw, event.window);
                    break;

                case SDL_EVENT_QUIT:
                    _actv = false;
                    break;

                default: break;
            }
        }

        return _actv;
    }
} // scent
