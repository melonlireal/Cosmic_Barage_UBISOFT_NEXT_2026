///////////////////////////////////////////////////////////////////////////////
// Filename: GameTest.cpp
// Provides a demo of how to use the API
///////////////////////////////////////////////////////////////////////////////

#if BUILD_PLATFORM_WINDOWS
//------------------------------------------------------------------------
#include <windows.h> 
#endif

#include <iostream>
//------------------------------------------------------------------------
#include <math.h>  
//------------------------------------------------------------------------
#include "../ContestAPI/app.h"
//------------------------------------------------------------------------
#include "Enemy.h"
#include "EnemySplatter.h"
#include "EnemyMinion.h"
#include "EnemyCharger.h"
#include "UI.h"

#include "GameManager.h"
#include "EnemyManager.h"
#include "Bullet.h"
#include "Timer.h"
// technically this is not needed here but I'm adding them for clarity
//------------------------------------------------------------------------
// Example data....
//------------------------------------------------------------------------

Timer* spawn_timer;
EnemyManager* enemy_manager;
UI* game_ui;

CSimpleSprite* background;

// x pos, y pos, health, damange
bool spawn = false;
bool playing = false; // check if the actual game is being played
bool shutting = false;
bool pause = false;
bool show_help = false;

//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------

void Init()
{
	//------------------------------------------------------------------------
	// Example Sprite Code....
	Game_Manager_Initialize();

	game_ui = new UI();
	background = App::CreateSprite("./data/TestData/art/background.png", 1, 1);
	background->SetPosition(APP_VIRTUAL_WIDTH/2.f, APP_VIRTUAL_HEIGHT/2.f); // center the background
	background->SetScale(1.5f);

	enemy_manager = new EnemyManager();
	spawn_timer = new Timer(0.5f);
	
	App::PlayAudio("./data/TestData//music/bgm.wav", true);
	//------------------------------------------------------------------------
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(const float deltaTime)
{
	show_help = false; 

	if (App::IsKeyPressed(App::KEY_H)) {
		show_help = true;
	}
	//once player stop pressing H, help menu disappear

	if (!pause && App::IsKeyPressed(App::KEY_P) && game_ui->game_current_state == PLAYING) {
		App::PlayAudio("./data/TestData//music/UI.wav", false); 
		pause = true;
	}

	if (pause && App::IsKeyPressed(App::KEY_U) && game_ui->game_current_state == PLAYING) {
		App::PlayAudio("./data/TestData//music/UI.wav", false); 
		pause = false;
	}
	// pause and unpase game

	if (pause || shutting){return;} // dont update anything when game paused

	if (player_entity->health <= 0 && playing){
		// check if gameover
		game_ui->switch_game_state(GAME_OVER);
		playing = false;
		spawn_timer->timer_end();
		player_entity->player_set_position(0, -200.0f); 
		// move player offscreen when game over
	}

	spawn_timer->timer_increment_time(&spawn);
	if (spawn) {
		spawn = false;
		enemy_manager->spawn_rand_enemy();
		// spawn an enemy every interval
	}

	enemy_manager->update_enemies(deltaTime);
	enemy_manager->render_and_clear_enemies();

	player_entity->player_update(deltaTime);
	// update entities

	// check for collisions between player bullets and boss

	// move player based on controller input
	float player_x_dir = 0.0f;
	float player_y_dir = 0.0f;
	if (App::GetController().GetLeftThumbStickX() > 0.5f || App::IsKeyPressed(App::KEY_RIGHT))
	{	
		if (playing){
			player_x_dir += 1.0f;
		}
	}
	if (App::GetController().GetLeftThumbStickX() < -0.5f || App::IsKeyPressed(App::KEY_LEFT))
	{
		if (playing){
			player_x_dir -= 1.0f;
		}
	}
	if (App::GetController().GetLeftThumbStickY() > 0.5f || App::IsKeyPressed(App::KEY_UP))
	{
		if (playing){
		player_y_dir += 1.0f;
		}
	}
	if (App::GetController().GetLeftThumbStickY() < -0.5f || App::IsKeyPressed(App::KEY_DOWN))
	{
		if (playing){
		player_y_dir -= 1.0f;
		}
	}
	player_entity->player_move(player_x_dir, player_y_dir);


	if (App::IsKeyPressed(App::KEY_ENTER) || App::GetController().GetRightTrigger() > 0.0f)
	{
		//||App::GetController().CheckButton(App::BTN_A)
		// cuz it appears this button also triggers enter key
		if (!App::IsSoundPlaying("./data/TestData//music/UI.wav")){
			App::PlayAudio("./data/TestData//music/UI.wav", false);
		}
		if (!playing && game_ui->game_current_state == START_SCENE){
		game_ui->switch_game_state(PLAYING);
		playing = true;
		player_entity->player_set_position(APP_VIRTUAL_WIDTH/2.f, APP_VIRTUAL_HEIGHT/4.f);
		spawn_timer->timer_start();
		}

	}

	if (App::IsKeyPressed(App::KEY_R) || App::GetController().CheckButton(App::BTN_X))
	{
		if (!playing && game_ui->game_current_state == GAME_OVER){

			if (!App::IsSoundPlaying("./data/TestData//music/UI.wav")){
				App::PlayAudio("./data/TestData//music/UI.wav", false);
			}
			enemy_bullet_manager->clear_all_bullets();
			player_bullet_manager->clear_all_bullets();
			enemy_manager->clear_all_enemies();

			game_ui->switch_game_state(PLAYING);
			player_entity->health = 5;
			score = 0;
			playing = true;
			player_entity->player_set_position(APP_VIRTUAL_WIDTH/2.f, APP_VIRTUAL_HEIGHT/4.f);
			spawn_timer->timer_start();
		}
	}

	if (App::IsKeyPressed(App::KEY_B) || App::GetController().CheckButton(App::BTN_B)){
		if (!playing && game_ui->game_current_state == GAME_OVER){
			if (!App::IsSoundPlaying("./data/TestData//music/UI.wav")){
				App::PlayAudio("./data/TestData//music/UI.wav", false);
			}
			enemy_bullet_manager->clear_all_bullets();
			player_bullet_manager->clear_all_bullets();
			enemy_manager->clear_all_enemies();

			game_ui->switch_game_state(START_SCENE);
			player_entity->health = 5;
			score = 0;
		}
	}

	// check for shooting input
	if (App::IsMousePressed(GLUT_LEFT_BUTTON) || App::IsKeyPressed(App::KEY_SPACE) || App::GetController().GetRightTrigger() >0.0f)
	{
		if (playing){
		player_entity->player_shoot();
		}
		
	}


	// check for collisions
	float enemy_x, enemy_y;
	for (Enemy* enemy : *(enemy_manager->enemies)) {
		enemy->enemy_get_position(enemy_x, enemy_y);
		Position enemy_pos = std::make_pair(enemy_x, enemy_y);
		if(player_bullet_manager->check_bullet_collisions(enemy_pos, 50.0f)){
			enemy->enemy_take_damage(2.0f);
			if (App::IsSoundPlaying("./data/TestData//music/enemy_hurt.wav") == false){
				App::PlayAudio("./data/TestData//music/enemy_hurt.wav", false);
			}
		}
	}
	// collision between player bullets and enemies

	float player_x, player_y;
	player_entity->player_get_position(player_x, player_y);
	Position player_pos = std::make_pair(player_x, player_y);
	if(enemy_bullet_manager->check_bullet_collisions(player_pos, 10.0f)){
		player_entity->player_take_damage(1.0f);
		if (App::IsSoundPlaying("./data/TestData//music/player_hurt.wav") == false){
			App::PlayAudio("./data/TestData//music/player_hurt.wav", false);
		}
	}
	// collision between enemy bullets and player

	if (enemy_manager->check_enemy_player_collisions(player_entity)) {
		player_entity->player_take_damage(2.0f);
		if (App::IsSoundPlaying("./data/TestData//music/player_hurt.wav") == false){
			App::PlayAudio("./data/TestData//music/player_hurt.wav", false);
		}
	}
	//collision between enemies and player
	// these checkers can be greately improved if use screen is devided to difference sectors 
	// and only collision in the same sector is checked
	// it can be done by making bullet manager and enemy manager 
	// store bullet and enemy in a map rather than vector
	// however I run out of time to implement this optimization

}


//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{
	if (shutting){
		return;
		// prevent race condition during shutdown
	}
	background->Draw();
	// draw background first
		
	player_entity->player_render();
	enemy_manager->render_and_clear_enemies();
	// draw player and enemies


	player_bullet_manager->render_and_clear_bullets();
	enemy_bullet_manager->render_and_clear_bullets();
	// draw bullets


	game_ui->render_game_ui(player_entity->health, pause);
	App::Print(10.0f, APP_VIRTUAL_HEIGHT - 20.0F, "Press H for Help", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24);
	if (show_help){
		game_ui->render_help();
	}
	// draw UI and help menu

	for (int i = 0; i < APP_VIRTUAL_HEIGHT; i += 3.5)
	{

		App::DrawLine(0.0, i, APP_VIRTUAL_WIDTH	, i, 0.0, 0.0, 0.0);
	}
	// a layer of simple arcade effect
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{
	shutting = true;
	player_bullet_manager->clear_all_bullets();
	enemy_bullet_manager->clear_all_bullets();
	enemy_manager->clear_all_enemies();
	delete background;
	delete spawn_timer;
	delete game_ui;
	delete player_entity;
	delete player_bullet_manager;
	delete enemy_bullet_manager;
	delete enemy_manager;
	return;
}