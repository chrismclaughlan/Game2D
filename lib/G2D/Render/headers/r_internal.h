#ifndef G2D_RENDER_INTERNAL_H
#define G2D_RENDER_INTERNAL_H

#include "../../render.h"

void r_draw_point(uint32 colour, int x0, int y0);
void r_draw_line_pixels(uint32 colour, struct Vec2 v0, struct Vec2 v1);

#endif