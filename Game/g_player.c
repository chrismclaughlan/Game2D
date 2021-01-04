#include "headers/g_player.h"
#include <math.h>


void game_player_input(const float dt)
{

	/*
	
	IDEA:

	get vector to new pos
	see if this new vector intersects with scenery
	
	*/


	//struct Vec2f vf_before = gp_player->sprite->pos;

	//const double multiplier = 1.0f;
	//if (IS_DOWN(BUTTON_W) || IS_DOWN(BUTTON_UP))	gp_player->sprite->pos.y += multiplier * dt;
	//if (IS_DOWN(BUTTON_A) || IS_DOWN(BUTTON_LEFT))	gp_player->sprite->pos.x -= multiplier * dt;
	//if (IS_DOWN(BUTTON_S) || IS_DOWN(BUTTON_DOWN))	gp_player->sprite->pos.y -= multiplier * dt;
	//if (IS_DOWN(BUTTON_D) || IS_DOWN(BUTTON_RIGHT)) gp_player->sprite->pos.x += multiplier * dt;

	//gp_player->aim = window_input_mouse_get_screen_coords();

	//clampv(gp_player->sprite->pos, -1.0f, +1.0f);

	//for (int i = 0; i < scene_objects_size; i++)
	//{
	//	if (game_collision_is_inside_polygon(gp_player->sprite->pos, scene_objects[i]))
	//	{
	//		gp_player->sprite->pos = vf_before;
	//		break;
	//	}
	//}
}