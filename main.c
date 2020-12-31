#include "G2D/g2d.h"
#include "Game/game.h"
#include <stdlib.h>
#include <shellapi.h>
#include <stdio.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	if (!g2d_init())
	{
		return 1;
	}

	if (!window_create(hInstance, 600, 600, "Game"))
	{
		return 1;
	}
	//(void) atexit(window_destroy)

	game_init();
	(void) atexit(game_destroy);

	window_fps_init();
    for (;;)
    {
        /* Input */
        window_input();

        /* Simulate */
        game_simulate();

        /* Render TODO window_render() ... again */
		window_render();

		/* frame rate */
		window_fps_query();
    }

	return 0;
}