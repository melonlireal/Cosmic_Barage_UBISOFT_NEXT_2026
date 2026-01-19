#include "GameManager.h"

BulletManager* player_bullet_manager = nullptr;
BulletManager* enemy_bullet_manager = nullptr;
Player* player_entity = nullptr;
int score = 0;

void Game_Manager_Initialize() {

    player_bullet_manager =  new BulletManager();
    enemy_bullet_manager = new BulletManager();

    CSimpleSprite* player_sprite = App::CreateSprite("./data/TestData/art/player_sprite_sheet.png", 5, 2);
    player_sprite->SetScale(0.5f);
    player_sprite->CreateAnimation(0, 0.05f, {0, 1, 2, 3, 4}); // idle animation
    player_sprite->CreateAnimation(1, 0.05f, {5, 6, 7, 8, 9}); // hit animation
    player_sprite->SetAnimation(0, true); // start with idle animation
    Position player_pos = std::make_pair(APP_VIRTUAL_WIDTH/2.f, -190.f); //hide player offscreen initially
    float player_speed = 10.0f;
    int player_health = 5;
    float player_shoot_interval = 0.1f;
    player_entity = new Player(player_pos, player_sprite, player_health, player_speed, player_shoot_interval, player_bullet_manager);
    // player still needs to have its bullet manager assigned as it is declared here unlike enemys
}