#include "../render.h"

void 
r_clear_screen(uint32 colour)
{
	uint32* pixel = gp_g2d_window->p_buffer;

	for (uint y = 0; y < gp_g2d_window->height; y++)
	{
		for (uint x = 0; x < gp_g2d_window->width; x++)
		{
			*pixel++ = colour;
		}
	}
}

inline float 
r_coord_translate_from_i_x(int i)
{
	return ((float)i / (float)gp_g2d_window->width) * 2.0f;
}

inline float 
r_coord_translate_from_i_y(int i)
{
	return ((float)i / (float)gp_g2d_window->height) * 2.0f;
}

inline int 
r_coord_translate_from_f_x(float f)
{
	return (f / 2.0f) * (float)gp_g2d_window->width;
}

inline int 
r_coord_translate_from_f_y(float f)
{
	return (f / 2.0f) * (float)gp_g2d_window->height;
}

struct Vec2 
r_screen_to_px(struct Vec2f vf)
{
	struct Vec2 v;

	v.x = r_coord_translate_from_f_x((vf.x + 1.0f));
	v.y = r_coord_translate_from_f_y((vf.y + 1.0f));

	return v;
}

struct Vec2f 
r_px_to_screen(struct Vec2 v)
{
	struct Vec2f vf;

	vf.x = r_coord_translate_from_i_x(v.x) - 1.0f;
	vf.y = r_coord_translate_from_i_y(v.y) - 1.0f;

	return vf;
}
