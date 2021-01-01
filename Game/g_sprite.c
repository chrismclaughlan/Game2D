#include "headers/g_sprite.h"
#include <stdlib.h>

struct Sprite* 
game_sprite_create(struct Sprite_Image* sprite_image, float x, float y, 
	float scale)
{
	struct Sprite* sprite = malloc(sizeof(struct Sprite));
	if (!sprite)
	{

		return NULL;
	}
	(void) memset(sprite, 0, sizeof(struct Sprite));

	sprite->sprite_image = sprite_image;
	sprite->pos.x = x; sprite->pos.y = y;
	sprite->scale = scale;
	
	return sprite;
}

void 
game_sprite_destroy(struct Sprite* sprite)
{
	(void)free(sprite);
}

void 
game_sprite_modify_pos(struct Sprite* sprite, float x, float y)
{
	sprite->pos.x = x; sprite->pos.y = y;
}

void 
game_sprite_modify_pos_offset(struct Sprite* sprite, float x_offset, 
	float y_offset)
{
	sprite->pos_offset_x = x_offset; sprite->pos_offset_y = y_offset;
}

void 
game_sprite_modify_scale(struct Sprite* sprite, float scale)
{
	sprite->scale = scale;
}

void 
game_sprite_modify_angle(struct Sprite* sprite, float angle)
{
	sprite->angle = angle;
}

void 
game_sprite_modify_angle_offset(struct Sprite* sprite, float angle_offset)
{
	sprite->angle_offset = angle_offset;
}