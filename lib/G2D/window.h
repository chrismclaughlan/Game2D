#ifndef G2D_W_H
#define G2D_W_H


#include <stdio.h>


#define LOG_DEBUG(format, ...)\
	{fprintf(stderr, "[DEBUG]: "); \
	fprintf(stderr, format, ##__VA_ARGS__);}

#define LOG_ERROR(format, ...)\
	{fprintf(stderr, "[FILE]: %s [FUNC]: %s [LINE]: %d [MSG]: ", \
	__FILE__, __FUNCTION__, __LINE__); \
	fprintf(stderr, format, ##__VA_ARGS__);}


#include "utils.h"
#include "Window/w_buttons.h"
#include "Window/w_input.h"

#if defined(_WIN32) || defined(_WIN64)
#include "Window/w_win32.h"
#else
/* Other platforms */
#endif


struct G2D_Window
{
	uint width;
	uint height;
	uint32* p_buffer;
	bool has_focus;

#if defined(_WIN32) || defined(_WIN64)
	HINSTANCE hinstance;
	HDC hdc;
	HWND hwnd;
	FILE* f_window_console;
	BITMAPINFO bitmap_info;
	LARGE_INTEGER fps_counter_last;
	LARGE_INTEGER fps_counter_current;
	float fps_counter_f;
	float fps_last_dt;
#else
	/* Other platforms */
#endif
};


#endif