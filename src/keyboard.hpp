#ifndef SCENT_KEYBOARD_HPP
#define SCENT_KEYBOARD_HPP

#include "types.hpp"
#include "channel.hpp"

namespace scent
{
    struct Keyboard_Msg
    {
    public:
        enum Type
            : u32
        {
            UNDEF = 0,
            DOWN  = 1u,
            UP    = 2u,

            COUNT = UP,
        };

    public:
        /**
         *
         */
        Type type;

        /**
         *
         */
        u16 code;

        /**
         *
         */
        u16 scan;

        /**
         *
         */
        u16 modifs;

        /**
         *
         */
        u8 repeat;

    public:
        /**
         *
         */
        Keyboard_Msg();
    };

    struct Keyboard
    {
    private:
        /**
         *
         */
        u8* _states = 0;

        /**
         *
         */
        u16* _modifs = 0;

        /**
         *
         */
        Channel<Keyboard_Msg> _chnl;

    public:
        /**
         *
         */
        Keyboard();

        /**
         *
         */
        void
        init();

        /**
         *
         */
        void
        init_channel(Alloc& alloc, u32 size);

        /**
         *
         */
        void
        drop();

        /**
         *
         */
        bool
        is_down(u32 scan);

        /**
         *
         */
        bool
        is_now_down(u32 scan);

        /**
         *
         */
        bool
        is_up(u32 scan);

        /**
         *
         */
        bool
        is_now_up(u32 scan);

        /**
         *
         */
        bool
        attach(void (*fptr) (Keyboard_Msg));

        /**
         *
         */
        template <class Ctx>
        bool
        attach(Ctx& self, void (*fptr) (Ctx&, Keyboard_Msg));

        /**
         *
         */
        template <class Ctx>
        bool
        attach(Ctx& self, void (*fptr) (const Ctx&, Keyboard_Msg));

        /**
         *
         */
        void
        update();

        /**
         *
         */
        void
        send(const Keyboard_Msg& message);
    };
} // scent

#endif // SCENT_KEYBOARD_HPP
