#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include "../ContestAPI/app.h"
#include "Bullet.h"
#include <math.h>  

typedef std::vector<Bullet*> BulletList;
typedef std::pair<float, float> Direction, Position; // basically a VECTOR2D in godot

// manager that handles all bullets shot by player and enemies

class BulletManager{
    public:
    BulletList* bullets;

    BulletManager();

    ~BulletManager();
    
    void manager_add_bullets(Position shooter_pos, Direction direction, \
        std::string bullet_sprite_path, float sprite_scale, float bullet_speed);

    void update_bullets();

    void update_bullets(Position target_pos);

    void render_and_clear_bullets();

    bool check_bullet_collisions(Position target_pos, float radius);

    void clear_all_bullets();


};

#endif