#pragma once

#include "GameScene.hpp"
#include "../ESGLib.h"

class clearScene : public CGameScene {
public:
	clearScene()
	{
//		ContentRootDirectory(_T("Content"));
	}

	virtual ~clearScene()
	{
		Finalize();

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
	}

	virtual bool Initialize();

	virtual int  Update();
	virtual void Draw();

private:
	void Finalize();

private:
	// •Ï”éŒ¾
	SPRITE        player;
	SPRITE        clear_;
	SPRITE        a;
	SPRITE        b;
	SPRITE        ta_score;
	SPRITE        bg;
	SPRITE        figure;
	SpriteElement c;
	//RENDERTARGET font;

	float a_roll;
	float a_big;
	float b_big;
	float c_roll;
	float clip_x;
	float b_big2;
	float roll;
	float score_x, score_y, score_x2, score_y2, score_x3, score_y3, score_x4, score_y4, score_x5, score_y5, score_x6, score_y6;
	float speed, speed2;
	float b_big3;
	int   count;
	int   second;
	int   bat_state;
	int   clip_x_max;
	int   time;
	int   time2;
	int   figure_x;
	int   score_state;
	int   start_state;
	FONT  txt;
	FONT  bigtxt;
	SOUND big_se;
	SOUND small_se;
	SOUND tin_se;
	SOUND perfect_se;
};
