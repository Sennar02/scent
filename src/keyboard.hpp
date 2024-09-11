#ifndef SCENT_KEYBOARD_HPP
#define SCENT_KEYBOARD_HPP

#include "types.hpp"
#include "emitter.hpp"

namespace scent
{
    struct Keyboard_Signal
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
        Keyboard_Signal();
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
        Emitter<Keyboard_Signal> _emtr;

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
        init_emitter(Alloc& alloc, u32 size);

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
        attach(void (*fptr) (Keyboard_Signal));

        /**
         *
         */
        template <class Ctx>
        bool
        attach(void (*fptr) (Ctx&, Keyboard_Signal), Ctx& self);

        /**
         *
         */
        template <class Ctx>
        bool
        attach(void (*fptr) (const Ctx&, Keyboard_Signal), Ctx& self);

        /**
         *
         */
        void
        update();

        /**
         *
         */
        void
        signal(const Keyboard_Signal& signal);
    };
} // scent

#endif // SCENT_KEYBOARD_HPP
