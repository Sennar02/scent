#include <SDL3/SDL.h>

#include "application.hpp"

namespace scent
{
    void
    window_signal(Window* window, SDL_WindowEvent event);

    void
    keyboard_signal(Keyboard* keyboard, SDL_KeyboardEvent event);

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
        // todo(trakot):
        // insert (window_code, window) inside hash_map.

        _wndw = &window;
    }

    void
    Application::init_keyboard(Keyboard& keyboard)
    {
        _kybd = &keyboard;
    }

    bool
    Application::update()
    {
        if ( _wndw != 0 ) _wndw->update();
        if ( _kybd != 0 ) _kybd->update();

        return _actv;
    }

    bool
    Application::signal()
    {
        SDL_Event event;

        if ( SDL_PollEvent(&event) == false )
            return false;

        switch ( event.type ) {
            case SDL_EVENT_WINDOW_SHOWN:
            case SDL_EVENT_WINDOW_HIDDEN:
            case SDL_EVENT_WINDOW_MOVED: {
                window_signal(_wndw, event.window);
            } break;

            case SDL_EVENT_KEY_DOWN:
            case SDL_EVENT_KEY_UP: {
                keyboard_signal(_kybd, event.key);
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

            while ( signal() ) {
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

    void
    window_signal(Window* window, SDL_WindowEvent event)
    {
        Window_Signal signal;

        if ( window == 0 || window->code() != event.windowID)
            return;

        switch ( event.type ) {
            case SDL_EVENT_WINDOW_SHOWN: {
                signal.type = Window_Signal::SHOW;
            } break;

            case SDL_EVENT_WINDOW_HIDDEN: {
                signal.type = Window_Signal::HIDE;
            } break;

            case SDL_EVENT_WINDOW_MOVED: {
                signal.type   = Window_Signal::MOVE;
                signal.coords = {event.data1, event.data2};
            } break;

            default: break;
        }

        // todo(trakot): read window from hash_map and update.

        window->signal(signal);
    }

    void
    keyboard_signal(Keyboard* keyboard, SDL_KeyboardEvent event)
    {
        Keyboard_Signal signal;

        if ( keyboard == 0 ) return;

        switch ( event.type ) {
            case SDL_EVENT_KEY_DOWN: {
                signal.type = Keyboard_Signal::DOWN;
            } break;

            case SDL_EVENT_KEY_UP: {
                signal.type = Keyboard_Signal::UP;
            } break;

            default: break;
        }

        signal.code   = event.key;
        signal.scan   = event.scancode;
        signal.modifs = event.mod;
        signal.repeat = event.repeat;

        keyboard->signal(signal);
    }
} // scent

