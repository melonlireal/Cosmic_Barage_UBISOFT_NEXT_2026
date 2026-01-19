#include "EnemyCharger.h"

    EnemyCharger::EnemyCharger(Position pos, float hp, float spe,
                  Direction target_dir, CSimpleSprite* spr,
                  float shoot_interval)
        : Enemy(pos, hp, spe, target_dir, spr, shoot_interval) {
        }

    void EnemyCharger::enemy_shoot(Position target_pos) {
        if (!can_shoot) {
            return;
        }
        // Reset shoot flag (important!)
        can_shoot = false;
        
        float enemy_x, enemy_y;
        enemy_get_position(enemy_x, enemy_y);
        Position shooter_pos = std::make_pair(enemy_x, enemy_y);
        Direction dir1 = std::make_pair(1.0f, 0.0f); // Shoot sideways
        Direction dir2 = std::make_pair(-1.0f, 0.0f); // Shoot sideways
        std::string bullet_sprite_path = "./data/TestData/art/chargerbullet.png";
        float sprite_scale = 0.7f;
        float bullet_speed = 1.0f;
        enemy_bullet_manager->manager_add_bullets(shooter_pos, dir1, bullet_sprite_path, sprite_scale, bullet_speed);
        enemy_bullet_manager->manager_add_bullets(shooter_pos, dir2, bullet_sprite_path, sprite_scale, bullet_speed);
    }