#include "../game.h"
#include "headers/g_internal.h"
#include "headers/g_scene.h"
#include "headers/g_player.h"
#include "headers/g_utils.h"
#include <math.h>
#include <stdlib.h>


static void game_bullet_holes_place(struct Vec2f vf)
{
	g_bullet_holes[g_bullet_holes_index % (sizeof(g_bullet_holes) / sizeof(g_bullet_holes[0]))] = vf;
	g_bullet_holes_index++;
}

static void game_bullet_holes_render()
{
	for (int i = 0; i < (sizeof g_bullet_holes) / sizeof(*g_bullet_holes) && i < g_bullet_holes_index; i++)
	{
		r_draw_circle_f(SOLID_COLOUR(0x0), g_bullet_holes[i], 0.005f, 0.005f);
	}
}


void game_simulate()
{
	const float dt = gp_g2d_window->fps_last_dt;
	uint32 colour_background = SOLID_COLOUR(0x000000);
	uint32 colour_enemy = SOLID_COLOUR(0xff0000);

	/* - - - - - - - - Input - - - - - - - - */

	const struct Vec2f mouse_pos = window_input_mouse_get_screen_coords();

	if (PRESSED(BUTTON_1)) g_game_mode = GM_BUILD;
	if (PRESSED(BUTTON_2)) g_game_mode = GM_PLAY;

	switch (g_game_mode)
	{
	case GM_BUILD:
	{
		if (RELEASED(BUTTON_LMOUSE))
		{
			gp_selection_pos_1 = NULL;
			gp_selection_pos_2 = NULL;

			/* TODO create new object when moving polygon (delete etc.) */
			gp_selection_object->offset_x = 0.0f;
			gp_selection_object->offset_y = 0.0f;
			gp_selection_object = NULL;
		}
		else if (PRESSED(BUTTON_LMOUSE))
		{
			/* does this intersect with line circle? */
			for (struct Object* object = gp_scene_objects_head; object != NULL; object = object->next)
			{
				if (!object->is_moveable)
				{
					continue;
				}

				if (game_collision_is_inside_polygon(mouse_pos, object))
				{
					/* Move object entirely */
					LOG_DEBUG("clicked inside object\n");
					gp_selection_object = object;
					gp_selection_object_start = mouse_pos;
					break;
				}
				else
				{
					for (struct Line* line = object->lines_start; line != NULL; line = line->next)
					{
						if (game_collision_is_in_circle(mouse_pos, line->start, BUILD_SELECTION_CIRCLE_RADIUS))
						{
							if (PRESSED(BUTTON_LMOUSE))
							{

					/* Move object vertex */

								//scene_objects[i].lines[j].points[0] = pos;
								//scene_objects[i].lines[(j - 1 < 0) ? scene_objects[i].lines_size - 1 : j - 1].points[1] = pos;
								gp_selection_pos_1 = &line->start;
								if (line->prev)
								{
									gp_selection_pos_2 = &line->prev->end;
								}
								else
								{
									gp_selection_pos_2 = &object->lines_end->end;
								}
								break;
							}
						}
					}
				}
			}
		}
	} break;
	case GM_PLAY:
	{
		/* Player aim */
		gp_player->aim = mouse_pos;

		/* Player movement */
		struct Vec2f vf_before = gp_player->sprite->pos;
		const double multiplier = 1.0f;
		if (IS_DOWN(BUTTON_W) || IS_DOWN(BUTTON_UP))	gp_player->sprite->pos.y += multiplier * dt;
		if (IS_DOWN(BUTTON_A) || IS_DOWN(BUTTON_LEFT))	gp_player->sprite->pos.x -= multiplier * dt;
		if (IS_DOWN(BUTTON_S) || IS_DOWN(BUTTON_DOWN))	gp_player->sprite->pos.y -= multiplier * dt;
		if (IS_DOWN(BUTTON_D) || IS_DOWN(BUTTON_RIGHT)) gp_player->sprite->pos.x += multiplier * dt;

		clampv(gp_player->sprite->pos, -1.0f, +1.0f);

		for (struct Object* object = gp_scene_objects_head; object != NULL; object = object->next)
		{
			if (object->is_collidable && game_collision_is_inside_polygon(gp_player->sprite->pos, object))
			{
				gp_player->sprite->pos = vf_before;
				break;
			}
		}

		gp_player->sprite->angle = u_vector_angle(game_utils_get_vector_up(), u_vector_subtract(gp_player->aim, gp_player->sprite->pos));

		/* Enemies movement */
		game_entities_update_positions(dt);

	} break;
	}


	/* - - - - - - - - Simulate - - - - - - - - */

	/* Scene collisions */
	struct Vec2f* vf_origin = &gp_player->sprite->pos;
	g_scene_objects_intersected_queue_index = 0;
	game_collision_update_los(vf_origin, gp_scene_objects_head);

	
	/* Player aim scene collisions */
	struct Vec2f vf_player_aim_intersect;
	if (!game_collision_lines(&gp_player->sprite->pos, &gp_player->aim, gp_scene_objects_head, &vf_player_aim_intersect))
		vf_player_aim_intersect = gp_player->aim;


	switch (g_game_mode)
	{
	case GM_BUILD:
	{
		if (gp_selection_pos_1 && gp_selection_pos_2) {
			*gp_selection_pos_1 = mouse_pos;
			*gp_selection_pos_2 = mouse_pos;
		}

		if (gp_selection_object)
		{
			game_scene_object_move(gp_selection_object, gp_selection_object_start, mouse_pos);
		}
	} break;
	case GM_PLAY:
	{
		if (PRESSED(BUTTON_LMOUSE))
		{
			if (!w_win32_sound_play(g_sound_gun_shot))
			{
				LOG_ERROR("w_win32_sound_play()\n");
			}

			double d_ = u_vector_distance(gp_player->aim, vf_player_aim_intersect);
			if (d_ == 0.0f)  /* test if aim blocked by object */
			{
				game_entities_update_player_interactions(&vf_player_aim_intersect);

				game_bullet_holes_place(vf_player_aim_intersect);
			}
		}

		if (PRESSED(BUTTON_RMOUSE))
		{
			if (!w_win32_sound_play(g_sound_gun_cock))
			{
				LOG_ERROR("w_win32_sound_play()\n");
			}
		}
	} break;
	}


	/* - - - - - - - - Render - - - - - - - - */

	r_clear_screen(colour_background);

	game_render_los(vf_origin);



	for (struct Object* object = gp_scene_objects_head; object != NULL; object = object->next)
	{
		game_render_object(object);
	}
	//game_render_object(&scene_boundary);
	//game_render_object(&scene_objects[0]);
	//game_render_object(&scene_objects[1]);

	game_render_player(vf_player_aim_intersect);

	game_entities_render(gp_scene_objects_head);
	game_bullet_holes_render();

	switch (g_game_mode)
	{
	case GM_BUILD:
	{
		/* does this intersect with line circle? */
		//struct Vec2f pos = window_input_mouse_get_screen_coords();
		for (struct Object* object = gp_scene_objects_head; object != NULL; object = object->next)
		{
			for (struct Line* line = object->lines_start; line != NULL; line = line->next)
			{
				r_draw_circle_f(SOLID_COLOUR(0xcccccc), line->start,
					BUILD_SELECTION_CIRCLE_RADIUS, BUILD_SELECTION_CIRCLE_RADIUS);
			}
		}

		if (gp_selection_pos_1)
		{
			r_draw_circle_f(SOLID_COLOUR(0xffffff), *gp_selection_pos_1,
				BUILD_SELECTION_CIRCLE_RADIUS, BUILD_SELECTION_CIRCLE_RADIUS);
		}
	} break;
	}
}