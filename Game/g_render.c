#include "headers/game.h"
#include <stdlib.h>
#include <math.h>

inline void game_render_line(struct Line* line)
{
	render_draw_line_f(line->colour, line->points[0], line->points[1], false);
}

void game_render_object(struct Object* object)
{
	for (int i = 0; i < object->lines_size; i++)
	{
		game_render_line(&object->lines[i]);
	}
}

void game_render_player(const struct Vec2f vf_player_aim_intersect)
{
	//render_draw_circle_f(SOLID_COLOUR(0x0000ff), player.sprite.pos, PLAYER_SIZE, PLAYER_SIZE);

	render_draw_line_f(SOLID_COLOUR(0xff00ff), player.sprite.pos, vf_player_aim_intersect, false);

	render_draw_sprite(player.sprite);
}

void game_render_los(const struct Vec2f* vf_origin)
{	
	/*
	 * Sort intersections by angle(radians).
	 * Triangles will be drawn from origin to every two intersections
	 */
	qsort(scene_objects_intersected_queue, scene_objects_intersected_queue_index, sizeof(struct Vec3f), vector3f_cmp_z);

	//struct Vec2f fov_1, fov_2;
	//double rad = player.sprite.angle + player.sprite.angle_offset;
	//fov_1.x = cos(rad - 0.5f);
	//fov_1.y = sin(rad - 0.5f);
	//fov_2.x = cos(rad + 0.5f);
	//fov_2.y = sin(rad + 0.5f);
	//fov_1 = vector_add(player.sprite.pos, fov_1);
	//fov_2 = vector_add(player.sprite.pos, fov_2);

	struct Vec2f vf0, vf1;
	for (int i = 0, j = 1; i < scene_objects_intersected_queue_index; i++, j++)
	{
		if (j == scene_objects_intersected_queue_index) j = 0;
		//if (j == scene_objects_intersected_queue_index) break;

		uint32 colour_1 = 0xcccccc;
		vf0.x = scene_objects_intersected_queue[i].x;
		vf0.y = scene_objects_intersected_queue[i].y;
		vf1.x = scene_objects_intersected_queue[j].x;
		vf1.y = scene_objects_intersected_queue[j].y;


		/* compare angles */

		//double d1 = vector_dotproduct_perpendicular(fov_1, vf0);
		//double d2 = vector_dotproduct_perpendicular(fov_2, vf0);
		//double d3 = vector_dotproduct_perpendicular(fov_1, vf1);
		//double d4 = vector_dotproduct_perpendicular(fov_2, vf1);

		//if (d1 < 0.0f || d2 > 0.0f || d3 < 0.0f || d4 > 0.0f)
		//{
		//	continue;
		//}

		/* FOV */


		render_draw_triangle(SOLID_COLOUR(0xF5F5DC), *vf_origin, vf0, vf1);
		//render_draw_line_f(SOLID_COLOUR(0xcccccc), *vf_origin, vf0);
		//render_draw_line_f(SOLID_COLOUR(0xff0000), *vf_origin, vf1);
	}
}