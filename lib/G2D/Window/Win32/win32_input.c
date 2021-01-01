#include "../headers/w_win32.h"
#include "headers/win32_internal.h"

void window_input()
{
	window_input_keyboard_reset_changed();

	MSG msg;
	while (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			exit(msg.wParam);
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}