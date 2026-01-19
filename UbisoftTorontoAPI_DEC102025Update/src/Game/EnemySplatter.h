#ifndef ENEMYSPLATTER_H
#define ENEMYSPLATTER_H

#include "Enemy.h"

//splattter quickly moves down to the top of screen then starts shooting bullet in all directions
// they are a huge threat if not dealt with quickly

class EnemySplatter : public Enemy {
public:
    EnemySplatter(Position pos, float hp, float spe,
                  Direction target_dir, CSimpleSprite* spr,
                  float shoot_interval);



    void enemy_move() override;
    
    void enemy_shoot(Position target_pos) override;
};

#endif