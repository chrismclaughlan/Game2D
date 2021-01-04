#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "g_internal.h"

#define PLAYER_SIZE 0.05f

struct Player
{
	//struct Vec2f pos;
	struct Vec2f aim;
	struct G2D_Sprite* sprite;
};


/* Input */

void game_player_input(const float dt);


#endif