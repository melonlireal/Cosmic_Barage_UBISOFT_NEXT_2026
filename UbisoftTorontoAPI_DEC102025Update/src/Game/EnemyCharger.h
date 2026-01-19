#ifndef ENEMY_CHARGER_H
#define ENEMY_CHARGER_H

#include "Enemy.h"

class EnemyCharger : public Enemy {
public:
    EnemyCharger(Position pos, float hp, float spe,
                  Direction target_dir, CSimpleSprite* spr,
                  float shoot_interval);

    void enemy_shoot(Position target_pos) override;
};

#endif 