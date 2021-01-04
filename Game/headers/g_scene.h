#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "g_internal.h"


struct Line
{
	uint32 colour;
	//struct Vec2f points[2];

	struct Vec2f start;
	struct Vec2f end;

	struct Line* next;
	struct Line* prev;
};


struct Object
{
	struct Line* lines_start;
	struct Line* lines_end;

	struct Object* next;

	bool is_collidable;
};



struct Line*	game_scene_line_create(uint32 colour, struct Vec2f start, struct Vec2f end);
void			game_scene_line_destroy(struct Line* line);
struct Object*	game_scene_object_create(uint32 colour, struct Vec2f* vertexes, int nvertexes, bool is_collidable);
void			game_scene_object_destroy(struct Object* object);



#endif