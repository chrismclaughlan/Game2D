#include "game.h"
#include <math.h>

void game_entities_update_positions(double dt)
{
	for (int i = 0; i < enemies_size; i++)
	{
		if (enemies[i].hp <= 0) continue;

		struct Vec2f vf_before = enemies[i].body.pos;

		struct Vec2f vf_difference;
		vf_difference = vector_subtract(player.sprite.pos, enemies[i].body.pos);
		vf_difference = vector_normalise(vf_difference);
		if (vector_distance(enemies[i].body.pos, player.sprite.pos) > PLAYER_SIZE)
		{
			enemies[i].body.pos.x += vf_difference.x * enemies[i].speed * dt;
			enemies[i].body.pos.y += vf_difference.y * enemies[i].speed * dt;
		}
		
		clampv(enemies[i].body.pos, -1.0f, +1.0f);

		/* Check scene objects collisions */
		for (int j = 0; j < scene_objects_size; j++)
		{
			if (is_inside_polygon(enemies[i].body.pos, scene_objects[j]))
			{
				enemies[i].body.pos = vf_before;
				break;
			}
		}

		enemies[i].sprite.pos.x = enemies[i].body.pos.x;
		enemies[i].sprite.pos.y = enemies[i].body.pos.y;
		enemies[i].sprite.angle = atan2(0.0f, 1.0f) - atan2(vf_difference.x, vf_difference.y);
	}
}

void game_entities_update_player_interactions(
	const struct Vec2f const* vf_player_aim_intersect)
{
	for (int i = 0; i < enemies_size; i++)
	{
		if (enemies[i].hp <= 0) continue;

		double distance;
		struct Vec2f vf_circle_intersect_0, vf_circle_intersect_1;
		if (game_collision_circle_and_line(enemies[i].body, player.sprite.pos,
			*vf_player_aim_intersect, &distance, &vf_circle_intersect_0,
			&vf_circle_intersect_1))
		{
			float chance_to_hit = 0.0f;
			double d0 = vector_distance(player.sprite.pos, *vf_player_aim_intersect);
			double d1 = vector_distance(player.sprite.pos, vf_circle_intersect_0);
			double d2 = vector_distance(player.sprite.pos, vf_circle_intersect_1);
			if (d0 < d1)
			{
				/* miss -> vf_player_aim_intersect INFRONT of target */
				chance_to_hit = 0.5f - (d1 - d0);
			}
			else if (d0 > d2)
			{
				/* miss -> vf_player_aim_intersect BEHIND of target */
				chance_to_hit = 0.5f - (d0 - d2);
			}
			else
			{
				/* HIT */
				chance_to_hit = 1.0f;
			}

			chance_to_hit = clamp(chance_to_hit, 0.0f, 1.0f);
			LOG_DEBUG("chance to hit: %f\n", chance_to_hit);
			enemies[i].hp -= enemies[i].hp * chance_to_hit;
		}
	}
}

void game_entities_render(const struct Object const* starting_object)
{
	for (int i = 0; i < enemies_size; i++)
	{
		uint32 colour = SOLID_COLOUR(0xff0000);
		if (enemies[i].hp <= 0) colour = SOLID_COLOUR(0x0);

		//for (int i = 0; i < enemies_size; i++)
		//{
			struct Vec2f intersect;
			if (!collision_lines(&player.sprite.pos, &enemies[i].body.pos, starting_object, &intersect))
			{
				//render_draw_circle_f(colour, enemies[i].body.pos,
				//	enemies[i].body.radius, enemies[i].body.radius);

				render_draw_sprite(enemies[i].sprite);
			}
			//render_draw_sprite(enemies[i].sprite);
		//}
	}
}