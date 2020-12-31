#include "render.h"

void render_clear_screen(uint32 colour)
{
	uint32* pixel = g2d_window->pbuffer;

	for (uint y = 0; y < g2d_window->height; y++)
	{
		for (uint x = 0; x < g2d_window->width; x++)
		{
			*pixel++ = colour;
		}
	}
}

inline float render_coord_translate_from_i_x(int i)
{
	return ((float)i / (float)g2d_window->width) * 2.0f;
}

inline float render_coord_translate_from_i_y(int i)
{
	return ((float)i / (float)g2d_window->height) * 2.0f;
}

inline int render_coord_translate_from_f_x(float f)
{
	return (f / 2.0f) * (float)g2d_window->width;
}

inline int render_coord_translate_from_f_y(float f)
{
	return (f / 2.0f) * (float)g2d_window->height;
}

struct Vec2 render_screen_to_px(struct Vec2f vf)
{
	struct Vec2 v;

	v.x = render_coord_translate_from_f_x((vf.x + 1.0f));
	v.y = render_coord_translate_from_f_y((vf.y + 1.0f));

	return v;
}

struct Vec2f render_px_to_screen(struct Vec2 v)
{
	struct Vec2f vf;

	vf.x = render_coord_translate_from_i_x(v.x) - 1.0f;
	vf.y = render_coord_translate_from_i_y(v.y) - 1.0f;

	return vf;
}
