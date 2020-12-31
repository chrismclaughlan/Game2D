#ifndef G2D_WINDOW_WIN32_H
#define G2D_WINDOW_WIN32_H

#include "../Win_32/headers/hwindows.h"  /* First include */
#include "../../headers/g2d.h"
#include "../../headers/utils.h"

#include <stdio.h>

#define SOLID_COLOUR(c) (c | 0xff000000)

/* Input */

//struct Input_State input_state;
extern bool window_input_mouse_is_within_rect(int x0, int y0, int x1, int y1);
extern struct Vec2f window_input_mouse_get_screen_coords(void);

/* Window */

//extern HWND* window_get_handle(void);

bool window_create(HINSTANCE hInstance, uint window_width, uint window_height, char* window_name);

#define LOG_DEBUG(format, ...) {fprintf(stderr, "[DEBUG]: "); fprintf(stderr, format, ##__VA_ARGS__);}
#define LOG_ERROR(format, ...) {fprintf(stderr, "[FILE]: %s [FUNC]: %s [LINE]: %d [MSG]: ", __FILE__, __FUNCTION__, __LINE__); fprintf(stderr, format, ##__VA_ARGS__);}

extern void window_input(void);

//extern uint window_get_width(void);
//extern uint window_get_height(void);
extern void window_render(void);


/* - - - - - - - - Input - - - - - - - - */


#define TYPING_ALLOWED_CHARS "0123456789abcdefghijklmnopqrstuvwxyz!£$*(){}[],.<>/?\;'#:@~`¬"


/* Keyboard */

void window_input_keyboard_reset(void);
void window_input_keyboard_reset_changed(void);
void window_input_keyboard_event(uint vk_code, bool is_down);
void window_input_keyboard_event_type(char vk_code);

/* Mouse */
void window_input_mouse_event_move(int x, int y);
void window_input_mouse_event_scroll(int delta);
void window_input_mouse_event_click(uint vk_code, bool is_down);
void window_input_mouse_event_window_enter();
void window_input_mouse_event_window_leave();


/* - - - - - - - - Internal.h - - - - - - - - */

//struct Render_Buffer
//{
//	uint width;
//	uint height;
//	uint32* pbuffer;
//	BITMAPINFO bitmap_info;
//};

LRESULT window_callback(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
extern void window_fps_init(void);
extern void window_fps_query(void);

//struct Input_State input_state;
//struct Render_Buffer render_buffer;
//
//HDC hdc;
//HWND hwnd;
//FILE* fwindow_console;

//struct Game2D_Window
//{
//	struct Input_State input_state;
//	struct Render_Buffer render_buffer;
//
//	HDC hdc;
//	HWND hwnd;
//	FILE* fwindow_console;
//};


/* Sprites */

struct Sprite
{
	struct Sprite_Image* sprite_image;

	struct Vec2f pos;	/* Screen coords (-1.0f -> +1.0f) */
	float pos_offset_x;
	float pos_offset_y;
	float scale;		/* 0.0f -> +1.0f */
	float angle;		/* radians */
	float angle_offset;
};

struct Sprite_Image
{
	uint8* pdata;
	uint bi_size_image;
	uint bi_bit_count;
	uint bi_width;
	uint bi_height;
};

/* Sprite Image */
struct Sprite_Image* window_sprite_image_load(char* filename);
extern struct Sprite_Image* window_sprite_image_load(char* filename);
extern void window_sprite_image_destroy(struct Sprite_Image* sprite_image);

#endif