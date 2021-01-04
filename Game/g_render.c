#include "headers/g_render.h"
#include "headers/g_scene.h"
#include "headers/g_player.h"
#include <stdlib.h>
#include <math.h>

inline void game_render_line(struct Line* line)
{
	r_draw_line_f(line->colour, line->start, line->end, false);
}

void game_render_object(struct Object* object)
{
	for (struct Line* line = object->lines_start; line != NULL; line = line->next)
	{
		game_render_line(line);
	}
}

void game_render_player(const struct Vec2f vf_player_aim_intersect)
{
	const struct Vec2f vf_translated = { 
		gp_player->sprite->pos.x + (cos(gp_player->sprite->angle) * gp_player->sprite->pos_offset_x),
		gp_player->sprite->pos.y + (sin(gp_player->sprite->angle) * gp_player->sprite->pos_offset_y)
	};
	r_draw_line_f(SOLID_COLOUR(0xff00ff), vf_translated, vf_player_aim_intersect, false);

	r_draw_sprite(gp_player->sprite);

	r_draw_circle_f(ALPHA_COLOUR_PERCENT(0x0000ff, 0.5f), gp_player->sprite->pos, PLAYER_SIZE, PLAYER_SIZE);
}

void game_render_los(const struct Vec2f* vf_origin)
{	
	/*
	 * Sort intersections by angle(radians).
	 * Triangles will be drawn from origin to every two intersections
	 */
	qsort(g_scene_objects_intersected_queue, g_scene_objects_intersected_queue_index, sizeof(struct Vec3f), u_vector3f_cmp_z);

	//struct Vec2f fov_1, fov_2;
	//double rad = gp_player->sprite->angle + gp_player->sprite->angle_offset;
	//fov_1.x = cos(rad - 0.5f);
	//fov_1.y = sin(rad - 0.5f);
	//fov_2.x = cos(rad + 0.5f);
	//fov_2.y = sin(rad + 0.5f);
	//fov_1 = vector_add(gp_player->sprite->pos, fov_1);
	//fov_2 = vector_add(gp_player->sprite->pos, fov_2);

	struct Vec2f vf0, vf1;
	for (int i = 0, j = 1; i < g_scene_objects_intersected_queue_index; i++, j++)
	{
		if (j == g_scene_objects_intersected_queue_index) j = 0;
		//if (j == g_scene_objects_intersected_queue_index) break;

		uint32 colour_1 = 0xcccccc;
		vf0.x = g_scene_objects_intersected_queue[i].x;
		vf0.y = g_scene_objects_intersected_queue[i].y;
		vf1.x = g_scene_objects_intersected_queue[j].x;
		vf1.y = g_scene_objects_intersected_queue[j].y;


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


		r_draw_triangle(SOLID_COLOUR(0xF5F5DC), *vf_origin, vf0, vf1);
		//r_draw_line_f(SOLID_COLOUR(0xcccccc), *vf_origin, vf0);
		//r_draw_line_f(SOLID_COLOUR(0xff0000), *vf_origin, vf1);
	}
}