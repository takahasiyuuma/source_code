//
// TemplateScene.h
//

#pragma once

#include "Scene.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class DifficultysettingScene final : public Scene {
public:
	DifficultysettingScene() = default;
	virtual ~DifficultysettingScene() { Terminate(); }

	DifficultysettingScene(DifficultysettingScene&&) = default;
	DifficultysettingScene& operator= (DifficultysettingScene&&) = default;

	DifficultysettingScene(DifficultysettingScene const&) = delete;
	DifficultysettingScene& operator= (DifficultysettingScene const&) = delete;

	// These are the functions you will implement.
	void Initialize() override;
	void LoadAssets() override;

	void Terminate() override;

	void OnDeviceLost() override;
	void OnRestartSound() override;

	NextScene Update(const float deltaTime) override;
	void Render() override;

	static int game_mode_state;

private:

	float alpha;
	float elapsedTime;
	bool next_scene_flag;
	bool start_flag;

	unique_ptr <SpriteBatch> sprite_batch;
	SPRITE sprite_bg;

	//BGM
	unique_ptr<SoundEffect>         bgm;
	unique_ptr<SoundEffectInstance> bgm_loop;

	//ƒGƒ“ƒWƒ“’âŽ~‰¹SE
	unique_ptr<SoundEffect> engine_stop_se;

	//Œˆ’è‰¹
	unique_ptr<SoundEffect> decision_sound_se;

	void game_mode_state_0_text_draw();
	void game_mode_state_1_text_draw();
	void game_mode_state_2_text_draw();
};