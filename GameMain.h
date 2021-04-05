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
	// �ϐ��錾
	enum {
		���̐� = 100,
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
	int hitcount[���̐�];
	float Tv_alpha;
	float big[���̐�];
	float circle_alpha[���̐�];
	float hard_speed;
	float big_�R��;
	float big_go;
	float alpha_go;
	float miss_x, miss_y;
	float �J����_aplha[���̐�];
	float �e���r_aplha[���̐�];
	float �d�q�����W_aplha[���̐�];
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
	MEDIA ���[�r�[;
	SPRITE �w�i;
	SPRITE �v���C���[;
	SPRITE �e���r;
	SPRITE �J����;
	SPRITE �d�q�����W;
	SPRITE �����蔻��;

	_int64 moviepos;

	int �^�C�~���O[���̐�];
	int �b;
	int ��b;
	int �J�n_state;
	float �d�q�����W���x;
	float �e���r���x;
	float �J�������x;
	float �e���r_x[���̐�], �e���r_y[���̐�];
	float �J����_x[���̐�], �J����_y[���̐�];
	float �d�q�����W_x[���̐�], �d�q�����W_y[���̐�];
	float �v���C���[_x, �v���C���[_y;
	float �����蔻��_x, �����蔻��_y;
	int �S�[��[���̐�];
	char comma;
	int ���[�r�[����;
	int ��_state[���̐�];
	int ��;
	int �f�o�b�N;
	//int �e���r����;
	//int �e���r����_state[���̐�];
	float �X�s�[�h_y[���̐�];
	float �V�[�^[���̐�];
	Vector3 �|�C���g[4];
	float t[���̐�];
	int �t�H���g_state;

	SPRITE �K�X��;
	float �K�X�ʑ��x;
	float �K�X��_x[���̐�], �K�X��_y[���̐�];
	Rect �K�X��_collision[���̐�];

	SPRITE ����e���r;
	int ����e���r�A�Ő�;
	int ����e���r_state;
	Rect ����e���r_collision;
	float ����e���r_x, ����e���r_y;
	float ����e���r���x;

	Rect �����蔻��_collision;
	Rect �e���r_collision[���̐�];
	Rect �J����_collision[���̐�];
	Rect �d�q�����W_collision[���̐�];

	FONT �t�H���g;

	KeyboardState keyboard;
	KeyboardBuffer key_buf;
	// �֐��錾

	void ����Initialize();
	void ����Main();
	void ����Draw();
	void iwai_Initialize();
	void iwai_Update();
	void iwai_Draw();
	void �R��_Initialize();
	void �R��_Update();
	void �R��_Draw();
};