#ifndef G2D_W_WIN32_H
#define G2D_W_WIN32_H

#include "Win32/headers/hwindows.h"  /* First include */
#include "../../g2d.h"
#include "../utils.h"


/* Sound */

struct G2D_Win32_Sound;

bool	w_win32_sound_manager_init();
bool	w_win32_sound_manager_destroy();
int		w_win32_sound_create(LPSTR lpName);
bool	w_win32_sound_destroy(int id);
bool	w_win32_sound_play(int id);

//struct G2D_Win32_Sound* w_win32_sound_create(LPSTR lpName);
//bool					w_win32_sound_destroy(struct G2D_Win32_Sound* sound);
//bool					w_win32_sound_play(struct G2D_Win32_Sound* sound);


/* Input */

//struct Input_State input_state;
/* TODO move */
extern bool			window_input_mouse_is_within_rect(int x0, int y0, int x1, int y1);
extern struct Vec2f window_input_mouse_get_screen_coords(void);

/* Window */

//extern HWND* window_get_handle(void);

extern bool w_win32_create(HINSTANCE hInstance, uint window_width, uint window_height, char* window_name);
extern void w_win32_input(void);
extern void w_win32_render(void);
extern void w_win32_destroy(void);


/* Fps */

extern void w_win32_fps_init(void);
extern void w_win32_fps_query(void);


/* Sprites */

struct G2D_Sprite_Image
{
	uint8* pdata;
	uint bi_size_image;
	uint bi_bit_count;
	uint bi_width;
	uint bi_height;
};

struct G2D_Sprite
{
	struct G2D_Sprite_Image* sprite_image;

	struct Vec2f pos;	/* Screen coords (-1.0f -> +1.0f) */
	float pos_offset_x;
	float pos_offset_y;
	float scale;		/* 0.0f -> +1.0f */
	float angle;		/* radians */
	float angle_offset;
};


/* Sprite Image */

extern struct G2D_Sprite_Image* w_win32_sprite_image_load(char* filename);
extern void						w_win32_sprite_image_destroy(struct G2D_Sprite_Image* sprite_image);

#endif