#include "headers/g_scene.h"
#include <stdlib.h>

struct Line*
game_scene_line_create(uint32 colour, struct Vec2f start, struct Vec2f end)
{
	struct Line* line;
	line = malloc((sizeof *line));
	if (!line)
	{

		return NULL;
	}
	(void)memset(line, 0, sizeof(struct Line));

	line->colour = colour;
	line->start = start;
	line->end = end;

	return line;
}

void 
game_scene_line_destroy(struct Line* line)
{
	(void)free(line);
}

void 
game_scene_object_move(struct Object* object, struct Vec2f start, struct Vec2f end)
{
	const float diff_x = end.x - start.x;
	const float diff_y = end.y - start.y;

	object->offset_x = diff_x;
	object->offset_y = diff_y;

	//for (struct Line* line = object->lines_start; line != NULL; line = line->next)
	//{
	//	line->start.x += diff_x;
	//	line->start.y += diff_y;
	//	line->end.x += diff_x;
	//	line->end.y += diff_y;
	//}
}

struct Object* 
game_scene_object_create(uint32 colour, struct Vec2f* vertexes, int nvertexes, 
	bool is_collidable, bool is_moveable)
{
	struct Object* object;
	object = malloc((sizeof *object));
	if (!object)
	{

		return NULL;
	}
	(void)memset(object, 0, sizeof(struct Object));


	object->lines_start = game_scene_line_create(
		colour, vertexes[0], vertexes[1]);

	struct Line* line = object->lines_start;
	struct Line* line_prev = NULL;
	for (int i = 1; i < nvertexes; i++)
	{
		int j = (i + 1) < nvertexes ? (i + 1) : 0;

		if (line == NULL)
		{

			(void)free(object);
			/* TODO free all MEMORY LEAK */
			return NULL;
		}

		line->next = game_scene_line_create(
			colour, vertexes[i], vertexes[j]);

		line_prev = line;
		line = line->next;
		line->prev = line_prev;
	}
	object->lines_end = line;

	object->is_collidable = is_collidable;
	object->is_moveable = is_moveable;
	object->offset_x = 0.0f;
	object->offset_y = 0.0f;

	return object;
}

void game_scene_object_destroy(struct Object* object)
{
	while (object->lines_start != NULL)
	{
		struct Line* tmp = object->lines_start->next;
		game_scene_line_destroy(object->lines_start);
		object->lines_start = tmp;
		if (object->lines_start)
			object->lines_start->prev = NULL;
	}
}