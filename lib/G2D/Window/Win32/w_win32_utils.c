#include "../w_win32.h"
#include "headers/w_win32_internal.h"

void 
w_win32_focus_set()
{
	(void)SetFocus(gp_g2d_window->hwnd);
	gp_g2d_window->has_focus = true;
	//ShowCursor(false);
}

void 
w_win32_focus_lost()
{
	gp_g2d_window->has_focus = false;
	//ShowCursor(true);
}