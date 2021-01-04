#include "../render.h"
#include "headers/r_internal.h"


/* Draw Point */

static inline uint32 
alpha_blend(uint32 c_src, uint32 c_dst, float alpha)
{
	return (uint32)((float)c_src * alpha) + ((1.0f - alpha) * (float)c_dst);
}

void 
r_draw_point(uint32 colour, int x0, int y0)
{
	if (x0 < 0 || x0 >= gp_g2d_window->width || y0 < 0 || y0 >= gp_g2d_window->height)
	{
		return;
	}

	const float alpha = ((float)(colour & 0xff000000) / (float)0xff000000);
	uint32 colour_new = 0;
	//colour_new |= (uint32)alpha_blend((colour & 0xff0000) >> 16, (g2d_window->p_buffer[x0 + (y0 * g2d_window->width)] & 0xff0000) >> 16, alpha) << 16;
	//colour_new |= (uint32)alpha_blend((colour & 0x00ff00) >> 8, (g2d_window->p_buffer[x0 + (y0 * g2d_window->width)] & 0x00ff00) >> 8, alpha) << 8;
	//colour_new |= (uint32)alpha_blend(colour & 0x0000ff, g2d_window->p_buffer[x0 + (y0 * g2d_window->width)] & 0x0000ff, alpha) << 0;
	colour_new |= 0xff0000 & alpha_blend(colour & 0xff0000, gp_g2d_window->p_buffer[x0 + (y0 * gp_g2d_window->width)] & 0xff0000, alpha);
	colour_new |= 0x00ff00 & alpha_blend(colour & 0x00ff00, gp_g2d_window->p_buffer[x0 + (y0 * gp_g2d_window->width)] & 0x00ff00, alpha);
	colour_new |= 0x0000ff & alpha_blend(colour & 0x0000ff, gp_g2d_window->p_buffer[x0 + (y0 * gp_g2d_window->width)] & 0x0000ff, alpha);
	gp_g2d_window->p_buffer[x0 + (y0 * gp_g2d_window->width)] = colour_new;
}

void 
r_draw_point_f(uint32 colour, struct Vec2f vf)
{
	struct Vec2 v = r_screen_to_px(vf);
	r_draw_point(colour, v.x, v.y);
}
