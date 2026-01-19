#ifndef PLAYER_H
#define PLAYER_H

#include "../ContestAPI/SimpleSprite.h"
#include "BulletManager.h"
#include "Timer.h"

// entity that player controls

class Player{
    public:
        Player(Position pos, CSimpleSprite* spr, int hp, float spd, 
            float shoot_interval, BulletManager* player_bullet_mgr);
        CSimpleSprite* sprite;
        int health;
        float speed;
        float shoot_interval = 0.2f;
        BulletManager* player_bullet_manager;
        Timer* shoot_timer;
        Timer* invincibility_timer;
        bool can_shoot = false;
        bool invincible = false;
        bool invincible_time_up = false;


        ~Player();

        void player_update(float deltaTime); // update player's animation and timer

        void player_shoot(); // let player shoot bullet

        void player_move(float dx, float dy); // move player in the direction of dx, dy

        void player_get_position(float &x, float &y);

        void player_set_position(float x, float y);     

        //void player_get_health(int &hp);

        void player_take_damage(int dmg);

        void player_render(); // render player sprite and its bullets

        bool player_hit_enemy(Position enemy_pos, float radius); // check if any of player's bullets hit the enemy

};

#endif