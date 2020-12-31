#include "render.h"


/* Draw Rect */

static void render_draw_rect_pixels(uint32 colour, uint x0, uint y0, uint x1, uint y1)
{
	x0 = clamp(x0, 0, g2d_window->width);
	x1 = clamp(x1, 0, g2d_window->width);
	y0 = clamp(y0, 0, g2d_window->height);
	y1 = clamp(y1, 0, g2d_window->height);

	for (uint y = y0; y < y1; y++)
	{
		uint32* pixel = (g2d_window->pbuffer + x0) + (y * g2d_window->width);
		for (uint x = x0; x < x1; x++)
		{
			*pixel++ = colour;
		}
	}
}

/**
 *       +1.0f
 *         |
 * -1.0f <-@-> +1.0f
 *         |
 *       -1.0f
 */
void render_draw_rect(uint32 colour, struct Vec2f vf, float half_width, float half_height)
{
	int half_width_i, half_height_i;
	struct Vec2 v;

	/* Find center pixel */
	clampv(vf, -1.0f, +1.0f);
	v = render_screen_to_px(vf);

	/* Translate dismentions */
	half_width_i = render_coord_translate_from_f_x(half_width);
	half_height_i = render_coord_translate_from_f_y(half_height);

	render_draw_rect_pixels(colour,
		v.x - half_width_i,
		v.y - half_height_i,
		v.x + half_width_i,
		v.y + half_height_i
	);

	//LOG_DEBUG("player_pos_f: (%.2f, %.2f) player_pos_i: (%d, %d)\n", vf.x, vf.y, v.x, v.y);
}

