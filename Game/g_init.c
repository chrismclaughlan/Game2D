#include "../game.h"
#include "headers/g_resources.h"
#include "headers/g_player.h"
#include "headers/g_entities.h"
#include "headers/g_scene.h"
#include <stdlib.h>


void game_init()
{
	/* Sound */

	g_sound_gun_shot = w_win32_sound_create("gun_shot");
	g_sound_gun_cock = w_win32_sound_create("gun_cock");
	g_sound_gun_trigger = w_win32_sound_create("gun_trigger");


	/* Input */

	gp_g2d_input->allow_typing = false;
	gp_g2d_input->mouse_raw_input = false;


	/* Game Modes */

	// g_game_mode = GM_BUILD;  // BROKEN
	g_game_mode = GM_PLAY;
	gp_selection_pos_1 = NULL;
	gp_selection_pos_2 = NULL;
	gp_selection_object = NULL;


	/* Load sprite images */
	//char* resource_dirs[]	;// = (char* []){ "hello", "world" };

	char* resource_dirs[] = { "../resources/", "resources/" };
	gp_sprite_image_soldier = w_win32_sprite_image_load("soldier.bmp", resource_dirs, sizeof(resource_dirs) / sizeof(*resource_dirs));
	if (!gp_sprite_image_soldier)
	{
		Sleep(5000);
		exit(1);
	}
	gp_sprite_image_enemy = w_win32_sprite_image_load("enemy.bmp", resource_dirs, sizeof(resource_dirs) / sizeof(*resource_dirs));
	if (!gp_sprite_image_enemy)
	{
		Sleep(5000);
		exit(1);
	}


	gp_player = malloc((sizeof *gp_player));
	if (!gp_player)
	{
		LOG_ERROR("gp_player = malloc()\n");
		return;
	}
	(void)memset(gp_player, 0, sizeof(struct Player));
	
	gp_player->sprite = game_sprite_create(gp_sprite_image_soldier, 0.0f, 0.0f, 2.0f);
	if (!gp_player->sprite)
	{
		LOG_ERROR("game_sprite_create\n");
		return;
	}
	game_sprite_modify_pos_offset(gp_player->sprite, 0.05f, 0.05f);
	game_sprite_modify_angle_offset(gp_player->sprite, PI / 2.0f);



	/* Player */

	gp_player->aim.x = 0.0f;
	gp_player->aim.y = 0.0f;


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

	gp_enemy_head = game_entities_enemy_create(0.0f, 0.0f, 2.0f, 0.1f, 100);
	struct Enemy* enemy = gp_enemy_head;
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

	g_bullet_holes_index = 0;
	memset(g_bullet_holes, 0, sizeof(g_bullet_holes));


	/* Scene - LOS */
	g_scene_objects_intersected_queue_index = 0;
	g_scene_objects_intersected_queue = malloc((sizeof *g_scene_objects_intersected_queue) * 128);
	if (g_scene_objects_intersected_queue == NULL)
	{
		LOG_ERROR("malloc()"); 
		exit(1);
	}


	struct Vec2f vertexes[4];
	vertexes[0].x = -1.0f; vertexes[0].y = -1.0f;
	vertexes[1].x = -1.0f; vertexes[1].y = +1.0f;
	vertexes[2].x = +1.0f; vertexes[2].y = +1.0f;
	vertexes[3].x = +1.0f; vertexes[3].y = -1.0f;
	gp_scene_objects_head = game_scene_object_create(
		SOLID_COLOUR(0xF5F5DC), vertexes, sizeof(vertexes) / sizeof(vertexes[0]), false, false);
	if (!gp_scene_objects_head)
	{
		LOG_ERROR("game_scene_object_create()\n");
		exit(1);
	}

	struct Object* object = gp_scene_objects_head;
	for (int i = 1; i < 4; i++)
	{
		vertexes[0].x = 0.1f * (float)i; vertexes[0].y = +0.1f * (float)i;
		vertexes[1].x = 0.1f * (float)i; vertexes[1].y = +0.2f * (float)i;
		vertexes[2].x = 0.2f * (float)i; vertexes[2].y = +0.2f * (float)i;
		vertexes[3].x = 0.2f * (float)i; vertexes[3].y = +0.1f * (float)i;
		object->next = game_scene_object_create(SOLID_COLOUR(0xF5F5DC),
			vertexes, sizeof(vertexes) / sizeof(vertexes[0]), true, true);

		if (!object->next)
		{
			LOG_ERROR("game_scene_object_create()\n");
			exit(1);
		}

		object = object->next;
	}
}
