#include "../w_win32.h"

void 
w_win32_fps_init()
{
	LARGE_INTEGER fps_counter_frequency;
	QueryPerformanceCounter(&gp_g2d_window->fps_counter_last);
	QueryPerformanceFrequency(&fps_counter_frequency);

	gp_g2d_window->fps_counter_f = (float)fps_counter_frequency.QuadPart;
	gp_g2d_window->fps_last_dt = 0.016666f;  /* TODO get display frequency */
}

void 
w_win32_fps_query()
{
	QueryPerformanceCounter(&gp_g2d_window->fps_counter_current);
	gp_g2d_window->fps_last_dt = (float)((float)(gp_g2d_window->fps_counter_current.QuadPart - gp_g2d_window->fps_counter_last.QuadPart) / gp_g2d_window->fps_counter_f);
	gp_g2d_window->fps_counter_last = gp_g2d_window->fps_counter_current;
}