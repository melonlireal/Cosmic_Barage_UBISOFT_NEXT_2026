#include "UI.h"


UI::UI() {
    game_current_state = START_SCENE;
}

void UI::switch_game_state(game_state new_state){
    game_current_state = new_state;
}

void UI::render_game_ui(int player_health, bool paused){
    if (game_current_state == START_SCENE){
        render_start_scene();
    } else if (game_current_state == PLAYING){
        render_health_bar(player_health);
        render_score();
    } else if (game_current_state == GAME_OVER){
        render_game_over_scene();
    }
    render_game_pause(paused);
}

void UI::render_help(){
    App::Print(10.0f, APP_VIRTUAL_HEIGHT - 40.0f, "HELP:", 1.0f, 1.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24);
    App::Print(10.0f, APP_VIRTUAL_HEIGHT - 60.0f, "WASD / Arrow / Left Thumbstick: Move", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24);
    App::Print(10.0f, APP_VIRTUAL_HEIGHT - 80.0f, "Left Mouse / Space / Right Trigger: Shoot", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24);
    App::Print(10.0f, APP_VIRTUAL_HEIGHT - 100.0f, "P to Pause / U to Unpause", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24);
    App::Print(10.0f, APP_VIRTUAL_HEIGHT - 120.0f, "R to Restart after Game Over", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24);
    App::Print(10.0f, APP_VIRTUAL_HEIGHT - 140.0f, "B to go back to Main Menu after Game Over", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24);
    App::Print(10.0f, APP_VIRTUAL_HEIGHT - 160.0f, "Press Enter to start the game", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24);
    App::Print(10.0f, APP_VIRTUAL_HEIGHT - 180.0f, "Press Q to quit", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24);
    App::Print(10.0f, APP_VIRTUAL_HEIGHT - 200.0f, "Have Fun!", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24);
}

void UI::render_start_scene(){
    // I WILL ADD A LARGE FONT EVEN WHEN YALL DONT GIVE ME THE OPTION
    CSimpleSprite* FONT= App::CreateSprite("./data/TestData/art/MYBIGFONT.png", 1, 1);
    FONT->SetPosition(APP_VIRTUAL_WIDTH/2.f, APP_VIRTUAL_HEIGHT/2.f + 50);
    FONT->Draw();
    delete FONT;
    App::Print(APP_VIRTUAL_WIDTH/2.f -50, APP_VIRTUAL_HEIGHT/2.f -50, "START", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24 );
    App::Print(APP_VIRTUAL_WIDTH/2.f -40, APP_VIRTUAL_HEIGHT/2.f - 80, "QUIT", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24 );
}


void UI::render_health_bar(int player_health){
    Position heart_pos = std::make_pair(50.0f, 700.0f);
for (int i = 0; i < player_health; i++){
        CSimpleSprite* heart= App::CreateSprite("./data/TestData/art/player_health.png", 1, 1);
        heart->SetPosition(heart_pos.first + i * 60.0f, heart_pos.second);
        heart->SetScale(0.2f);
        heart->Draw();
        delete heart;
    }
}

void UI::render_score(){
    App::Print(APP_VIRTUAL_WIDTH/2.f -50, 700.0, std::to_string(score).c_str(), 1.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24 );
}

void UI::render_game_pause(bool paused){
    if (paused){
        App::Print(APP_VIRTUAL_WIDTH/2.f -40, APP_VIRTUAL_HEIGHT/2.f, "PAUSED", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24 );
        App::Print(APP_VIRTUAL_WIDTH/2.f -120, APP_VIRTUAL_HEIGHT/2.f -30, "PRESS U TO UNPAUSE", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24 );
    }
}

void UI::render_game_over_scene(){
    CSimpleSprite* GAMEOVER= App::CreateSprite("./data/TestData/art/GAMEOVER.png", 1, 1);
    GAMEOVER->SetPosition(APP_VIRTUAL_WIDTH/2.f, APP_VIRTUAL_HEIGHT/2.f + 50);
    GAMEOVER->Draw();
    delete GAMEOVER;
    App::Print(APP_VIRTUAL_WIDTH/2.f -15, APP_VIRTUAL_HEIGHT/2.f - 20, std::to_string(score).c_str(), 1.0f, 0.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24);
    App::Print(APP_VIRTUAL_WIDTH/2.f -40, APP_VIRTUAL_HEIGHT/2.f -50, "RESTART", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24);
    App::Print(APP_VIRTUAL_WIDTH/2.f -80, APP_VIRTUAL_HEIGHT/2.f - 80, "BACK TO MENU", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24);
    App::Print(APP_VIRTUAL_WIDTH/2.f -25, APP_VIRTUAL_HEIGHT/2.f - 110, "QUIT", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24);
}

void UI::restart(){
    game_current_state = START_SCENE;
    score = 0;
}