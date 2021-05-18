//
// TitleScene.h
//

#pragma once

#include "Scene.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class TitleScene final : public Scene {
public:
	TitleScene() = default;
	virtual ~TitleScene() { Terminate(); }

	TitleScene(TitleScene&&) = default;
	TitleScene& operator= (TitleScene&&) = default;

	TitleScene(TitleScene const&) = delete;
	TitleScene& operator= (TitleScene const&) = delete;

	// These are the functions you will implement.
	void Initialize() override;
	void LoadAssets() override;

	void Terminate() override;

	void OnDeviceLost() override;
	void OnRestartSound() override;

	NextScene Update(const float deltaTime) override;
	void Render() override;

	static int スコア;
	static int スコア2;
	static int スコア3;
	static int ハイスコア;
	static int 逃走タイム秒3;
	static int ハードハイスコア;
	static int ハード逃走タイム秒3;

private:

	unique_ptr <SpriteBatch> sprite_batch;
	SPRITE                   sprite_bg;
	SPRITE                   sprite_player_mini;

	unique_ptr<SoundEffect>         bgm;
	unique_ptr<SoundEffectInstance> bgm_loop;
	unique_ptr<SoundEffect>         engine_start_up_se;
	unique_ptr<SoundEffect>         decision_sound_se;

	int   title_state;
	float elapsedTime;
	float alpha;
	float player_mini_x, player_mini_y;
	bool  nextSceneFlag;
	bool  start_flag;

	NextScene nextScene;

	void next_scene_update(const float deltaTime);

	void game_mode_no_text_draw();
	void game_mode_ha_text_draw();
	void game_mode_ex_text_draw();
};