#ifndef UI_H
#define UI_H

#include "../ContestAPI/app.h"
#include "GameManager.h"

enum game_state{
    START_SCENE = 0,
    PLAYING = 1,
    GAME_OVER = 2
};

class UI{
    public:
        game_state game_current_state;

        UI();

        void switch_game_state(game_state new_state);

        void render_game_ui(int player_health, bool paused);

        void render_help();

    private:

        void render_start_scene();

        void render_health_bar(int player_health);

        void render_score();

        void render_game_over_scene();

        void render_game_pause(bool paused);

        void restart();
};

#endif