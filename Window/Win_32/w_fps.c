#include "win32.h"

void window_fps_init()
{
	LARGE_INTEGER fps_counter_frequency;
	QueryPerformanceCounter(&g2d_window->fps_counter_last);
	QueryPerformanceFrequency(&fps_counter_frequency);

	g2d_window->fps_counter_f = (float)fps_counter_frequency.QuadPart;
	g2d_window->fps_last_dt = 0.016666f;  /* TODO get display frequency */
}

void window_fps_query()
{
	QueryPerformanceCounter(&g2d_window->fps_counter_current);
	g2d_window->fps_last_dt = (float)((float)(g2d_window->fps_counter_current.QuadPart - g2d_window->fps_counter_last.QuadPart) / g2d_window->fps_counter_f);
	g2d_window->fps_counter_last = g2d_window->fps_counter_current;
}