#include "../headers/game.h"
#include "headers/g_player.h"
#include "headers/g_entities.h"
#include "headers/g_scene.h"
#include <stdlib.h>

void game_destroy(void)
{
	/* Player */
	game_sprite_destroy(player->sprite);
	(void)free(player);


	/* Entities - Enemy */
	while (enemy_head != NULL)
	{
		struct Enemy* tmp = enemy_head->next;
		game_entities_enemy_destroy(enemy_head);
		enemy_head = tmp;
	}


	/* Sprite Images*/
	
	window_sprite_image_destroy(sprite_image_soldier);
	window_sprite_image_destroy(sprite_image_enemy);


	/* Scene */

	(void) free(scene_objects_intersected_queue);

	while (scene_objects_head != NULL)
	{
		struct Object* tmp = scene_objects_head->next;
		game_scene_object_destroy(scene_objects_head);
		scene_objects_head = tmp;
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