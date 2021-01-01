#include "../headers/game.h"
#include "headers/g_resources.h"
#include "headers/g_player.h"
#include "headers/g_entities.h"
#include "headers/g_scene.h"
#include <stdlib.h>


void game_init()
{
	/* Input */

	gp_g2d_input->allow_typing = false;
	gp_g2d_input->mouse_raw_input = false;


	/* Game Modes */

	game_mode = GM_BUILD;
	selection_pos_1 = NULL;
	selection_pos_2 = NULL;


	/* Load sprite images */
	sprite_image_soldier = window_sprite_image_load(RESOURCE_PLAYER);
	if (!sprite_image_soldier)
	{
		Sleep(5000);
		exit(1);
	}
	sprite_image_enemy = window_sprite_image_load(RESOURCE_ENEMY);
	if (!sprite_image_enemy)
	{
		Sleep(5000);
		exit(1);
	}


	player = malloc(sizeof(struct Player));
	if (!player)
	{
		LOG_ERROR("player = malloc()\n");
		return;
	}
	(void)memset(player, 0, sizeof(struct Player));
	
	player->sprite = game_sprite_create(sprite_image_soldier, 0.0f, 0.0f, 0.4f);
	if (!player->sprite)
	{
		LOG_ERROR("game_sprite_create\n");
		return;
	}
	game_sprite_modify_pos_offset(player->sprite, 0.2f, 0.2f);
	game_sprite_modify_angle_offset(player->sprite, PI / 2.0f);



	/* Player */

	player->aim.x = 0.0f;
	player->aim.y = 0.0f;


	/* Enemy */

	//enemies_size = 5;
	//enemies = malloc(sizeof(struct Enemy*) * enemies_size);
	//if (enemies == NULL)
	//{
	//	LOG_ERROR("malloc()"); exit(1);
	//}

	//const int enemy_hp = 100;
	//const float enemy_scale = 2.0f;
	//for (int i = 0; i < enemies_size; i++)
	//{
	//	const enemy_pos_x = 0.1f * (float)(i + 1);
	//	const enemy_pos_y = 0.1f * (float)(i + 1);
	//	const float enemy_speed = 0.1f * (float)(i + 1);

	//	enemies[i] = game_entities_enemy_create(
	//		enemy_pos_x, enemy_pos_y, 
	//		enemy_scale,
	//		enemy_speed, enemy_hp);
	//	if (!enemies[i])
	//	{
	//		LOG_ERROR("Failed to create enemy\n");
	//		return;
	//	}

	//	//game_sprite_modify_pos_offset(enemies[i]->sprite, 0.2f, 0.2f);
	//	//game_sprite_modify_angle_offset(enemies[i]->sprite, PI / 2.0f);
	//}

	enemy_head = game_entities_enemy_create(0.0f, 0.0f, 2.0f, 0.1f, 100);
	struct Enemy* enemy = enemy_head;
	for (int i = 0; i < 5; i++)
	{
		enemy->next = game_entities_enemy_create(
			0.1f * (i + 1), 0.1f * (i + 1), 
			2.0f, 0.1f * (i + 1), 100);
		if (!enemy->next)
		{
			LOG_ERROR("game_entities_enemy_create()\n");
			exit(1);
		}

		enemy = enemy->next;
	}


	/* Scene */

	bullet_holes_index = 0;
	memset(bullet_holes, 0, sizeof(bullet_holes));


	/* Scene - LOS */
	scene_objects_intersected_queue_index = 0;
	scene_objects_intersected_queue = malloc(sizeof(struct Vec3f) * 128);
	if (scene_objects_intersected_queue == NULL)
	{
		LOG_ERROR("malloc()"); 
		exit(1);
	}


	struct Vec2f vertexes[4];
	vertexes[0].x = -1.0f; vertexes[0].y = -1.0f;
	vertexes[1].x = -1.0f; vertexes[1].y = +1.0f;
	vertexes[2].x = +1.0f; vertexes[2].y = +1.0f;
	vertexes[3].x = +1.0f; vertexes[3].y = -1.0f;
	scene_objects_head = game_scene_object_create(
		SOLID_COLOUR(0xF5F5DC), vertexes, sizeof(vertexes) / sizeof(vertexes[0]));
	if (!scene_objects_head)
	{
		LOG_ERROR("game_scene_object_create()\n");
		exit(1);
	}

	struct Object* object = scene_objects_head;
	for (int i = 1; i < 4; i++)
	{
		vertexes[0].x = 0.1f * (float)i; vertexes[0].y = +0.1f * (float)i;
		vertexes[1].x = 0.1f * (float)i; vertexes[1].y = +0.2f * (float)i;
		vertexes[2].x = 0.2f * (float)i; vertexes[2].y = +0.2f * (float)i;
		vertexes[3].x = 0.2f * (float)i; vertexes[3].y = +0.1f * (float)i;
		object->next = game_scene_object_create(SOLID_COLOUR(0xF5F5DC),
			vertexes, sizeof(vertexes) / sizeof(vertexes[0]));

		if (!object->next)
		{
			LOG_ERROR("game_scene_object_create()\n");
			exit(1);
		}

		object = object->next;
	}
}
