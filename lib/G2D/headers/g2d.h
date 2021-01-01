#ifndef G2D_H
#define G2D_H

/**
 * Public API header.
 */

#include "utils.h"
#include "window.h"
#include "render.h"

bool g2d_init(void);
void g2d_poll_event(void);

struct G2D_Input* gp_g2d_input;
struct G2D_Window* gp_g2d_window;



//enum G2D_Window_Type
//{
//	G2D_WINDOW_TYPE_WIN32,
//
//	G2D_WINDOW_TYPE_COUNT
//};
//
//struct G2D_Window_Header
//{
//	uint width;
//	uint height;
//	uint32* p_buffer;
//	enum G2D_Window_Type type;
//};
//
//struct G2D_Window_Win32
//{
//	struct G2D_Window_Header header;
//
//	HDC hdc;
//	HWND hwnd;
//	FILE* f_window_console;
//	BITMAPINFO bitmap_info;
//	LARGE_INTEGER fps_counter_last;
//	LARGE_INTEGER fps_counter_current;
//	float fps_counter_f;
//	float fps_last_dt;
//};
//return ((struct G2D_Window_Win32*)gp_g2d_window)->fps_last_dt;

#endif