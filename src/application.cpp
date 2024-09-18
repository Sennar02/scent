#include <SDL3/SDL.h>

#include "application.hpp"

namespace scent
{
    void
    message_window(Window* window, SDL_WindowEvent event)
    {
        Window_Msg message;

        // todo(trakot): read window from registry and update.

        switch ( event.type ) {
            case SDL_EVENT_WINDOW_SHOWN: {
                message.type = Window_Msg::SHOW;
            } break;

            case SDL_EVENT_WINDOW_HIDDEN: {
                message.type = Window_Msg::HIDE;
            } break;

            case SDL_EVENT_WINDOW_MOVED: {
                message.type   = Window_Msg::MOVE;
                message.coords = {event.data1, event.data2};
            } break;

            default: break;
        }


        if ( window != 0 && window->desc() == event.windowID )
            window->send(message);
    }

    void
    message_keyboard(Keyboard* keyboard, SDL_KeyboardEvent event)
    {
        Keyboard_Msg message;

        // todo(trakot): read keyboard from registry and update.

        switch ( event.type ) {
            case SDL_EVENT_KEY_DOWN: {
                message.type = Keyboard_Msg::DOWN;
            } break;

            case SDL_EVENT_KEY_UP: {
                message.type = Keyboard_Msg::UP;
            } break;

            default: break;
        }

        message.code   = event.key;
        message.scan   = event.scancode;
        message.modifs = event.mod;
        message.repeat = event.repeat;

        if ( keyboard != 0 )
            keyboard->send(message);
    }

    Application::Application() {}

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

    bool
    Application::is_active() const
    {
        return _actv;
    }

    void
    Application::stop()
    {
        _actv = false;
    }

    void
    Application::init_window(Window& window)
    {
        // todo(trakot): insert window in registry.

        _wndw = &window;
    }

    void
    Application::init_keyboard(Keyboard& keyboard)
    {
        // todo(trakot): insert keyboard in registry.

        _kybd = &keyboard;
    }

    bool
    Application::update()
    {
        // todo(trakot): update every resource in registry.

        if ( _wndw != 0 ) _wndw->update();
        if ( _kybd != 0 ) _kybd->update();

        return _actv;
    }

    bool
    Application::handle()
    {
        SDL_Event event;

        if ( SDL_PollEvent(&event) == false ) return false;

        switch ( event.type ) {
            case SDL_EVENT_WINDOW_SHOWN:
            case SDL_EVENT_WINDOW_HIDDEN:
            case SDL_EVENT_WINDOW_MOVED: {
                message_window(_wndw, event.window);
            } break;

            case SDL_EVENT_KEY_DOWN:
            case SDL_EVENT_KEY_UP: {
                message_keyboard(_kybd, event.key);
            } break;

            case SDL_EVENT_QUIT: {
                _actv = false;
            } break;

            default: break;
        }

        return true;
    }

    void
    Application::loop(Stage& stage, f32 frames)
    {
        f32 unit = 1.0f / frames;
        f32 time = 0.0f;

        if ( stage.init(*this) == false ) return;

        _clck.update();

        while ( update() ) {
            time += _clck.update();

            while ( handle() ) {
                if ( stage.input() == false )
                    stop();
            }

            stage.frame();

            for ( ; time >= unit; time -= unit )
                stage.tick(unit);

            stage.draw();
        }

        stage.drop();
    }
} // scent
