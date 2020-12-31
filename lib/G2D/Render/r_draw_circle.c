#include "../headers/render.h"
#include "headers/r_internal.h"

/* Draw Circle */

static void render_draw_circle(uint32 colour,
	struct Vec2 v_origin, int width, int height)
{
	int hh = height * height;
	int ww = width * width;
	int hhww = hh * ww;
	int x0 = width;
	int dx = 0;

	// do the horizontal diameter
	for (int x = -width; x <= width; x++)
		render_draw_point(colour, v_origin.x + x, v_origin.y);

	// now do both halves at the same time, away from the diameter
	for (int y = 1; y <= height; y++)
	{
		int x1 = x0 - (dx - 1);  // try slopes of dx - 1 or more
		for (; x1 > 0; x1--)
			if (x1 * x1 * hh + y * y * ww <= hhww)
				break;
		dx = x0 - x1;  // current approximation of the slope
		x0 = x1;

		for (int x = -x0; x <= x0; x++)
		{
			render_draw_point(colour, v_origin.x + x, v_origin.y - y);
			render_draw_point(colour, v_origin.x + x, v_origin.y + y);
		}
	}
}

void render_draw_circle_f(uint32 colour, struct Vec2f vf_origin,
	float radius_x, float radius_y)
{
	render_draw_circle(colour,
		render_screen_to_px(vf_origin),
		render_coord_translate_from_f_x(radius_x),
		render_coord_translate_from_f_y(radius_y));
}

