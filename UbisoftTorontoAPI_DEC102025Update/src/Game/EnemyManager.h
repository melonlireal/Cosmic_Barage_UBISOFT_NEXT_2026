#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "EnemySplatter.h"
#include "EnemyCharger.h"
#include "EnemyMinion.h"

#include "Player.h"
#include "../ContestAPI/SimpleSprite.h"
#include "Timer.h"
//#include <random>

typedef std::vector<Enemy*> EnemyList;

// manager that handles all enemies in the game 
class EnemyManager {
public:
    EnemyList* enemies;
    int splatter_count = 0;
    int charger_count = 0;
    int minion_count = 0;

    EnemyManager();

    ~EnemyManager();

    //void start_spawning();

    //void stop_spawning();

    void spawn_rand_enemy();

    void update_enemies(float deltaTime);

    void render_and_clear_enemies();

    bool check_enemy_player_collisions(Player* player);
    // Other member functions...
    void clear_all_enemies();
};

#endif