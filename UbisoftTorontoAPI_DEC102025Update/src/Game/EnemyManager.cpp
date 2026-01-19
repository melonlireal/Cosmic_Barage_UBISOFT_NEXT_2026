#include "EnemyManager.h"
    
enum which_enemy {
    ENEMY_MINION = 0,
    ENEMY_CHARGER = 1,
    ENEMY_SPLATTER = 2
};

    EnemyManager::EnemyManager() {
        enemies = new EnemyList();
    }

    EnemyManager::~EnemyManager() {
        clear_all_enemies();
        delete enemies;
    }

    void EnemyManager::spawn_rand_enemy() {
        // Placeholder implementation for random enemy spawning

        float spawn_x = static_cast<float>(std::rand() % static_cast<int>(APP_VIRTUAL_WIDTH));
        float spawn_y = 900.0f; // Spawn at the top of the screen
        Position spawn_pos = std::make_pair(spawn_x, spawn_y);

        Enemy* newEnemy = nullptr;
        int enemy_type;
        // limit splatter count to 3 for game balance
        if (splatter_count >= 3) {
            enemy_type = std::rand() % 2;
        }else{
            enemy_type = std::rand() % 3;
        }
        
        if (enemy_type == ENEMY_SPLATTER) {
            CSimpleSprite* sprite = App::CreateSprite("./data/TestData/art/splatter_sprite_sheet.png", 5, 2);
            sprite->SetScale(1.0f);
            sprite->CreateAnimation(0, 0.05f, {0, 1, 2, 3, 4}); // Idle animation
            sprite->CreateAnimation(1, 0.1f, {5, 6, 7, 8, 9}); // Death animation
            sprite->SetAnimation(0, true); // Start with idle animation

            float health = 10.0f;
            float speed = 5.0f;
            
            Direction target_dir = std::make_pair(0.f, -1.f);
            float shoot_interval = 3.0f;
            newEnemy = new EnemySplatter(spawn_pos, health, 
                speed, target_dir, sprite, shoot_interval);
            
            splatter_count++;
        } else if (enemy_type == ENEMY_CHARGER) {
            CSimpleSprite* sprite = App::CreateSprite("./data/TestData/art/charger_sprite_sheet.png", 5, 2);
            sprite->SetScale(1.0f);
            sprite->CreateAnimation(0, 0.05f, {0, 1, 2, 3, 4}); // Idle animation
            sprite->CreateAnimation(1, 0.1f, {5, 6, 7, 8, 9}); // Death animation
            sprite->SetAnimation(0, true); // Start with idle animation
            float health = 5.0f;
            float speed = 10.0f;
            
            Direction target_dir = std::make_pair(0.f, -1.f);
            float shoot_interval = 0.1f;
            newEnemy = new EnemyCharger(spawn_pos, health, 
                speed, target_dir, sprite, shoot_interval);
            charger_count++;

        } else if (enemy_type == ENEMY_MINION) {
            // Spawn EnemyMinion            
            CSimpleSprite* sprite = App::CreateSprite("./data/TestData/art/minion_sprite_sheet.png", 5, 2);
            sprite->SetScale(0.6f);
            sprite->CreateAnimation(0, 0.05f, {0, 1, 2, 3, 4}); // Idle animation
            sprite->CreateAnimation(1, 0.05f, {5, 6, 7, 8, 9}); // Death animation
            sprite->SetAnimation(0, true); // Start with idle animation
            float health = 3.0f;
            float speed = 2.0f;
            
            Direction target_dir = std::make_pair(0.f, -1.f);
            float shoot_interval = 3.0f;            
            newEnemy = new EnemyMinion(spawn_pos, health, 
                speed, target_dir, sprite, shoot_interval);
            minion_count++;
        }
        enemies->push_back(newEnemy);

        return;
    }

    void EnemyManager::update_enemies(float deltaTime) {
        for (Enemy* enemy : *enemies) {
            enemy->enemy_update(deltaTime);
        }
    }

    void EnemyManager::render_and_clear_enemies() {
    size_t write_index = 0;
    
    for (size_t read_index = 0; read_index < enemies->size(); read_index++) {
        Enemy* enemy = (*enemies)[read_index];
        float x, y;
        enemy->enemy_get_position(x, y);
        
        // Check if enemy is below y = -200
        if (y >= -200.0f) {
            enemy->enemy_render();
            // render enemy above y = -200
            // Move enemy index to keep position
            if (write_index != read_index) {
                (*enemies)[write_index] = enemy;
            }
            write_index++;
        } else {
            // Delete enemy that is below y = -200
            
            EnemySplatter* splatter = dynamic_cast<EnemySplatter*>(enemy);
            EnemyCharger* charger = dynamic_cast<EnemyCharger*>(enemy);
            EnemyMinion* minion = dynamic_cast<EnemyMinion*>(enemy);
            
            if (splatter != nullptr) {
                splatter_count--;
            } else if (charger != nullptr) {
                charger_count--;
            } else if (minion != nullptr) {
                minion_count--;
            }
            delete enemy;
        }
    }
    // Resize vector to remove deleted enemies
    enemies->resize(write_index);
    }

    bool EnemyManager::check_enemy_player_collisions(Player* player) {
        for (Enemy* enemy : *enemies) {
            float player_x, player_y;
            player->player_get_position(player_x, player_y);
            Position player_pos = std::make_pair(player_x, player_y);
            if (enemy->enemy_hit_player(player_pos, 50.0f)) {
                enemy->enemy_take_damage(9999.0f); // kill the enemy
                return true;
            }
        }
        return false;
    }

    void EnemyManager::clear_all_enemies() {
        for (Enemy* enemy : *enemies) {
            // delete all enemies
            delete enemy;
        }
        enemies->clear();
        splatter_count = 0;
        charger_count = 0;
        minion_count = 0;
    }