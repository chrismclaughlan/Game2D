#include "headers/game.h"
#include <math.h>
#include <stdlib.h>


static void game_bullet_holes_place(struct Vec2f vf)
{
	bullet_holes[bullet_holes_index % (sizeof(bullet_holes) / sizeof(bullet_holes[0]))] = vf;
	bullet_holes_index++;
}

static void game_bullet_holes_render()
{
	for (int i = 0; i < sizeof(bullet_holes) && i < bullet_holes_index; i++)
	{
		render_draw_circle_f(SOLID_COLOUR(0x0), bullet_holes[i], 0.005f, 0.005f);
	}
}


void game_simulate()
{
	const float dt = g2d_window->fps_last_dt;
	uint32 colour_background = SOLID_COLOUR(0x000000);
	uint32 colour_enemy = SOLID_COLOUR(0xff0000);

	/* - - - - - - - - Input - - - - - - - - */

	const struct Vec2f mouse_pos = window_input_mouse_get_screen_coords();

	if (PRESSED(BUTTON_1)) game_mode = GM_BUILD;
	if (PRESSED(BUTTON_2)) game_mode = GM_PLAY;
	if (IS_DOWN(BUTTON_3)) colour_background = SOLID_COLOUR(0x0000ff);
	if (IS_DOWN(BUTTON_4)) colour_background = SOLID_COLOUR(0xffffff);

	switch (game_mode)
	{
	case GM_BUILD:
	{
		if (RELEASED(BUTTON_LMOUSE))
		{
			selection_pos_1 = NULL;
			selection_pos_2 = NULL;
		}
		else if (PRESSED(BUTTON_LMOUSE))
		{
			/* does this intersect with line circle? */
			for (int i = 0; i < scene_objects_size; i++)
			{
				for (int j = 0; j < scene_objects[i].lines_size; j++)
				{
					if (game_collision_is_in_circle(mouse_pos, scene_objects[i].lines[j].points[0], BUILD_SELECTION_CIRCLE_RADIUS))
					{
						if (PRESSED(BUTTON_LMOUSE))
						{
							//scene_objects[i].lines[j].points[0] = pos;
							//scene_objects[i].lines[(j - 1 < 0) ? scene_objects[i].lines_size - 1 : j - 1].points[1] = pos;
							selection_pos_1 = &scene_objects[i].lines[j].points[0];
							selection_pos_2 = &scene_objects[i].lines[(j - 1 < 0) ? scene_objects[i].lines_size - 1 : j - 1].points[1];
						}
					}

				}
			}
		}
	} break;
	case GM_PLAY:
	{
		/* Player aim */
		player.aim = mouse_pos;

		/* Player movement */
		struct Vec2f vf_before = player.sprite.pos;
		const double multiplier = 1.0f;
		if (IS_DOWN(BUTTON_W) || IS_DOWN(BUTTON_UP))	player.sprite.pos.y += multiplier * dt;
		if (IS_DOWN(BUTTON_A) || IS_DOWN(BUTTON_LEFT))	player.sprite.pos.x -= multiplier * dt;
		if (IS_DOWN(BUTTON_S) || IS_DOWN(BUTTON_DOWN))	player.sprite.pos.y -= multiplier * dt;
		if (IS_DOWN(BUTTON_D) || IS_DOWN(BUTTON_RIGHT)) player.sprite.pos.x += multiplier * dt;

		clampv(player.sprite.pos, -1.0f, +1.0f);

		for (int i = 0; i < scene_objects_size; i++)
		{
			if (is_inside_polygon(player.sprite.pos, scene_objects[i]))
			{
				player.sprite.pos = vf_before;
				break;
			}
		}

		player.sprite.angle = vector_angle(game_utils_get_vector_up(), vector_subtract(player.aim, player.sprite.pos));

		/* Enemies movement */
		game_entities_update_positions(dt);

	} break;
	}


	/* - - - - - - - - Simulate - - - - - - - - */

	/* Scene collisions */
	struct Vec2f* vf_origin = &player.sprite.pos;
	struct Object* starting_object = &scene_boundary;
	scene_objects_intersected_queue_index = 0;
	game_collision_update_los(vf_origin, starting_object);

	
	/* Player aim scene collisions */
	struct Vec2f vf_player_aim_intersect;
	if (!collision_lines(&player.sprite.pos, &player.aim, starting_object, &vf_player_aim_intersect))
		vf_player_aim_intersect = player.aim;


	switch (game_mode)
	{
	case GM_BUILD:
	{
		if (selection_pos_1 && selection_pos_2) {
			*selection_pos_1 = mouse_pos;
			*selection_pos_2 = mouse_pos;
		}
	} break;
	case GM_PLAY:
	{
		if (PRESSED(BUTTON_LMOUSE))
		{
			double d_ = vector_distance(player.aim, vf_player_aim_intersect);
			if (d_ == 0.0f)  /* test if aim blocked by object */
			{
				game_entities_update_player_interactions(&vf_player_aim_intersect);

				game_bullet_holes_place(vf_player_aim_intersect);
			}
		}
	} break;
	}


	/* - - - - - - - - Render - - - - - - - - */

	render_clear_screen(colour_background);

	game_render_los(vf_origin);

	game_render_object(&scene_boundary);
	game_render_object(&scene_objects[0]);
	game_render_object(&scene_objects[1]);

	game_render_player(vf_player_aim_intersect);

	game_entities_render(starting_object);
	game_bullet_holes_render();

	switch (game_mode)
	{
	case GM_BUILD:
	{
		/* does this intersect with line circle? */
		struct Vec2f pos = window_input_mouse_get_screen_coords();
		for (int i = 0; i < scene_objects_size; i++)
		{
			for (int j = 0; j < scene_objects[i].lines_size; j++)
			{
				render_draw_circle_f(SOLID_COLOUR(0xcccccc), scene_objects[i].lines[j].points[0],
					BUILD_SELECTION_CIRCLE_RADIUS, BUILD_SELECTION_CIRCLE_RADIUS);
			}
		}

		if (selection_pos_1)
		{
			render_draw_circle_f(SOLID_COLOUR(0xffffff), *selection_pos_1,
				BUILD_SELECTION_CIRCLE_RADIUS, BUILD_SELECTION_CIRCLE_RADIUS);
		}
	} break;
	}
}