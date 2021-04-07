#pragma once

#include "ESGLib.h"
#include "GameScene/GameScene.hpp"

class GameMain : public CGameScene {
public:
	GameMain() : DefaultFont(GraphicsDevice.CreateDefaultFont())
	{
//		ContentRootDirectory(_T("Content"));
	}

	virtual ~GameMain()
	{
#ifdef _INC_SQUIRREL
		Squirrel.ReleaseAllScripts();
#endif
#ifdef _INC_NUI
		NUI.ReleaseAllKinects();
#endif
#ifdef _INC_LIVE2D
		Live2D.ReleaseAllModels();
#endif
#ifdef _INC_EFFEKSEER
		Effekseer.ReleaseAllEffects();
#endif
#ifdef _INC_DIRECT2D
		Direct2D.ReleaseAllResources();
#endif
		MediaManager.ReleaseAllMedia();

		SoundDevice.ReleaseAllMusics();
		SoundDevice.ReleaseAllSounds();

		GraphicsDevice.ReleaseAllRenderTargets();
		GraphicsDevice.ReleaseAllStateBlocks();
		GraphicsDevice.ReleaseAllFonts();
		GraphicsDevice.ReleaseAllSprites();
		GraphicsDevice.ReleaseAllAnimationModels();
		GraphicsDevice.ReleaseAllModels();
		GraphicsDevice.ReleaseAllVertexBuffers();
		GraphicsDevice.ReleaseAllEffects();

		Finalize();
	}

public:
	virtual bool Initialize();

	virtual int  Update();
	virtual void Draw();

private:
	void Finalize();
	FONT DefaultFont;
private:

	enum {
		タイトル画面,
		メイン画面,
		説明画面,
		ゲームオーバー画面,
		ゲームクリア画面,
		難易度設定画面,
	};

	// 変数宣言

	SPRITE ゲームプレイ背景;
	SPRITE スタート背景;
	SPRITE クリア背景;
	SPRITE ゲームオーバー背景;
	SPRITE 難易度設定背景;
	SPRITE プレイヤー;
	SPRITE プレイヤー上;
	SPRITE プレイヤー下;
	SPRITE 赤車;
	SPRITE 青車;
	SPRITE 追跡パトカー;
	SPRITE 壁パトカー;
	SPRITE 衝突エフェクト;
	SPRITE ＄袋;
	SPRITE ＄袋2;
	SPRITE 歩行者;
	SPRITE 歩行者2;
	SPRITE ゲームシステム背景;
	SPRITE ゲーム操作説明背景;
	SPRITE 金額枠;
	SPRITE タイム枠;
	SPRITE EXタイム枠;
	SPRITE 危険;
	SPRITE プレイヤー2;
	SPRITE クリア画面金額枠;

	bool 点滅_flag;

	float 背景_x;
	float プレイヤー_x, プレイヤー_y;
	float 赤車_x, 赤車_y;
	float 青車_x, 青車_y;
	float 壁パトカー_x, 壁パトカー_y;
	float 壁パトカー2_x, 壁パトカー2_y;
	float 壁パトカー3_x, 壁パトカー3_y;
	float 壁パトカー4_x, 壁パトカー4_y;
	float 追跡パトカー_x,追跡パトカー_y;
	float 歩行者_x, 歩行者_y;
	float 歩行者2_x, 歩行者2_y;
	float _time = 1.0f;
	float _totalTime = 0.0f;
	float スピード_x,スピード_y;
	float ＄袋_x, ＄袋_y;
	float ＄袋2_x, ＄袋2_y;
	float プレイヤー描画_x;

	int 画面_state;
	int 無敵_state;
	int 無敵;
	int 無敵2;
	int 無敵点滅;
	int 衝突_state;
	int 一秒;
	int タイム秒;
	int 逃走タイム秒;
	int 逃走タイム秒2;
	int 逃走タイム秒3;
	int 逃走タイム_state;
	int ハード逃走タイム秒3;
	int 衝突表示時間;
	int 衝突表示時間2;
	int スコア;
	int スコア2;
	int スコア3;
	int ハイスコア;
	int ハードハイスコア;
	int ライフ;
	int スピード;
	int スピード2;
	int スピード加速;
	int スピード加速秒;
	int スピード加速秒2;
	int ＄袋_state;
	int ＄袋2_state;
	int 追跡_state;
	int プレイヤー_state;
	int プレイヤー向き_state;
	int 逮捕_state;
	int 逮捕;
	int 逮捕2;
	int 逃走_state;
	int 逃走;
	int 逃走2;
	int 点滅;
	int パトカー壁秒数;
	int パトカー壁秒数2;
	int パトカー壁_state;
	int パトカー壁ランダム;
	int 説明_state;
	int 衝突エフェクト_x;
	int 衝突, 衝突2;
	int ゲームモード設定_state;
	int EXモード秒;
	int EXモード秒2;
	int EXモード秒3;
	int EXタイム_state;
	int スピードタイム;
	int スピード_state;
	int プレイヤー描画_state;

	FONT フォントスタート;
	FONT フォント;
	FONT フォント2;
	FONT フォント3;
	FONT フォント4;
	FONT フォント操作説明;
	FONT 注意フォント;

	Color 注意Color;

	MUSIC ゲームプレイBGM;
	SOUND 衝突SE;
	SOUND サイレンSE;
	SOUND3D サイレンSE3D;
	SOUND サイレンSE2;
	SOUND サイレンSE3;
	SOUND3D サイレンSE3D2;
	SOUND 走行中SE;
	SOUND エンジン起動SE;
	SOUND 通過SE;
	SOUND 上下移動SE;
	SOUND 上下移動SE2;
	SOUND 事故SE;
	SOUND シャッターSE;

	Rect プレイヤー_collision;
	Rect 赤車_collision;
	Rect 青車_collision;
	Rect 壁パトカー_collision;
	Rect 壁パトカー2_collision;
	Rect 壁パトカー3_collision;
	Rect 壁パトカー4_collision;

	KeyboardState Keystate;
	KeyboardBuffer Key_buffer;
	GamePadState pad;
	GamePadBuffer pad_buffer;

	// 関数宣言

	void タイトル処理();
	void タイトル初期化();
	void タイトル描画();
	void メイン処理();
	void 当たり判定処理();
	void プレイヤー処理();
	void エネミー処理();
	void 壁エネミー処理();
	void メイン描画();
	void 壁エネミー描画();
	void 操作説明処理();
	void 操作説明描画();
	void ゲームオーバー処理();
	void ゲームオーバー描画();
	void ゲームクリア処理();
	void ゲームクリア描画();
	void 難易度設定処理();
	void 難易度設定描画();
};