#ifndef ENEMY_H
#define ENEMY_H

#include "../ContestAPI/SimpleSprite.h"
#include "GameManager.h"
#include "Timer.h"
// enemy entity that attacks the player

class Enemy{
    public:
        float health;
        float speed;
        Direction target_direction;
        CSimpleSprite* sprite;
        Timer *shoot_timer;
        Timer *dead_timer;

        bool collide_able = true;
        bool dead = false;
        bool can_shoot = false;


        Enemy(Position pos,float hp, float spe, \
            Direction target_dir, CSimpleSprite* spr,
            float shoot_interval);

        ~Enemy();

        // move the enemy by dx and dy
        void enemy_update(float deltaTime); // update enemy's animation
        
        virtual void enemy_move();

        virtual void enemy_shoot(Position target_pos);
                
        void enemy_take_damage(float dmg);

        void enemy_get_position(float &x, float &y);

        // useful for teleporting enemy
        void enemy_set_position(float x, float y);

        void enemy_render();

        bool enemy_hit_player(Position player_pos, float radius);


};

#endif