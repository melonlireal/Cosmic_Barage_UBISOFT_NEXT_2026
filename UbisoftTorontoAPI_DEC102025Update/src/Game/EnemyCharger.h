#ifndef ENEMY_CHARGER_H
#define ENEMY_CHARGER_H

#include "Enemy.h"

// charger charge down the screen and launches rocket from both sides
class EnemyCharger : public Enemy {
public:
    EnemyCharger(Position pos, float hp, float spe,
                  Direction target_dir, CSimpleSprite* spr,
                  float shoot_interval);

    void enemy_shoot(Position target_pos) override;
};

#endif 