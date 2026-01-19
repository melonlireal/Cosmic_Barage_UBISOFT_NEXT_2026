
#include <iostream>
#include "../ContestAPI/app.h"
#include "Enemy.h"

Enemy::Enemy(Position pos,float hp, float spe,
    Direction target_dir, CSimpleSprite* spr, 
    float shoot_interval) {

    health = hp;
    speed = spe;
    target_direction = target_dir;
    sprite = spr;
    sprite->SetPosition(pos.first, pos.second);

    shoot_timer = new Timer(shoot_interval); // enemy can shoot every 2 seconds
    shoot_timer->timer_start();
    dead_timer = new Timer(0.2f); // 0.5 second death animation
}

Enemy::~Enemy(){
    delete shoot_timer;
    delete dead_timer;
    delete sprite;
}

void Enemy::enemy_update(float deltaTime){
    sprite->Update(deltaTime);

    if (dead){
        enemy_set_position(-300.0f, -300.0f);
    }

    shoot_timer->timer_increment_time(&can_shoot);
    dead_timer->timer_increment_time(&dead);
    enemy_bullet_manager->update_bullets();
    if (can_shoot){
        float player_x, player_y;
        player_entity->player_get_position(player_x, player_y);
        enemy_shoot(std::make_pair(player_x, player_y)); // shoot towards player base
    }
    enemy_move();
}

void Enemy::enemy_move(){
    float x, y;
    sprite->GetPosition(x, y);
    x += target_direction.first * speed;
    y += target_direction.second * speed;
    sprite->SetPosition(x, y);
}

void Enemy::enemy_shoot(Position target_pos =  std::make_pair(0.f, 0.f)){
    return; // do nothing as this method is supposed to be overwrite
}

void Enemy::enemy_take_damage(float dmg){
    if (!collide_able){
        return;
    }
    health -= dmg;
    if (health < 0){
        health = 0;
        collide_able = false;
        score += 100;
        sprite->SetAnimation(1, true); // play death animation
        dead_timer->timer_start();
    }
}

void Enemy::enemy_get_position(float &x, float &y){
    sprite->GetPosition(x, y);
}


void Enemy::enemy_set_position(float x, float y){
    sprite->SetPosition(x, y);
}

void Enemy::enemy_render(){
    enemy_bullet_manager->render_and_clear_bullets();
    sprite->Draw();
}

bool Enemy::enemy_hit_player(Position player_pos, float radius){
    float enemy_x, enemy_y;
    enemy_get_position(enemy_x, enemy_y);
    if (fabs(enemy_x - player_pos.first) < radius && fabs(enemy_y - player_pos.second) < radius){
        return true;
    }
    return false;
}
