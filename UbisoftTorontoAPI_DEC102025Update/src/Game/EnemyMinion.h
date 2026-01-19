#ifndef ENEMYMINION_H
#define ENEMYMINION_H

#include "Enemy.h"


// minion that moves down the screen and slowly shoots at players direction
// their bullerts move slowly and they have low health
class EnemyMinion : public Enemy {
public:
    EnemyMinion(Position pos, float hp, float spe,
                  Direction target_dir, CSimpleSprite* spr,
                  float shoot_interval);

    void enemy_shoot(Position target_pos) override;
};

#endif