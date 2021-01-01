#ifndef GAME_G_H
#define GAME_G_H

#include "../../lib/G2D/headers/g2d.h"

#include "g_collisions.h"
#include "g_entities.h"
#include "g_player.h"
#include "g_render.h"
#include "g_resources.h"
#include "g_scene.h"
#include "g_sprite.h"
#include "g_utils.h"


/* - - - - - - - - Game Mode - - - - - - - - */

enum Game_Mode
{
	GM_BUILD,
	GM_PLAY,

	GM_COUNT
};

enum Game_Mode game_mode;

#define BUILD_SELECTION_CIRCLE_RADIUS 0.02f

struct Vec2f* selection_pos_1;
struct Vec2f* selection_pos_2;


/* - - - - - - - - Player - - - - - - - - */

struct Sprite_Image* sprite_image_soldier;

struct Player* player;


/* - - - - - - - - Entities - - - - - - - - */

struct Sprite_Image* sprite_image_enemy;

struct Enemy* enemy_head;


/* - - - - - - - - Scene - - - - - - - - */

struct Object* scene_objects_head;
uint scene_objects_intersected_queue_index;
struct Vec3f* scene_objects_intersected_queue;

uint bullet_holes_index;
struct Vec2f bullet_holes[32];

#endif