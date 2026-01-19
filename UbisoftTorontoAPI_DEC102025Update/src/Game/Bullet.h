#ifndef BULLET_H
#define BULLET_H

#include "../ContestAPI/SimpleSprite.h"

// bullet entity shot by player or enemies
// bullet will automatically rotate its sprite to face its direction of travel

class Bullet{
    public:
        Bullet(std::pair<float, float> pos, std::pair<float, float> dir, float spe, CSimpleSprite* spr);
        std::pair<float, float> direction;
        float speed;
        CSimpleSprite* sprite;

        ~Bullet();

        void bullet_update_position(); // update the bullets position based on its direction and speed

        void bullet_set_direction(float target_x, float target_y);
        // set the bullet's direction towards a target position

        void bullet_set_position(float x, float y); // set the bullet's position

        void bullet_get_position(float &x, float &y); // get the bullet's position

        float bullet_get_speed();  // get the bullet's speed

        void bullet_set_speed(float s); // set the bullet's speed

};

#endif