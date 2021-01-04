#include "../w_win32.h"
#include "headers/w_win32_internal.h"

void 
w_win32_destroy(void)
{
	if (!w_win32_sound_manager_destroy())
	{
		LOG_ERROR("w_win32_sound_manager_destroy()\n");
	}


	if (gp_g2d_window->hdc && ReleaseDC(gp_g2d_window->hwnd, gp_g2d_window->hdc))
	{
		gp_g2d_window->hdc = NULL;
	}
	if (gp_g2d_window->hwnd && DestroyWindow(gp_g2d_window->hwnd))
	{
		gp_g2d_window->hwnd = NULL;
	}
	if (UnregisterClass(G2D_WINDOW_CLASS_NAME, gp_g2d_window->hinstance))
	{
		gp_g2d_window = NULL;
	}
}