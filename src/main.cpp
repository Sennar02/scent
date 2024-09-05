#include "application.hpp"
#include "window.hpp"

using namespace scent;

static Application game;

int
main()
{
    Window window =
        game.get_window("Prova", {640u, 360u}).val();

    window.show();

    while ( game.update() ) {
        Vec4<f32> rect = {10u, 10u, 620u, 340u};

        window.fill_rect(rect, COLOUR_BLACK);
        window.render(COLOUR_WHITE);
    }

    game.drop();
}
