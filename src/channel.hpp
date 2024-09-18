#ifndef SCENT_CHANNEL_HPP
#define SCENT_CHANNEL_HPP

#include "types.hpp"
#include "alloc.hpp"
#include "array_list.hpp"

namespace scent
{
    template <class Msg>
    struct Channel
    {
    private:
        struct Pure {
            i8* fptr;
        };

        struct Tied {
            i8* fptr;
            i8* self;
        };

        /**
         *
         */
        Array_List<Pure> _pure;

        /**
         *
         */
        Array_List<Tied> _tied;

    public:
        /**
         *
         */
        Channel();

        /**
         *
         */
        Channel(Alloc& alloc, u32 size);

        /**
         *
         */
        void
        init(Alloc& alloc, u32 size);

        /**
         *
         */
        void
        drop();

        /**
         *
         */
        bool
        attach(void (*fptr) (Msg));

        /**
         *
         */
        template <class Ctx>
        bool
        attach(Ctx& self, void (*fptr) (Ctx&, Msg));

        /**
         *
         */
        template <class Ctx>
        bool
        attach(const Ctx& self, void (*fptr) (const Ctx&, Msg));

        /**
         *
         */
        void
        send(const Msg& message) const;
    };
} // scent

#include "channel.inl"

#endif // SCENT_CHANNEL_HPP
