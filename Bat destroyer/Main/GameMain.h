#pragma once

#include "ESGLib.h"
#include "GameScene/GameScene.hpp"

class GameMain : public CGameScene {
public:
	GameMain()
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

public:
	static int score;
	static int perfect_;
	static int good_;
	static int miss_;
private:
	// ïœêîêÈåæ
	enum {
		object_max = 100,
	};
	SPRITE player;
	SPRITE player_swing;
	SPRITE player_Empty_swing;
	SPRITE map;
	SPRITE perfect;
	SPRITE good;
	SPRITE miss;
	SPRITE life;
	SPRITE good_point;
	SPRITE perfect_point;
	SPRITE Tv;
	SPRITE circle;
	SPRITE hit_point;
	SPRITE ready;
	SPRITE go;
	SOUND good_se;
	SOUND perfect_se;
	SOUND miss_se;
	float player_x, player_y;
	float Tv_x, Tv_y;
	int hit_test;
	float range;
	int swing_flg;
	float life_y;
	float clip_x;
	int count;
	float good_x,good_y;
	float perfect_x, perfect_y;
	int hitcount[object_max];
	float Tv_alpha;
	float big[object_max];
	float circle_alpha[object_max];
	float hard_speed;
	float big_ÇRÇÑ;
	float big_go;
	float alpha_go;
	float miss_x, miss_y;
	float camera_aplha[object_max];
	float tv_aplha[object_max];
	float microwave_aplha[object_max];
	int combo;
	FONT txt;
	Rect  player_collision;
	Rect  perfect_collision;
	Rect  Tv_collision;
	Rect  good_collision;
	Rect  good2_collision;
	Rect  miss_collision;
	ANIMATIONMODEL explosion;
	CAMERA camera;
	MEDIA movie;
	SPRITE bg;
	SPRITE ta_player;
	SPRITE tv;
	SPRITE ta_camera;
	SPRITE microwave;
	SPRITE hit;

	_int64 moviepos;

	int timing[object_max];
	int ta_time;
	int second_1;
	int start_state;
	float microwave_speed;
	float tv_speed;
	float camera_speed;
	float tv_x[object_max], tv_y[object_max];
	float camera_x[object_max], camera_y[object_max];
	float microwave_x[object_max], microwave_y[object_max];
	float ta_player_x, ta_player_y;
	float hit_x, hit_y;
	int goal[object_max];
	char comma;
	int movie_time;
	int object_state[object_max];
	int number;
	int debug;
	float speed_y[object_max];
	float theta[object_max];
	Vector3 point[4];
	float t[object_max];
	int font_state;

	SPRITE gas;
	float gas_speed;
	float gas_x[object_max], gas_y[object_max];
	Rect gas_collision[object_max];

	SPRITE big_tv;
	int big_tv_hit;
	int big_tv_state;
	Rect big_tv_collision;
	float big_tv_x, big_tv_y;
	float big_tv_speed;

	Rect hit_collision;
	Rect tv_collision[object_max];
	Rect camera_collision[object_max];
	Rect microwave_collision[object_max];

	FONT font;

	KeyboardState keyboard;
	KeyboardBuffer key_buf;
	// ä÷êîêÈåæ

	void takahasi_Initialize();
	void takahasi_Main();
	void takahasi_Draw();
	void iwai_Initialize();
	void iwai_Update();
	void iwai_Draw();
	void ÇRÇÑ_Initialize();
	void ÇRÇÑ_Update();
	void ÇRÇÑ_Draw();
};