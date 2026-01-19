#include "EnemyMinion.h"

    EnemyMinion::EnemyMinion(Position pos, float hp, float spe,
                  Direction target_dir, CSimpleSprite* spr,
                  float shoot_interval)
        : Enemy(pos, hp, spe, target_dir, spr, shoot_interval) {
        // Base class constructor handles initialization
    }

    void EnemyMinion::enemy_shoot(Position target_pos) {
        if (!can_shoot) {
            return;
        }
        // Reset shoot flag (important!)
        can_shoot = false;
        
        float enemy_x, enemy_y;
        enemy_get_position(enemy_x, enemy_y);
        Position shooter_pos = std::make_pair(enemy_x, enemy_y);
        float dx, dy;
        dx = target_pos.first - enemy_x;
        dy = target_pos.second - enemy_y;
        float distance = sqrt(dx*dx + dy*dy);
        float normx = dx / distance;
        float normy = dy / distance;
        Direction direction = std::make_pair(normx, normy); // Shoot towards target
        std::string bullet_sprite_path = "./data/TestData/art/minionbullet.png";
        float sprite_scale = 0.6f;
        float bullet_speed = 0.1f;
        enemy_bullet_manager->manager_add_bullets(shooter_pos, direction, bullet_sprite_path, sprite_scale, bullet_speed);
    }