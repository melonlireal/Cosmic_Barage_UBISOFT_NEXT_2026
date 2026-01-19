#include "Player.h"

Player::Player(Position pos, CSimpleSprite* spr, int hp, float spd,
    float shoot_interval, BulletManager* player_bullet_mgr){
    sprite = spr;
    health = hp;
    speed = spd;
    sprite->SetPosition(pos.first, pos.second);
    shoot_timer = new Timer(shoot_interval);
    shoot_timer->timer_start();
    invincibility_timer = new Timer(1.0f); // 1 second of invincibility after being hit
    player_bullet_manager = player_bullet_mgr;
}

Player::~Player(){
    delete shoot_timer;
    delete invincibility_timer;
    delete sprite;
}


void Player::player_update(float deltaTime){
    sprite->Update(deltaTime);
    shoot_timer->timer_increment_time(&can_shoot);
    invincibility_timer->timer_increment_time(&invincible_time_up);
    player_bullet_manager->update_bullets();

    if (invincible_time_up){
        invincible = false;
        invincibility_timer->timer_end();
        invincible_time_up = false;
        sprite->SetAnimation(0, true); // back to idle animation
    }

}


void Player::player_shoot(){
    if (!can_shoot){
        return;
    }
    App::PlayAudio("./data/TestData/music/fire.mp3", false);
    can_shoot = false;
    float player_x, player_y;
    player_get_position(player_x, player_y);
    /*
    // I used to make player shoot bu mouse but then it dont feel like a bullet hell game anymore
	float mouse_x, mouse_y;
	App::GetMousePos(mouse_x, mouse_y);
	mouse_y = APP_VIRTUAL_HEIGHT - mouse_y; // have to invert it
	float dx = mouse_x - player_x;
	float dy = mouse_y - player_y;
	float distance = sqrt(dx*dx + dy*dy);
	float normx = dx / distance;
	float normy = dy / distance;
    */
	Direction direction = std::make_pair(0.f, 1.f);
    Position shooter_pos = std::make_pair(player_x, player_y + 30.0f);
        std::string bullet_sprite_path = "./data/TestData/art/bullet.png";
        float sprite_scale = 0.3f;
        float bullet_speed = 15.0f;
        player_bullet_manager->manager_add_bullets(shooter_pos, direction, bullet_sprite_path, sprite_scale, bullet_speed);
}


void Player::player_move(float dx, float dy){
    float x, y;
    sprite->GetPosition(x, y);
    x += dx * speed;
    y += dy * speed;
    sprite->SetPosition(x, y);
}


void Player::player_get_position(float &x, float &y){
    float xpos, ypos;
    sprite->GetPosition(xpos, ypos);
    x = xpos;
    y = ypos;
}

void Player::player_set_position(float x, float y){
    sprite->SetPosition(x, y);
}

void Player::player_take_damage(int dmg){
    if (invincible){
        return;
    }
    /*
    if (App::IsSoundPlaying("./data/TestData//music/player_hurt.wav") == false){
		App::PlayAudio("./data/TestData//music/player_hurt.wav", false);
	}
    */
    health -= dmg;
    if (health < 0){
        health = 0;
    }
    invincibility_timer->timer_start();
    sprite->SetAnimation(1, true); // play hit animation
    invincible = true;
}

void Player::player_render(){
    player_bullet_manager->render_and_clear_bullets();
    sprite->Draw();
}

bool Player::player_hit_enemy(Position enemy_pos, float radius){
    return player_bullet_manager->check_bullet_collisions(enemy_pos, radius);
}