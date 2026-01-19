#include <iostream>
#include "Bullet.h"

    Bullet::Bullet(std::pair<float, float> pos, std::pair<float, float> dir, float spe, CSimpleSprite* spr){
        direction = dir;
        speed = spe;
        sprite = spr;
        sprite->SetPosition(pos.first, pos.second);
    }

    Bullet::~Bullet(){
        delete sprite;
    }

    void Bullet::bullet_update_position(){
        float curr_x, curr_y;
        sprite->GetPosition(curr_x, curr_y);
        curr_x += direction.first * speed;
        curr_y += direction.second * speed;
        sprite->SetPosition(curr_x, curr_y);
    }

    void Bullet::bullet_set_direction(float target_x, float target_y){
        float position_x, position_y;
        sprite->GetPosition(position_x, position_y);
        float dx = target_x - position_x;
        float dy = target_y - position_y;
        float distance = sqrt(dx*dx + dy*dy);
        direction.first = dx / distance;
        direction.second = dy / distance;
    }

    void Bullet::bullet_set_position(float x, float y){
        sprite->SetPosition(x, y);
    }

    void Bullet::bullet_get_position(float &x, float &y){
        sprite->GetPosition(x, y);
    }

    float Bullet::bullet_get_speed(){
        return speed;
    }

    void Bullet::bullet_set_speed(float s){
        speed = s;
    }

