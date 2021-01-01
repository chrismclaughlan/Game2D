#ifndef G2D_RENDER_H
#define G2D_RENDER_H

//#include "../game2d.h"
#include "g2d.h"
#include <math.h>

//struct Game2D_Renderer
//{
//
//};

#define SOLID_COLOUR(c) (c | 0xff000000)

extern void render_clear_screen	(uint32 colour);
extern void render_draw_point_f	(uint32 colour, struct Vec2f vf);
extern void render_draw_rect	(uint32 colour, struct Vec2f vf0, float half_width, float half_height);
extern void render_draw_line_f	(uint32 colour, struct Vec2f vf0, struct Vec2f vf1);
extern void render_draw_triangle(uint32 colour, struct Vec2f vf0, struct Vec2f vf1, struct Vec2f vf2);
extern void render_draw_circle_f(uint32 colour, struct Vec2f vf_origin, float radius_x, float radius_y);
//extern void render_draw_rect_pixels(uint32 colour, uint x0, uint y0, uint x1, uint y1);


extern inline float render_coord_translate_from_i_x(int i);
extern inline float render_coord_translate_from_i_y(int i);
extern inline int	render_coord_translate_from_f_x(float f);
extern inline int	render_coord_translate_from_f_y(float f);
extern struct Vec2	render_screen_to_px(struct Vec2f vf);
extern struct Vec2f render_px_to_screen(struct Vec2 v);

/* Sprite */
extern void render_draw_sprite(struct Sprite* sprite);

#endif