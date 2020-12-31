#ifndef G2D_H
#define G2D_H

/**
 * Public API header.
 */

#include "utils.h"
#include "../Window/Win_32/headers/hwindows.h"
#include <stdio.h>

bool g2d_init(void);
void g2d_poll_event(void);

struct Button
{
	bool is_down;
	bool changed;
};

enum
{
	/* Mouse */
	BUTTON_LMOUSE,
	BUTTON_RMOUSE,
	BUTTON_MMOUSE,

	/* Keyboard */
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,

	BUTTON_W,
	BUTTON_A,
	BUTTON_S,
	BUTTON_D,

	BUTTON_0,
	BUTTON_1,
	BUTTON_2,
	BUTTON_3,
	BUTTON_4,
	BUTTON_5,
	BUTTON_6,
	BUTTON_7,
	BUTTON_8,
	BUTTON_9,

	BUTTON_SPACE,

	BUTTON_COUNT
};

struct G2D_Window
{
	uint width;
	uint height;
	uint32* pbuffer;

	/* Windows */
	HDC hdc;
	HWND hwnd;
	FILE* fwindow_console;
	BITMAPINFO bitmap_info;
	LARGE_INTEGER fps_counter_last;
	LARGE_INTEGER fps_counter_current;
	float fps_counter_f;
	float fps_last_dt;
};

struct G2D_Input
{
	/* Mouse */
	bool mouse_raw_input;  /* Changes behaviour of mouse_pos */
	struct Vec2 mouse_pos;
	int mouse_scroll;
	bool mouse_in_window;

	/* Keyboard */
	struct Button buttons[BUTTON_COUNT];

	bool allow_typing;
	uint type_index;
	char type_buffer[128];
};

struct G2D_Input* g2d_input;
struct G2D_Window* g2d_window;

#define IS_DOWN(btn) (g2d_input->buttons[btn].is_down)
#define PRESSED(btn) (g2d_input->buttons[btn].is_down && g2d_input->buttons[btn].changed)
#define RELEASED(btn) (!g2d_input->buttons[btn].is_down && g2d_input->buttons[btn].changed)

#define MOUSE_WHEEL_DELTA 120

#define PROCESS_BUTTON(vk, btn)\
case vk:\
{\
	g2d_input->buttons[btn].is_down = is_down;\
	g2d_input->buttons[btn].changed = true;\
} break;

#include "window.h"
#include "render.h"

#endif