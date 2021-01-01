#ifndef GAME_ENTITIES_H
#define GAME_ENTITIES_H

#include "g_internal.h"


#define ENEMY_SIZE 0.02f


struct Circle
{
	struct Vec2f pos;
	float radius;
};


struct Enemy
{
	struct Circle body;  /* TMP: used for hitbox */

	struct Sprite* sprite;  /* use for pos etc. */
	float speed;
	int hp;

	struct Enemy* next;
};

void game_entities_update_positions(double dt);
void game_entities_update_player_interactions(const struct Vec2f const* vf_player_aim_intersect);
void game_entities_render(const struct Object const* starting_object);


struct Enemy* game_entities_enemy_create(float x, float y, float scale, float speed, int hp);
void game_entities_enemy_destroy(struct Enemy* enemy);


#endif