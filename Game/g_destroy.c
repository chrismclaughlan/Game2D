#include "headers/game.h"

void game_destroy(void)
{
	/* Sprites */
	(void)free(enemies);

	/* Sprite Images*/

	window_sprite_image_destroy(sprite_image_soldier);
	window_sprite_image_destroy(sprite_image_enemy);

	/* Scene */

	(void) free(scene_objects_intersected_queue);

	/* Scene - Boundary */
	(void) free(scene_boundary.lines);

	/* Scene - Objects */
	for (int i = 0; i < scene_objects_size; i++)
	{
		(void) free(scene_objects[i].lines);
	}
	(void) free(scene_objects);
}