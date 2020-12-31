#ifndef GAME_H
#define GAME_H

//#include "../utils.h"
#include "../G2D/g2d.h"


/* Globals */

#define CMAKE_BUILD
#ifdef CMAKE_BUILD
#define TEXTURE_PLAYER "..\\resources\\soldier.bmp"
#define TEXTURE_ENEMY "..\\resources\\enemy.bmp"
#else
#define TEXTURE_PLAYER "resources\\soldier.bmp"
#define TEXTURE_ENEMY "resources\\enemy.bmp"
#endif

#define PLAYER_SIZE 0.02f
#define ENEMY_SIZE 0.02f

#define BUILD_SELECTION_CIRCLE_RADIUS 0.02f

/* Sprite Images */

enum Game_Mode
{
	GM_BUILD,
	GM_PLAY,

	GM_COUNT
};

struct Player
{
	//struct Vec2f pos;
	struct Vec2f aim;
	struct Sprite sprite;
};

struct Line
{
	uint32 colour;
	struct Vec2f points[2];
};

struct Object
{
	uint lines_size;
	struct Line* lines;
	struct Object* next;
};

struct Circle
{
	struct Vec2f pos;
	float radius;
};

struct Enemy
{
	struct Circle body;  /* TMP: used for hitbox */

	struct Sprite sprite;  /* use for pos etc. */
	float speed;
	int hp;
};


/* Utils */

struct Vec2f game_utils_get_vector_up(void);


/* Enemy */

void game_entities_update_positions(double dt);
void game_entities_update_player_interactions(
	const struct Vec2f const* vf_player_aim_intersect);
void game_entities_render(const struct Object const* starting_object);


/* Input */

void game_player_input(const float dt);


/* Collision */

int collision_lines(const struct Vec2f* vf_origin, const struct Vec2f* vf_ray,
	const struct Object* starting_object, struct Vec2f* vf_intersect);
void game_collision_update_los(const struct Vec2f* vf_origin, const struct Object const* starting_object);
bool game_collision_is_in_circle(struct Vec2f vf_origin, struct Vec2f vf_target, float radius);
bool game_collision_circle_and_line(struct Circle C, struct Vec2f A,
	struct Vec2f B, double* distance, struct Vec2f* F, struct Vec2f* G);

/* Render */

inline void game_render_line(struct Line* line);
void game_render_object(struct Object* object);
void game_render_player(const struct Vec2f vf_player_aim_intersect);
void game_render_los(const struct Vec2f* vf_origin);


/* game.h */

enum Game_Mode game_mode;
struct Vec2f* selection_pos_1;
struct Vec2f* selection_pos_2;

struct Sprite_Image* sprite_image_soldier;
struct Sprite_Image* sprite_image_enemy;

struct Player player;
uint enemies_size;
struct Enemy* enemies;

uint bullet_holes_index;
struct Vec2f bullet_holes[32];

struct Object scene_boundary;
uint scene_objects_size;
struct Object* scene_objects;
uint scene_objects_intersected_queue_index;
struct Vec3f* scene_objects_intersected_queue;

void game_init(void);
void game_simulate(void);
void game_destroy(void);

#endif