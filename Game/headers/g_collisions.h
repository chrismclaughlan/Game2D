#ifndef GAME_COLLISIONS_H
#define GAME_COLLISIONS_H

#include "g_internal.h"

bool game_collision_is_inside_polygon(struct Vec2f point, struct Object object);
int game_collision_lines(const struct Vec2f* vf_origin, const struct Vec2f* vf_ray, const struct Object* starting_object, struct Vec2f* vf_intersect);
void game_collision_update_los(const struct Vec2f* vf_origin, const struct Object const* starting_object);
bool game_collision_is_in_circle(struct Vec2f vf_origin, struct Vec2f vf_target, float radius);
bool game_collision_circle_and_line(struct Circle C, struct Vec2f A, struct Vec2f B, double* distance, struct Vec2f* F, struct Vec2f* G);

#endif