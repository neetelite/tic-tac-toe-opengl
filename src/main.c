#include "../../library/base.h"
#include "../../library/platform.h"
#include "../../library/graphics.h"

#include "gl_shape.c"

#include "game.h"
#include "game.c"

i32
main(void)
{
    /* Path */
    os_path_build();

    /* Window */
    os_window_create(900, 900, "Tic Tac Toe");

    /* OpenGL */
    os_opengl_init();
    gl_init();
    gl_load_all_programs();

    /* Input */
    os_input_init();

    /* Timer */
    time_init();
    struct TimeLimiter time_limiter = {0};
    time_limiter_init(&time_limiter, 30.0);

    Game game = {0};
    game_init(&game);

    os_state.running = true;
    loop
    {
        os_events();
        game_update(&game);
        os_render();

        time_limiter_tick(&time_limiter);

        if(!os_state.running) break;
    }
}