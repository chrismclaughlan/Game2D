#include "lib/G2D/headers/g2d.h"
#include "Game/headers/game.h"
#include <stdlib.h>
#include <shellapi.h>
#include <stdio.h>

#ifndef PROJECT_NAME
#define PROJECT_NAME "Game2D"
#endif

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	if (!g2d_init())
	{
		return 1;
	}

	if (!window_create(hInstance, 600, 600, PROJECT_NAME))
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
