#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H

#include "g_internal.h"

struct Sprite* game_sprite_create(struct Sprite_Image* sprite_image, float x, float y, float scale);
void game_sprite_destroy(struct Sprite* sprite);
void game_sprite_modify_pos(struct Sprite* sprite, float x, float y);
void game_sprite_modify_pos_offset(struct Sprite* sprite, float x_offset, float y_offset);
void game_sprite_modify_scale(struct Sprite* sprite, float scale);
void game_sprite_modify_angle(struct Sprite* sprite, float angle);
void game_sprite_modify_angle_offset(struct Sprite* sprite, float angle_offset);

#endif