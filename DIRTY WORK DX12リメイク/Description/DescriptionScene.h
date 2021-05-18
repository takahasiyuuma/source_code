//
// DescriptionScene.h
//

#pragma once

#include "Scene.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class DescriptionScene final : public Scene {
public:
	DescriptionScene() = default;
	virtual ~DescriptionScene() { Terminate(); }

	DescriptionScene(DescriptionScene&&) = default;
	DescriptionScene& operator= (DescriptionScene&&) = default;

	DescriptionScene(DescriptionScene const&) = delete;
	DescriptionScene& operator= (DescriptionScene const&) = delete;

	// These are the functions you will implement.
	void Initialize() override;
	void LoadAssets() override;

	void Terminate() override;

	void OnDeviceLost() override;
	void OnRestartSound() override;

	NextScene Update(const float deltaTime) override;
	void Render() override;

private:

	//スプライト
	unique_ptr <SpriteBatch> sprite_batch;
	SPRITE sprite_main_screen;
	SPRITE sprite_player;
	SPRITE sprite_player_up;
	SPRITE sprite_player_down;
	SPRITE sprite_explanation_window;
	SPRITE sprite_game_system_window;

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

	//エンジン停止音SE
	unique_ptr<SoundEffect>         engine_stop_se;

	//決定音SE
	unique_ptr<SoundEffect>         decision_sound_se;

	//変数
	float player_x,player_y;
	float main_bg_x;
	float speed_x,speed_y;
	float acceleration_up;
	float acceleration_down;
	float alpha;
	float elapsedTime;
	int   speed;
	int   player_direction_state;
	int   description_state;
	bool  next_scene_flag;
	bool  start_flag;

	NextScene next_scene;

	//関数
	void player_update(const float deltaTime);
	void player_draw();
	void description_draw();
	void main_bg_update(const float deltaTime);
	void main_bg_draw();
	void description_state_0_text_draw();
	void description_state_1_text_draw();
};