#include "../headers/render.h"
#include "headers/r_internal.h"


/* Draw Line */

/**
 * \brief Implements Bresenham algorithm for drawing a straight line with
 * pixels.
 *
 * https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 *
 * \param v1 Vec2 to start drawing from
 * \param v2 Vec2 to finish drawing to
 * \param colour colour to draw pixels in line
 */
void render_draw_line_pixels(uint32 colour,
	struct Vec2 v0, struct Vec2 v1)
{
	int dx, sx, dy, sy, err, e2;
	dx = abs(v1.x - v0.x);
	dy = -(abs(v1.y - v0.y));
	if (v0.x < v1.x)
		sx = 1;
	else
		sx = -1;
	if (v0.y < v1.y)
		sy = 1;
	else
		sy = -1;
	err = dx + dy;
	while (true)
	{
		render_draw_point(colour, v0.x, v0.y);

		if (v0.x == v1.x && v0.y == v1.y)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			v0.x += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			v0.y += sy;
		}
	}
}

void render_draw_line_f(uint32 colour, struct Vec2f vf0, struct Vec2f vf1)
{
	render_draw_line_pixels(colour,
		render_screen_to_px(vf0),
		render_screen_to_px(vf1));
}

