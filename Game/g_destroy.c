#include "../game.h"
#include "headers/g_player.h"
#include "headers/g_entities.h"
#include "headers/g_scene.h"
#include <stdlib.h>

void game_destroy(void)
{
	/* Sound */

	(void)w_win32_sound_destroy(g_sound_gun_shot);
	(void)w_win32_sound_destroy(g_sound_gun_cock);
	(void)w_win32_sound_destroy(g_sound_gun_trigger);


	/* Player */
	game_sprite_destroy(gp_player->sprite);
	(void)free(gp_player);


	/* Entities - Enemy */
	while (gp_enemy_head != NULL)
	{
		struct Enemy* tmp = gp_enemy_head->next;
		game_entities_enemy_destroy(gp_enemy_head);
		gp_enemy_head = tmp;
	}


	/* Sprite Images*/
	
	w_win32_sprite_image_destroy(gp_sprite_image_soldier);
	w_win32_sprite_image_destroy(gp_sprite_image_enemy);


	/* Scene */

	(void) free(g_scene_objects_intersected_queue);

	while (gp_scene_objects_head != NULL)
	{
		struct Object* tmp = gp_scene_objects_head->next;
		game_scene_object_destroy(gp_scene_objects_head);
		gp_scene_objects_head = tmp;
	}

	///* Scene - Boundary */
	//(void) free(scene_boundary.lines);

	///* Scene - Objects */
	//for (int i = 0; i < scene_objects_size; i++)
	//{
	//	(void) free(scene_objects[i].lines);
	//}
	//(void) free(scene_objects);
}