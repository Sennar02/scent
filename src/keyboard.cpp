#include <SDL3/SDL.h>

#include "keyboard.hpp"

namespace scent
{
    static const u8 KEY_CHANGE = 0x01u;
    static const u8 KEY_ACTIVE = 0x02u;

    static const u8 KEY_UP       = 0x00u;
    static const u8 KEY_NOW_UP   = 0x01u;
    static const u8 KEY_DOWN     = 0x02u;
    static const u8 KEY_NOW_DOWN = 0x03u;

    static const u32 KEY_COUNT = 512u;

    static u8  states[KEY_COUNT];
    static u16 modifs[KEY_COUNT];

    Keyboard_Msg::Keyboard_Msg()
        : type   {UNDEF}
        , code   {0}
        , scan   {0}
        , modifs {0}
        , repeat {0}
    {}

    Keyboard::Keyboard() {}

    void
    Keyboard::init()
    {
        if ( _states != 0 ) drop();

        _states = states;
        _modifs = modifs;

        for ( u32 i = 0; i < KEY_COUNT; i += 1u ) {
            _states[i] = KEY_UP;
            _modifs[i] = 0;
        }
    }

    void
    Keyboard::init_channel(Alloc& alloc, u32 size)
    {
        _chnl.init(alloc, size);
    }

    void
    Keyboard::drop()
    {
        _states = 0;
        _modifs = 0;

        _chnl.drop();
    }

    bool
    Keyboard::is_down(u32 scan)
    {
        if ( scan < KEY_COUNT )
            return _states[scan] == KEY_DOWN;

        return false;
    }

    bool
    Keyboard::is_now_down(u32 scan)
    {
        if ( scan < KEY_COUNT )
            return _states[scan] == KEY_NOW_DOWN;

        return false;
    }

    bool
    Keyboard::is_up(u32 scan)
    {
        if ( scan < KEY_COUNT )
            return _states[scan] == KEY_UP;

        return false;
    }

    bool
    Keyboard::is_now_up(u32 scan)
    {
        if ( scan < KEY_COUNT )
            return _states[scan] == KEY_NOW_UP;

        return false;
    }

    bool
    Keyboard::attach(void (*fptr) (Keyboard_Msg))
    {
        return _chnl.attach(fptr);
    }

    template <class Ctx>
    bool
    Keyboard::attach(Ctx& self, void (*fptr) (Ctx&, Keyboard_Msg))
    {
        return _chnl.attach(self, fptr);
    }

    template <class Ctx>
    bool
    Keyboard::attach(Ctx& self, void (*fptr) (const Ctx&, Keyboard_Msg))
    {
        return _chnl.attach(self, fptr);
    }

    void
    Keyboard::update()
    {
        for ( u32 i = 0; i < KEY_COUNT; i += 1u ) {
            _states[i] = _states[i] & ~KEY_CHANGE;
            _modifs[i] = 0;
        }
    }

    void
    Keyboard::send(const Keyboard_Msg& message)
    {
        u8 first = message.repeat == 0;

        switch ( message.type ) {
            case Keyboard_Msg::DOWN: {
                _states[message.scan] = KEY_ACTIVE + KEY_CHANGE * first;
                _modifs[message.scan] = message.modifs;
            } break;

            case Keyboard_Msg::UP: {
                _states[message.scan] = KEY_CHANGE;
                _modifs[message.scan] = message.modifs;
            } break;

            case Keyboard_Msg::UNDEF:
                break;
        }

        _chnl.send(message);
    }
} // scent
