#include "../w_win32.h"
#include "headers/w_win32_internal.h"
#include <stdlib.h>

void 
w_win32_input()
{
	window_input_keyboard_reset_changed();

	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			(void)exit((int)msg.wParam);
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}