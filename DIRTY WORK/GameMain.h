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
		�^�C�g�����,
		���C�����,
		�������,
		�Q�[���I�[�o�[���,
		�Q�[���N���A���,
		��Փx�ݒ���,
	};

	// �ϐ��錾

	SPRITE �Q�[���v���C�w�i;
	SPRITE �X�^�[�g�w�i;
	SPRITE �N���A�w�i;
	SPRITE �Q�[���I�[�o�[�w�i;
	SPRITE ��Փx�ݒ�w�i;
	SPRITE �v���C���[;
	SPRITE �v���C���[��;
	SPRITE �v���C���[��;
	SPRITE �Ԏ�;
	SPRITE ��;
	SPRITE �ǐՃp�g�J�[;
	SPRITE �ǃp�g�J�[;
	SPRITE �Փ˃G�t�F�N�g;
	SPRITE ����;
	SPRITE ����2;
	SPRITE ���s��;
	SPRITE ���s��2;
	SPRITE �Q�[���V�X�e���w�i;
	SPRITE �Q�[����������w�i;
	SPRITE ���z�g;
	SPRITE �^�C���g;
	SPRITE EX�^�C���g;
	SPRITE �댯;
	SPRITE �v���C���[2;
	SPRITE �N���A��ʋ��z�g;

	bool �_��_flag;

	float �w�i_x;
	float �v���C���[_x, �v���C���[_y;
	float �Ԏ�_x, �Ԏ�_y;
	float ��_x, ��_y;
	float �ǃp�g�J�[_x, �ǃp�g�J�[_y;
	float �ǃp�g�J�[2_x, �ǃp�g�J�[2_y;
	float �ǃp�g�J�[3_x, �ǃp�g�J�[3_y;
	float �ǃp�g�J�[4_x, �ǃp�g�J�[4_y;
	float �ǐՃp�g�J�[_x,�ǐՃp�g�J�[_y;
	float ���s��_x, ���s��_y;
	float ���s��2_x, ���s��2_y;
	float _time = 1.0f;
	float _totalTime = 0.0f;
	float �X�s�[�h_x,�X�s�[�h_y;
	float ����_x, ����_y;
	float ����2_x, ����2_y;
	float �v���C���[�`��_x;

	int ���_state;
	int ���G_state;
	int ���G;
	int ���G2;
	int ���G�_��;
	int �Փ�_state;
	int ��b;
	int �^�C���b;
	int �����^�C���b;
	int �����^�C���b2;
	int �����^�C���b3;
	int �����^�C��_state;
	int �n�[�h�����^�C���b3;
	int �Փ˕\������;
	int �Փ˕\������2;
	int �X�R�A;
	int �X�R�A2;
	int �X�R�A3;
	int �n�C�X�R�A;
	int �n�[�h�n�C�X�R�A;
	int ���C�t;
	int �X�s�[�h;
	int �X�s�[�h2;
	int �X�s�[�h����;
	int �X�s�[�h�����b;
	int �X�s�[�h�����b2;
	int ����_state;
	int ����2_state;
	int �ǐ�_state;
	int �v���C���[_state;
	int �v���C���[����_state;
	int �ߕ�_state;
	int �ߕ�;
	int �ߕ�2;
	int ����_state;
	int ����;
	int ����2;
	int �_��;
	int �p�g�J�[�Ǖb��;
	int �p�g�J�[�Ǖb��2;
	int �p�g�J�[��_state;
	int �p�g�J�[�ǃ����_��;
	int ����_state;
	int �Փ˃G�t�F�N�g_x;
	int �Փ�, �Փ�2;
	int �Q�[�����[�h�ݒ�_state;
	int EX���[�h�b;
	int EX���[�h�b2;
	int EX���[�h�b3;
	int EX�^�C��_state;
	int �X�s�[�h�^�C��;
	int �X�s�[�h_state;
	int �v���C���[�`��_state;

	FONT �t�H���g�X�^�[�g;
	FONT �t�H���g;
	FONT �t�H���g2;
	FONT �t�H���g3;
	FONT �t�H���g4;
	FONT �t�H���g�������;
	FONT ���Ӄt�H���g;

	Color ����Color;

	MUSIC �Q�[���v���CBGM;
	SOUND �Փ�SE;
	SOUND �T�C����SE;
	SOUND3D �T�C����SE3D;
	SOUND �T�C����SE2;
	SOUND �T�C����SE3;
	SOUND3D �T�C����SE3D2;
	SOUND ���s��SE;
	SOUND �G���W���N��SE;
	SOUND �ʉ�SE;
	SOUND �㉺�ړ�SE;
	SOUND �㉺�ړ�SE2;
	SOUND ����SE;
	SOUND �V���b�^�[SE;

	Rect �v���C���[_collision;
	Rect �Ԏ�_collision;
	Rect ��_collision;
	Rect �ǃp�g�J�[_collision;
	Rect �ǃp�g�J�[2_collision;
	Rect �ǃp�g�J�[3_collision;
	Rect �ǃp�g�J�[4_collision;

	KeyboardState Keystate;
	KeyboardBuffer Key_buffer;
	GamePadState pad;
	GamePadBuffer pad_buffer;

	// �֐��錾

	void �^�C�g������();
	void �^�C�g��������();
	void �^�C�g���`��();
	void ���C������();
	void �����蔻�菈��();
	void �v���C���[����();
	void �G�l�~�[����();
	void �ǃG�l�~�[����();
	void ���C���`��();
	void �ǃG�l�~�[�`��();
	void �����������();
	void ��������`��();
	void �Q�[���I�[�o�[����();
	void �Q�[���I�[�o�[�`��();
	void �Q�[���N���A����();
	void �Q�[���N���A�`��();
	void ��Փx�ݒ菈��();
	void ��Փx�ݒ�`��();
};