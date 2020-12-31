#include "headers/game.h"
#include <math.h>

bool is_inside_polygon(struct Vec2f point, struct Object object)
{
	bool c = false;

	for (int i = 0, j = object.lines_size - 1; i < object.lines_size; j = i++) {
		if (((object.lines[i].points[0].y > point.y) != (object.lines[j].points[0].y > point.y)) &&
			(point.x < (object.lines[j].points[0].x - object.lines[i].points[0].x) * (point.y - object.lines[i].points[0].y) / (object.lines[j].points[0].y - object.lines[i].points[0].y) + object.lines[i].points[0].x))
			c = !c;
	}
	return c;
}

void game_player_input(const float dt)
{

	/*
	
	IDEA:

	get vector to new pos
	see if this new vector intersects with scenery
	
	*/


	//struct Vec2f vf_before = player.sprite.pos;

	//const double multiplier = 1.0f;
	//if (IS_DOWN(BUTTON_W) || IS_DOWN(BUTTON_UP))	player.sprite.pos.y += multiplier * dt;
	//if (IS_DOWN(BUTTON_A) || IS_DOWN(BUTTON_LEFT))	player.sprite.pos.x -= multiplier * dt;
	//if (IS_DOWN(BUTTON_S) || IS_DOWN(BUTTON_DOWN))	player.sprite.pos.y -= multiplier * dt;
	//if (IS_DOWN(BUTTON_D) || IS_DOWN(BUTTON_RIGHT)) player.sprite.pos.x += multiplier * dt;

	//player.aim = window_input_mouse_get_screen_coords();

	//clampv(player.sprite.pos, -1.0f, +1.0f);

	//for (int i = 0; i < scene_objects_size; i++)
	//{
	//	if (is_inside_polygon(player.sprite.pos, scene_objects[i]))
	//	{
	//		player.sprite.pos = vf_before;
	//		break;
	//	}
	//}
}