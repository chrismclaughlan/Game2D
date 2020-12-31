//#include "../utils.h"
#include "game.h"
#include <stdlib.h>

#define PROCESS_LINE(l, c, ax, ay, bx, by)\
l.colour = c;\
l.points[0].x = ax;\
l.points[0].y = ay;\
l.points[1].x = bx;\
l.points[1].y = by;

#define INIT_OBJECTS(o, n)\


#define INIT_LINES(l, n)\
l = malloc(sizeof(struct Line) * n);\
scene_boundary.lines_size = n;

void game_init()
{
	/* Game Modes */

	game_mode = GM_BUILD;
	selection_pos_1 = NULL;
	selection_pos_2 = NULL;


	/* Load sprite images */
	sprite_image_soldier = window_sprite_image_load(TEXTURE_PLAYER);
	if (!sprite_image_soldier)
	{
		Sleep(5000);
		exit(1);
	}
	sprite_image_enemy = window_sprite_image_load(TEXTURE_ENEMY);
	if (!sprite_image_enemy)
	{
		Sleep(5000);
		exit(1);
	}


	/* Load sprites */
	player.sprite.sprite_image = sprite_image_soldier;
	player.sprite.pos.x = 0.0f;
	player.sprite.pos.y = 0.0f;
	player.sprite.pos_offset_x = 0.2f;
	player.sprite.pos_offset_y = 0.2f;
	player.sprite.scale = 0.4f;
	player.sprite.angle = 0.0f;
	player.sprite.angle_offset = PI / 2.0f;


	/* Input */

	g2d_input->allow_typing = false;
	g2d_input->mouse_raw_input = false;


	/* Player */

	player.aim.x = 0.0f;
	player.aim.y = 0.0f;


	/* Enemy */

	enemies_size = 5;
	enemies = malloc(sizeof(struct Enemy) * enemies_size);
	if (enemies == NULL)
	{
		LOG_ERROR("malloc()"); exit(1);
	}

	enemies[0].body.pos.x = 0.1f;
	enemies[0].body.pos.y = 0.1f;
	enemies[0].body.radius = ENEMY_SIZE;
	enemies[0].speed = 0.1f;
	enemies[0].hp = 100;
	enemies[0].sprite.sprite_image = sprite_image_soldier;
	enemies[0].sprite.pos.x = 0.0f;
	enemies[0].sprite.pos.y = 0.0f;
	enemies[0].sprite.pos_offset_x = 0.2f;
	enemies[0].sprite.pos_offset_y = 0.2f;
	enemies[0].sprite.scale = 0.4f;
	enemies[0].sprite.angle = 0.0f;
	enemies[0].sprite.angle_offset = PI / 2.0f;

	enemies[1].body.pos.x = 0.2f;
	enemies[1].body.pos.y = 0.2f;
	enemies[1].body.radius = ENEMY_SIZE;
	enemies[1].speed = 0.2f;
	enemies[1].hp = 100;
	enemies[1].sprite.sprite_image = sprite_image_soldier;
	enemies[1].sprite.pos.x = 0.0f;
	enemies[1].sprite.pos.y = 0.0f;
	enemies[1].sprite.pos_offset_x = 0.2f;
	enemies[1].sprite.pos_offset_y = 0.2f;
	enemies[1].sprite.scale = 0.4f;
	enemies[1].sprite.angle = 0.0f;
	enemies[1].sprite.angle_offset = PI / 2.0f;

	enemies[2].body.pos.x = 0.3f;
	enemies[2].body.pos.y = 0.3f;
	enemies[2].body.radius = ENEMY_SIZE;
	enemies[2].speed = 0.3f;
	enemies[2].hp = 100;
	enemies[2].sprite.sprite_image = sprite_image_enemy;
	enemies[2].sprite.pos.x = 0.0f;
	enemies[2].sprite.pos.y = 0.0f;
	enemies[2].sprite.pos_offset_x = 0.0f;
	enemies[2].sprite.pos_offset_y = 0.0f;
	enemies[2].sprite.scale = 2.0f;
	enemies[2].sprite.angle = 0.0f;
	enemies[2].sprite.angle_offset = 0.0f;

	enemies[3].body.pos.x = 0.4f;
	enemies[3].body.pos.y = 0.4f;
	enemies[3].body.radius = ENEMY_SIZE;
	enemies[3].speed = 0.4f;
	enemies[3].hp = 100;
	enemies[3].sprite.sprite_image = sprite_image_enemy;
	enemies[3].sprite.pos.x = 0.0f;
	enemies[3].sprite.pos.y = 0.0f;
	enemies[3].sprite.pos_offset_x = 0.0f;
	enemies[3].sprite.pos_offset_y = 0.0f;
	enemies[3].sprite.scale = 2.0f;
	enemies[3].sprite.angle = 0.0f;
	enemies[3].sprite.angle_offset = 0.0f;

	enemies[4].body.pos.x = 0.5f;
	enemies[4].body.pos.y = 0.5f;
	enemies[4].body.radius = ENEMY_SIZE;
	enemies[4].speed = 0.5f;
	enemies[4].hp = 100;
	enemies[4].sprite.sprite_image = sprite_image_enemy;
	enemies[4].sprite.pos.x = 0.0f;
	enemies[4].sprite.pos.y = 0.0f;
	enemies[4].sprite.pos_offset_x = 0.0f;
	enemies[4].sprite.pos_offset_y = 0.0f;
	enemies[4].sprite.scale = 2.0f;
	enemies[4].sprite.angle = 0.0f;
	enemies[4].sprite.angle_offset = 0.0f;


	/* Scene */

	bullet_holes_index = 0;
	memset(bullet_holes, 0, sizeof(bullet_holes));

	scene_objects_intersected_queue_index = 0;
	scene_objects_intersected_queue = malloc(sizeof(struct Vec3f) * 128);
	if (scene_objects_intersected_queue == NULL)
	{
		LOG_ERROR("malloc()"); exit(1);
	}

	/* Scene - Boundary*/
	scene_boundary.lines_size = 4;
	scene_boundary.lines = malloc(sizeof(struct Line) * scene_boundary.lines_size);
	PROCESS_LINE(scene_boundary.lines[0], SOLID_COLOUR(0xffffff), -1.0f, -1.0f, -1.0f, +1.0f);//-0.9f, -0.9f, -0.9f, +0.9f);  /* Left */
	PROCESS_LINE(scene_boundary.lines[1], SOLID_COLOUR(0xffffff), -1.0f, +1.0f, +1.0f, +1.0f);//-0.9f, +0.9f, +0.9f, +0.9f);  /* Top */
	PROCESS_LINE(scene_boundary.lines[2], SOLID_COLOUR(0xffffff), +1.0f, +1.0f, +1.0f, -1.0f);//+0.9f, +0.9f, +0.9f, -0.9f);  /* Right */
	PROCESS_LINE(scene_boundary.lines[3], SOLID_COLOUR(0xffffff), +1.0f, -1.0f, -1.0f, -1.0f);//+0.9f, -0.9f, -0.9f, -0.9f);  /* Bottom */

	/* Scene - Objects */
	scene_objects_size = 2;
	scene_objects = malloc(sizeof(struct Object) * scene_objects_size);
	if (scene_objects == NULL)
	{
		LOG_ERROR("malloc()"); exit(1);
	}

	/* Scene - Objects - 0*/
	scene_objects[0].lines = malloc(sizeof(struct Line) * 5);
	if (scene_objects[0].lines == NULL)
	{
		LOG_ERROR("malloc()"); exit(1);
	}

	scene_objects[0].lines_size = 5;
	PROCESS_LINE(scene_objects[0].lines[0], SOLID_COLOUR(0xffffff), -0.2f, -0.2f, -0.2f, -0.1f);  /* Left */
	PROCESS_LINE(scene_objects[0].lines[1], SOLID_COLOUR(0xffffff), -0.2f, -0.1f, -0.1f, -0.1f);  /* Top */
	PROCESS_LINE(scene_objects[0].lines[2], SOLID_COLOUR(0xffffff), -0.1f, -0.1f, -0.1f, -0.2f);  /* Right */
	PROCESS_LINE(scene_objects[0].lines[3], SOLID_COLOUR(0xffffff), -0.1f, -0.2f, -0.15f, -0.3f);  /* Bottom */
	PROCESS_LINE(scene_objects[0].lines[4], SOLID_COLOUR(0xffffff), -0.15f, -0.3f, -0.2f, -0.2f);  /* Bottom */

	/* Scene - Objects - 1*/
	scene_objects[1].lines = malloc(sizeof(struct Line) * 4);
	if (scene_objects[1].lines == NULL)
	{
		LOG_ERROR("malloc()"); exit(1);
	}

	scene_objects[1].lines_size = 4;
	PROCESS_LINE(scene_objects[1].lines[0], SOLID_COLOUR(0xffffff), +0.2f, +0.2f, +0.2f, +0.1f);  /* Left */
	PROCESS_LINE(scene_objects[1].lines[1], SOLID_COLOUR(0xffffff), +0.2f, +0.1f, +0.1f, +0.1f);  /* Top */
	PROCESS_LINE(scene_objects[1].lines[2], SOLID_COLOUR(0xffffff), +0.1f, +0.1f, +0.1f, +0.2f);  /* Right */
	PROCESS_LINE(scene_objects[1].lines[3], SOLID_COLOUR(0xffffff), +0.1f, +0.2f, +0.2f, +0.2f);  /* Bottom */


	/* Link all objects */
	scene_boundary.next = &scene_objects[0];
	scene_objects[0].next = &scene_objects[1];
	scene_objects[1].next = NULL;
}
