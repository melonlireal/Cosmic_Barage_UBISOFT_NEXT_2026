#include "EnemySplatter.h"

    EnemySplatter::EnemySplatter(Position pos, float hp, float spe,
                  Direction target_dir, CSimpleSprite* spr,
                  float shoot_interval)
        : Enemy(pos, hp, spe, target_dir, spr, shoot_interval) {
        // Base class constructor handles initialization
    }

    void EnemySplatter::enemy_move() {
        float enemy_x, enemy_y;
        enemy_get_position(enemy_x, enemy_y);
        enemy_x += target_direction.first * speed;
        enemy_y += target_direction.second * speed;
        if (enemy_y < 600.0f) {
            return; // stop moving after a height is reached
        }
        enemy_set_position(enemy_x, enemy_y);
    }

    void EnemySplatter::enemy_shoot(Position target_pos) {
        if (!can_shoot) {
            return;
        }
        // Reset shoot flag (important!)
        can_shoot = false;
        
        float enemy_x, enemy_y;
        enemy_get_position(enemy_x, enemy_y);
        Position shooter_pos = std::make_pair(enemy_x, enemy_y);

        int angles = 20; // will shoot in 20 angles
        for (int i = 0; i < angles; i++) {
            float angle_rad = (2.0f * PI * i) / angles;
            std::pair<float, float> direction = std::make_pair(
                cos(angle_rad),  // x direction
                sin(angle_rad)   // y direction
            );
            std::string bullet_sprite_path = "./data/TestData/art/splatterbullet.png";
            float sprite_scale = 0.8f;
            float bullet_speed = 0.1f;
            enemy_bullet_manager->manager_add_bullets(shooter_pos, direction, bullet_sprite_path, sprite_scale, bullet_speed);
        }
    }