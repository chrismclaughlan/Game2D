#ifndef GAME_RENDER_H
#define GAME_RENDER_H

#include "g_internal.h"

inline void game_render_line(struct Line* line);
void		game_render_object(struct Object* object);
void		game_render_player(const struct Vec2f vf_player_aim_intersect);
void		game_render_los(const struct Vec2f* vf_origin);

#endif