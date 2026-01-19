#ifndef ENEMYMINION_H
#define ENEMYMINION_H

#include "Enemy.h"

class EnemyMinion : public Enemy {
public:
    EnemyMinion(Position pos, float hp, float spe,
                  Direction target_dir, CSimpleSprite* spr,
                  float shoot_interval);

    void enemy_shoot(Position target_pos) override;
};

#endif