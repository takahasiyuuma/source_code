//
// MainScene.h
//

#pragma once

#include "Scene.h"


using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class MainScene final : public Scene {
public:
	MainScene() = default;
	virtual ~MainScene() { Terminate(); }

	MainScene(MainScene&&) = default;
	MainScene& operator= (MainScene&&) = default;

	MainScene(MainScene const&) = delete;
	MainScene& operator= (MainScene const&) = delete;

	// These are the functions you will implement.
	void Initialize() override;
	void LoadAssets() override;

	void Terminate() override;

	void OnDeviceLost() override;
	void OnRestartSound() override;

	NextScene Update(const float deltaTime) override;
	void Render() override;

private:

	enum {
		POLICE_WALL = 4,
	};

	//スプライト
	unique_ptr <SpriteBatch> sprite_batch;
	SPRITE sprite_main_screen;
	SPRITE sprite_player;
	SPRITE sprite_player_up;
	SPRITE sprite_player_down;
	SPRITE sprite_time_frame;
	SPRITE sprite_money_frame;
	SPRITE sprite_enemy_red;
	SPRITE sprite_enemy_blue;
	SPRITE sprite_enemy_police;
	SPRITE sprite_enemy_police_wall;
	SPRITE sprite_danger;

	//BGM
	unique_ptr<SoundEffect>         bgm;
	unique_ptr<SoundEffectInstance> bgm_loop;

	//エンジンSE
	unique_ptr<SoundEffect>         engine_se;
	unique_ptr<SoundEffectInstance> engine_se_loop;

	//急ハンドルSE（上移動中）
	unique_ptr<SoundEffect>         abrupt_steering_up_se;
	unique_ptr<SoundEffectInstance> abrupt_steering_up_se_loop;

	//急ハンドルSE（下移動中）
	unique_ptr<SoundEffect>         abrupt_steering_down_se;
	unique_ptr<SoundEffectInstance> abrupt_steering_down_se_loop;

	//変数
	float player_x, player_y;
	float main_bg_x;
	float speed_x, speed_y;
	float acceleration_up;
	float acceleration_down;
	float alpha;
	float alpha_danger;
	float elapsedTime;
	float enemy_red_x, enemy_red_y;
	float enemy_blue_x, enemy_blue_y;
	float enemy_police_x, enemy_police_y;
	float enemy_police_wall_x[POLICE_WALL], enemy_police_wall_y[POLICE_WALL];
	int   speed;
	int   player_direction_state;
	int   police_wall_decimals;
	int   police_wall_seconds;
	int   police_wall_state;
	int   police_wall_random;
	bool  next_scene_flag;
	bool  start_flag;
	bool  escape_flag;

	NextScene next_scene;

	//関数
	void player_update(const float deltaTime);
	void player_draw();
	void main_bg_update(const float deltaTime);
	void main_bg_draw();
	void enemy_update(const float deltaTime);
	void enemy_draw();
	void police_wall_update(const float deltaTime);
	void police_wall_draw();
};