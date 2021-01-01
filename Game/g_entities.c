#include "headers/g_entities.h"
#include "headers/g_player.h"
#include "headers/g_scene.h"
#include <math.h>
#include <stdlib.h>

struct Enemy* 
game_entities_enemy_create(float x, float y, float scale, float speed, int hp)
{
	struct Enemy* enemy = malloc(sizeof(struct Enemy));
	if (!enemy)
	{

		return NULL;
	}
	(void)memset(enemy, 0, sizeof(enemy));

	enemy->sprite = game_sprite_create(sprite_image_enemy, x, y, scale);
	if (!enemy->sprite)
	{

		(void)free(enemy);
		return NULL;
	}

	enemy->body.pos = enemy->sprite->pos;
	enemy->body.radius = ENEMY_SIZE;
	enemy->speed = speed;
	enemy->hp = hp;
	enemy->next = NULL;

	return enemy;
}

void 
game_entities_enemy_destroy(struct Enemy* enemy)
{
	game_sprite_destroy(enemy->sprite);
	(void)free(enemy);
}

void game_entities_update_positions(double dt)
{
	for (struct Enemy* enemy = enemy_head; enemy != NULL; enemy = enemy->next)
	{
		if (enemy->hp <= 0) continue;

		struct Vec2f vf_before = enemy->sprite->pos;

		struct Vec2f vf_difference;
		vf_difference = vector_subtract(player->sprite->pos, enemy->sprite->pos);
		vf_difference = vector_normalise(vf_difference);
		if (vector_distance(enemy->sprite->pos, player->sprite->pos) > PLAYER_SIZE)
		{
			enemy->sprite->pos.x += vf_difference.x * enemy->speed * dt;
			enemy->sprite->pos.y += vf_difference.y * enemy->speed * dt;
		}
		
		clampv(enemy->sprite->pos, -1.0f, +1.0f);

		/* Check scene objects collisions */
		for (struct Object* object = scene_objects_head; object != NULL; object = object->next)
		{
			if (game_collision_is_inside_polygon(enemy->sprite->pos, *object))  /* TODO pass pointer */
			{
				enemy->body.pos = vf_before;
				break;
			}
		}

		enemy->body.pos.x = enemy->sprite->pos.x;
		enemy->body.pos.y = enemy->sprite->pos.y;
		enemy->sprite->angle = atan2(0.0f, 1.0f) - atan2(vf_difference.x, vf_difference.y);
	}
}

void game_entities_update_player_interactions(
	const struct Vec2f const* vf_player_aim_intersect)
{
	for (struct Enemy* enemy = enemy_head; enemy != NULL; enemy = enemy->next)
	{
		if (enemy->hp <= 0) continue;

		double distance;
		struct Vec2f vf_circle_intersect_0, vf_circle_intersect_1;
		if (game_collision_circle_and_line(enemy->body, player->sprite->pos,
			*vf_player_aim_intersect, &distance, &vf_circle_intersect_0,
			&vf_circle_intersect_1))
		{
			float chance_to_hit = 0.0f;
			double d0 = vector_distance(player->sprite->pos, *vf_player_aim_intersect);
			double d1 = vector_distance(player->sprite->pos, vf_circle_intersect_0);
			double d2 = vector_distance(player->sprite->pos, vf_circle_intersect_1);
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
			enemy->hp -= enemy->hp * chance_to_hit;
		}
	}
}

void game_entities_render(const struct Object const* starting_object)
{
	for (struct Enemy* enemy = enemy_head; enemy != NULL; enemy = enemy->next)
	{
		uint32 colour = SOLID_COLOUR(0xff0000);
		if (enemy->hp <= 0) colour = SOLID_COLOUR(0x0);

		struct Vec2f intersect;
		if (!game_collision_lines(&player->sprite->pos, &enemy->body.pos, starting_object, &intersect))
		{
			//render_draw_circle_f(colour, enemy->body.pos,
			//	enemy->body.radius, enemy->body.radius);

			render_draw_sprite(enemy->sprite);
		}
	}
}