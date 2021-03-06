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
		^CgæÊ,
		CæÊ,
		à¾æÊ,
		Q[I[o[æÊ,
		Q[NAæÊ,
		ïÕxÝèæÊ,
	};

	// Ïé¾

	SPRITE Q[vCwi;
	SPRITE X^[gwi;
	SPRITE NAwi;
	SPRITE Q[I[o[wi;
	SPRITE ïÕxÝèwi;
	SPRITE vC[;
	SPRITE vC[ã;
	SPRITE vC[º;
	SPRITE ÔÔ;
	SPRITE ÂÔ;
	SPRITE ÇÕpgJ[;
	SPRITE ÇpgJ[;
	SPRITE ÕËGtFNg;
	SPRITE Ü;
	SPRITE Ü2;
	SPRITE àsÒ;
	SPRITE àsÒ2;
	SPRITE Q[VXewi;
	SPRITE Q[ìà¾wi;
	SPRITE àzg;
	SPRITE ^Cg;
	SPRITE EX^Cg;
	SPRITE ë¯;
	SPRITE vC[2;
	SPRITE NAæÊàzg;

	bool _Å_flag;

	float wi_x;
	float vC[_x, vC[_y;
	float ÔÔ_x, ÔÔ_y;
	float ÂÔ_x, ÂÔ_y;
	float ÇpgJ[_x, ÇpgJ[_y;
	float ÇpgJ[2_x, ÇpgJ[2_y;
	float ÇpgJ[3_x, ÇpgJ[3_y;
	float ÇpgJ[4_x, ÇpgJ[4_y;
	float ÇÕpgJ[_x,ÇÕpgJ[_y;
	float àsÒ_x, àsÒ_y;
	float àsÒ2_x, àsÒ2_y;
	float _time = 1.0f;
	float _totalTime = 0.0f;
	float Xs[h_x,Xs[h_y;
	float Ü_x, Ü_y;
	float Ü2_x, Ü2_y;
	float vC[`æ_x;

	int æÊ_state;
	int ³G_state;
	int ³G;
	int ³G2;
	int ³G_Å;
	int ÕË_state;
	int êb;
	int ^Cb;
	int ¦^Cb;
	int ¦^Cb2;
	int ¦^Cb3;
	int ¦^C_state;
	int n[h¦^Cb3;
	int ÕË\¦Ô;
	int ÕË\¦Ô2;
	int XRA;
	int XRA2;
	int XRA3;
	int nCXRA;
	int n[hnCXRA;
	int Ct;
	int Xs[h;
	int Xs[h2;
	int Xs[hÁ¬;
	int Xs[hÁ¬b;
	int Xs[hÁ¬b2;
	int Ü_state;
	int Ü2_state;
	int ÇÕ_state;
	int vC[_state;
	int vC[ü«_state;
	int ßß_state;
	int ßß;
	int ßß2;
	int ¦_state;
	int ¦;
	int ¦2;
	int _Å;
	int pgJ[Çb;
	int pgJ[Çb2;
	int pgJ[Ç_state;
	int pgJ[Ç_;
	int à¾_state;
	int ÕËGtFNg_x;
	int ÕË, ÕË2;
	int Q[[hÝè_state;
	int EX[hb;
	int EX[hb2;
	int EX[hb3;
	int EX^C_state;
	int Xs[h^C;
	int Xs[h_state;
	int vC[`æ_state;

	FONT tHgX^[g;
	FONT tHg;
	FONT tHg2;
	FONT tHg3;
	FONT tHg4;
	FONT tHgìà¾;
	FONT ÓtHg;

	Color ÓColor;

	MUSIC Q[vCBGM;
	SOUND ÕËSE;
	SOUND TCSE;
	SOUND3D TCSE3D;
	SOUND TCSE2;
	SOUND TCSE3;
	SOUND3D TCSE3D2;
	SOUND sSE;
	SOUND GWN®SE;
	SOUND ÊßSE;
	SOUND ãºÚ®SE;
	SOUND ãºÚ®SE2;
	SOUND ÌSE;
	SOUND Vb^[SE;

	Rect vC[_collision;
	Rect ÔÔ_collision;
	Rect ÂÔ_collision;
	Rect ÇpgJ[_collision;
	Rect ÇpgJ[2_collision;
	Rect ÇpgJ[3_collision;
	Rect ÇpgJ[4_collision;

	KeyboardState Keystate;
	KeyboardBuffer Key_buffer;
	GamePadState pad;
	GamePadBuffer pad_buffer;

	// Öé¾

	void ^Cg();
	void ^Cgú»();
	void ^Cg`æ();
	void C();
	void ½è»è();
	void vC[();
	void Gl~[();
	void ÇGl~[();
	void C`æ();
	void ÇGl~[`æ();
	void ìà¾();
	void ìà¾`æ();
	void Q[I[o[();
	void Q[I[o[`æ();
	void Q[NA();
	void Q[NA`æ();
	void ïÕxÝè();
	void ïÕxÝè`æ();
};