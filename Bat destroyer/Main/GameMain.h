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
	// 変数宣言
	enum {
		//出現する物(オブジェクト)の最大数
		object_max = 100,
	};

	//takahasi
	SPRITE         bg;
	SPRITE         ta_player;
	SPRITE         ta_camera;
	SPRITE         tv;
	SPRITE         microwave;
	Rect           player_collision;
	Rect           perfect_collision;
	Rect           Tv_collision;
	Rect           good_collision;
	Rect           good2_collision;
	Rect           miss_collision;
	ANIMATIONMODEL explosion;
	CAMERA         camera;
	MEDIA          movie;

	_int64 moviepos;

	int     timing[object_max];
	int     ta_time;
	int     second_1;
	int     start_state;
	int     goal[object_max];
	int     movie_time;
	int     object_state[object_max];
	int     number;
	int     debug;
	int     font_state;
	float   microwave_speed;
	float   tv_speed;
	float   camera_speed;
	float   tv_x[object_max], tv_y[object_max];
	float   camera_x[object_max], camera_y[object_max];
	float   microwave_x[object_max], microwave_y[object_max];
	float   ta_player_x, ta_player_y;
	float   hit_x, hit_y;
	float   speed_y[object_max];
	float   theta[object_max];
	float   t[object_max];
	char    comma;
	Vector3 point[4];

	SPRITE gas;
	float  gas_speed;
	float  gas_x[object_max], gas_y[object_max];
	Rect   gas_collision[object_max];

	SPRITE car;
	int    car_hit;
	int    car_state;
	float  car_x, car_y;
	float  car_speed;
	Rect   car_collision;

	Rect hit_collision;
	Rect tv_collision[object_max];
	Rect camera_collision[object_max];
	Rect microwave_collision[object_max];
	FONT font;

	KeyboardState  keyboard;
	KeyboardBuffer key_buf;

	// iwai
	
	//チームの方が作成したところなので省略

	// 関数宣言
	void takahasi_Initialize();
	void takahasi_Main();
	void takahasi_Draw();

	void iwai_Initialize();
	void iwai_Update();
	void iwai_Draw();

	void ３ｄ_Initialize();
	void ３ｄ_Update();
	void ３ｄ_Draw();
};
