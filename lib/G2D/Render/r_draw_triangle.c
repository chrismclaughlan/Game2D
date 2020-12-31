#include "../headers/render.h"
#include "headers/r_internal.h"


/* Draw Triangle */

/**
 * \brief Draws triangle with a flat-top.
 *
 * \see Called by render_draw_triangle_pixels
 */
static void render_draw_triangle_flattop(uint32 colour, struct Vec2 v0,
	struct Vec2 v1, struct Vec2 v2)
{
	//assert(v2.y - v0.y != 0);
	//assert(v2.y - v1.y != 0);
	float invslope1 = (float)(v2.x - v0.x) / (float)(v2.y - v0.y);
	float invslope2 = (float)(v2.x - v1.x) / (float)(v2.y - v1.y);

	float curx1 = (float)v2.x;
	float curx2 = (float)v2.x;

	for (int scanlineY = v2.y; scanlineY <= v0.y; scanlineY++)
	{
		struct Vec2 v0_, v1_;
		v0_.x = curx1; v0_.y = scanlineY;
		v1_.x = curx2; v1_.y = scanlineY;

		render_draw_line_pixels(colour, v0_, v1_);
		curx1 += invslope1;
		curx2 += invslope2;
	}
}

/**
 * \brief Draws triangle with a flat-bottom.
 *
 * \see Called by render_draw_triangle_pixels
 */
static void render_draw_triangle_flatbottom(uint32 colour,
	struct Vec2 v0, struct Vec2 v1, struct Vec2 v2)
{
	//assert(v1.y - v0.y != 0);
	//assert(v2.y - v0.y != 0);
	float invslope1 = (float)(v1.x - v0.x) / (float)(v1.y - v0.y);
	float invslope2 = (float)(v2.x - v0.x) / (float)(v2.y - v0.y);

	float curx1 = (float)v0.x;
	float curx2 = (float)v0.x;

	for (int scanlineY = v0.y; scanlineY >= v1.y; scanlineY--)
	{
		struct Vec2 v0_, v1_;
		v0_.x = curx1; v0_.y = scanlineY;
		v1_.x = curx2; v1_.y = scanlineY;

		render_draw_line_pixels(colour, v0_, v1_);
		curx1 -= invslope1;
		curx2 -= invslope2;
	}
}

/**
 * \brief Draws solid colour triangle.
 *
 * If the given triangle is a flat-top or bottom-top triangle it will draw
 * the corresponding one. If it is neither it must be broken up into these
 * different flat-top and flat-bottom triangles and then draw.
 *
 * \see render_draw_triangle_flattop
 * \see render_draw_triangle_flatbottom
 */
static void render_draw_triangle_pixels(uint32 colour,
	struct Vec2 v0, struct Vec2 v1, struct Vec2 v2)
{
	// Sort ascending by Y
	if (v0.y > v1.y)
	{
		swapi(v0.x, v1.x);
		swapi(v0.y, v1.y);
	}
	if (v1.y > v2.y)
	{
		swapi(v1.x, v2.x);
		swapi(v1.y, v2.y);

		if (v0.y > v1.y)
		{
			swapi(v0.x, v1.x);
			swapi(v0.y, v1.y);
		}
	}

	swapi(v0.x, v2.x);
	swapi(v0.y, v2.y);

	if (v1.y == v2.y)
	{
		render_draw_triangle_flatbottom(colour, v0, v1, v2);
	}
	else if (v0.y == v1.y)
	{
		render_draw_triangle_flattop(colour, v0, v1, v2);
	}
	else
	{
		// Split triangle into flat top and flat bottom
		struct Vec2 v3;
		v3.x = (int)(v0.x + ((float)(v1.y - v0.y) / (float)(v2.y - v0.y)) * (v2.x - v0.x));
		v3.y = v1.y;
		render_draw_triangle_flatbottom(colour, v0, v1, v3);
		render_draw_triangle_flattop(colour, v1, v3, v2);
	}
}

void render_draw_triangle(uint32 colour,
	struct Vec2f vf0, struct Vec2f vf1, struct Vec2f vf2)
{
	struct Vec2 v0, v1, v2;
	v0 = render_screen_to_px(vf0);
	v1 = render_screen_to_px(vf1);
	v2 = render_screen_to_px(vf2);

	render_draw_triangle_pixels(colour, v0, v1, v2);
}
