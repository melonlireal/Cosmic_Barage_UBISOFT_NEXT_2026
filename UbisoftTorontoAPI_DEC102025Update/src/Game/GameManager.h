#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "../ContestAPI/SimpleSprite.h"
#include "BulletManager.h"
#include "Player.h"


extern BulletManager* player_bullet_manager;
extern BulletManager* enemy_bullet_manager;
extern Player* player_entity;
extern int score;

void Game_Manager_Initialize();
#endif