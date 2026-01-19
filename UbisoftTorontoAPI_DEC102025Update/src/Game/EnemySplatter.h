#ifndef ENEMYSPLATTER_H
#define ENEMYSPLATTER_H

#include "Enemy.h"

class EnemySplatter : public Enemy {
public:
    EnemySplatter(Position pos, float hp, float spe,
                  Direction target_dir, CSimpleSprite* spr,
                  float shoot_interval);



    void enemy_move() override;
    
    void enemy_shoot(Position target_pos) override;
};

#endif