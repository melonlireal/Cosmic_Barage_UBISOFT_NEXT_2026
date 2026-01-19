#include "BulletManager.h"

    BulletManager::BulletManager(){
        bullets = new BulletList();
    }

    BulletManager::~BulletManager(){
        clear_all_bullets();
        delete bullets;
    }

    void BulletManager::manager_add_bullets(Position shooter_pos, Direction direction, \
            std::string bullet_sprite_path, float sprite_scale, float bullet_speed) {
                
        CSimpleSprite* bullet_sprite = App::CreateSprite(bullet_sprite_path.c_str(), 1, 1);
        float angle_rad = atan2(direction.second, direction.first) - PI / 2.0f;
        // this returns a double but float is precise enough as its just rotation
        bullet_sprite->SetAngle(angle_rad);  // Rotate sprite to face upwards
        bullet_sprite->SetScale(sprite_scale); 
        Bullet* new_bullet = new Bullet(shooter_pos, direction, bullet_speed, bullet_sprite);
        bullets->push_back(new_bullet);
        return;
    }

    void BulletManager::update_bullets() {
        for (auto& bullet : *bullets) {
            bullet->bullet_update_position();
        }
    }

    // this is for traceable bullets that follow a target
    void BulletManager::update_bullets(Position target_pos) {
        for (auto& bullet : *bullets) {
            bullet->bullet_set_direction(target_pos.first, target_pos.second);
            bullet->bullet_update_position();
        }
    }

    void BulletManager::render_and_clear_bullets() {

        // terrible algorithm fix later

        float tester_x, tester_y;
        
        // Use two-pointer technique for in-place removal
        size_t write_index = 0;
        float buffer = 10.0f;
        
        for (size_t read_index = 0; read_index < bullets->size(); read_index++) {
            auto* bullet = (*bullets)[read_index];
            bullet->bullet_get_position(tester_x, tester_y);
            
            // Check if bullet is in bounds
            if (tester_x >= -buffer && tester_x <= APP_VIRTUAL_WIDTH + buffer && 
                tester_y >= -buffer && tester_y <= APP_VIRTUAL_HEIGHT + buffer) {
                
                // Keep bullet - draw it
                bullet->sprite->Draw();
                
                // Move to keep position
                if (write_index != read_index) {
                    (*bullets)[write_index] = bullet;
                }
                write_index++;
            } else {
                // Delete out-of-bounds bullet
                delete bullet;
            }
        }
        
        // Resize vector to remove deleted bullets
        bullets->resize(write_index);
    }

    bool BulletManager::check_bullet_collisions(Position target_pos, float radius){
        for (auto& bullet : *bullets) {
            float bullet_x, bullet_y;
            bullet->bullet_get_position(bullet_x, bullet_y);
            // Simple collision check

            if (fabs(bullet_x - target_pos.first) < radius && fabs(bullet_y - target_pos.second) < radius) {
                bullet->sprite->SetPosition(-100.0f, -100.0f); // Move it off-screen for removal
                return true;
            }
        }
        return false;
    }

    // called when restarting the game or destroying the bullet manager
    void BulletManager::clear_all_bullets(){
        for (auto& bullet : *bullets) {
            delete bullet;
        }
        bullets->clear();
    }