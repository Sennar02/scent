#ifndef SCENT_KEYBOARD_HPP
#define SCENT_KEYBOARD_HPP

#include "types.hpp"

namespace scent
{
    struct Keyboard_Signal
    {
    public:
        enum Type
            : u32
        {
            DOWN = 1u,
            UP   = 2u,

            COUNT = UP,
            UNDEF,
        };

    public:
        Type type;

        u16 code;
        u16 scan;
        u16 modifs;
        u8  repeat;

    public:
        Keyboard_Signal();
    };

    struct Keyboard
    {
    private:
        u8*  _states = 0;
        u16* _modifs = 0;

    public:
        Keyboard();

        void
        init();

        void
        drop();

        bool
        is_down(u32 scan);

        bool
        is_now_down(u32 scan);

        bool
        is_up(u32 scan);

        bool
        is_now_up(u32 scan);

        void
        update();

        void
        signal(Keyboard_Signal signal);
    };
} // scent

#endif // SCENT_KEYBOARD_HPP
