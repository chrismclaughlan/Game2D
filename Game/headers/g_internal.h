#ifndef GAME_G_H
#define GAME_G_H

#include "../../lib/g2d.h"

#include "g_collisions.h"
#include "g_entities.h"
#include "g_player.h"
#include "g_render.h"
#include "g_resources.h"
#include "g_scene.h"
#include "g_sound.h"
#include "g_sprite.h"
#include "g_utils.h"

/* - - - - - - - - Sound - - - - - - - - */

int g_sound_gun_shot;
int g_sound_gun_cock;
int g_sound_gun_trigger;


/* - - - - - - - - Game Mode - - - - - - - - */

enum Game_Mode
{
	GM_BUILD,
	GM_PLAY,

	GM_COUNT
};

enum Game_Mode g_game_mode;

#define BUILD_SELECTION_CIRCLE_RADIUS 0.02f

struct Vec2f* gp_selection_pos_1;
struct Vec2f* gp_selection_pos_2;
struct Object* gp_selection_object;
struct Vec2f gp_selection_object_start;


/* - - - - - - - - Player - - - - - - - - */

struct G2D_Sprite_Image* gp_sprite_image_soldier;

struct Player* gp_player;


/* - - - - - - - - Entities - - - - - - - - */

struct G2D_Sprite_Image* gp_sprite_image_enemy;

struct Enemy* gp_enemy_head;


/* - - - - - - - - Scene - - - - - - - - */

struct Object* gp_scene_objects_head;
uint g_scene_objects_intersected_queue_index;
struct Vec3f* g_scene_objects_intersected_queue;  /* TODO */

uint g_bullet_holes_index;
struct Vec2f g_bullet_holes[32];  /* TODO */

#endif