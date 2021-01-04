#include "lib/g2d.h"
#include "game.h"
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

	if (!w_win32_create(hInstance, 600, 600, PROJECT_NAME))
	{
		return 1;
	}
	//(void) atexit(w_win32_destroy)

	game_init();
	(void) atexit(game_destroy);

	w_win32_fps_init();
    for (;;)
    {
        /* Input */
        w_win32_input();

        /* Simulate */
        game_simulate();

        /* Render TODO w_win32_render() ... again */
		w_win32_render();

		/* frame rate */
		w_win32_fps_query();
    }

	return 0;
}
