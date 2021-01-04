#ifndef G2D_RENDER_H
#define G2D_RENDER_H

#include "../g2d.h"
#include <math.h>


#define SOLID_COLOUR(c) (c | 0xff000000)
#define ALPHA_COLOUR(c, a) ((c & 0xffffff) | (a << 24))
#define ALPHA_COLOUR_PERCENT(c, a) ALPHA_COLOUR(c, (int)(a * 255))


extern void r_clear_screen	(uint32 colour);


/* - - - - Draw - - - - */

extern void r_draw_point_f	(uint32 colour, struct Vec2f vf);
extern void r_draw_rect	(uint32 colour, struct Vec2f vf0, float half_width, float half_height);
extern void r_draw_line_f	(uint32 colour, struct Vec2f vf0, struct Vec2f vf1);
extern void r_draw_triangle(uint32 colour, struct Vec2f vf0, struct Vec2f vf1, struct Vec2f vf2);
extern void r_draw_circle_f(uint32 colour, struct Vec2f vf_origin, float radius_x, float radius_y);
extern void r_draw_sprite(struct G2D_Sprite* sprite);
//extern void render_draw_rect_pixels(uint32 colour, uint x0, uint y0, uint x1, uint y1);


/* - - - - Translate - - - - */

extern inline float r_coord_translate_from_i_x(int i);
extern inline float r_coord_translate_from_i_y(int i);
extern inline int	r_coord_translate_from_f_x(float f);
extern inline int	r_coord_translate_from_f_y(float f);
extern struct Vec2	r_screen_to_px(struct Vec2f vf);
extern struct Vec2f r_px_to_screen(struct Vec2 v);


#endif