#include "headers/g_scene.h"
#include <stdlib.h>

struct Line*
game_scene_line_create(uint32 colour, struct Vec2f start, struct Vec2f end)
{
	struct Line* line = malloc(sizeof(struct Line));
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

struct Object* 
game_scene_object_create(uint32 colour, struct Vec2f* vertexes, int nvertexes)
{
	struct Object* object = malloc(sizeof(struct Object));
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

void game_scene_add_object_rect(struct Vec2f vf, float size)
{
	//struct Object* object;
	//float left, top, right, bottom;
	//left	= vf.x - size;
	//top		= vf.y + size;
	//right	= vf.x + size;
	//bottom	= vf.y - size;

	//left	= clamp(left, -1.0f, 1.0f);
	//top		= clamp(top, -1.0f, 1.0f);
	//right	= clamp(right, -1.0f, 1.0f);
	//bottom	= clamp(bottom, -1.0f, 1.0f);

	//object.lines = malloc(sizeof(struct Line)
	//{

	//};))
	//object.lines[0].points = 
}