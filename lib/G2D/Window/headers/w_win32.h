#ifndef G2D_WINDOW_WIN32_H
#define G2D_WINDOW_WIN32_H

#include "../Win32/headers/hwindows.h"  /* First include */
#include "../../headers/g2d.h"
#include "../../headers/utils.h"

/* Input */

//struct Input_State input_state;
extern bool window_input_mouse_is_within_rect(int x0, int y0, int x1, int y1);
extern struct Vec2f window_input_mouse_get_screen_coords(void);

/* Window */

//extern HWND* window_get_handle(void);

extern bool window_create(HINSTANCE hInstance, uint window_width, uint window_height, char* window_name);
extern void window_input(void);
extern void window_render(void);


/* Fps */

extern void window_fps_init(void);
extern void window_fps_query(void);


/* Sprites */

struct Sprite_Image
{
	uint8* pdata;
	uint bi_size_image;
	uint bi_bit_count;
	uint bi_width;
	uint bi_height;
};

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


/* Sprite Image */

extern struct Sprite_Image* window_sprite_image_load(char* filename);
extern struct Sprite_Image* window_sprite_image_load(char* filename);
extern void window_sprite_image_destroy(struct Sprite_Image* sprite_image);

#endif