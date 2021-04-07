// #include "Extension\DirectX11\DXGraphics11.hpp"
#include "StdAfx.h"
#include "GameMain.h"

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load all of your content.
/// Initialize will enumerate through any components and initialize them as well.
/// </summary>
bool GameMain::Initialize()
{
	// TODO: Add your initialization logic here
	WindowTitle(_T("ES Game Library"));

	//�Q�[���p�b�h������
	InputDevice.CreateGamePad(1);

	�Q�[���v���C�w�i = GraphicsDevice.CreateSpriteFromFile(_T("�Q�[���v���C���.png"));
	�X�^�[�g�w�i = GraphicsDevice.CreateSpriteFromFile(_T("�X�^�[�g���.png"));
	�N���A�w�i = GraphicsDevice.CreateSpriteFromFile(_T("�N���A���.png"));
	�Q�[���I�[�o�[�w�i = GraphicsDevice.CreateSpriteFromFile(_T("�Q�[���I�[�o�[���.png"));
	��Փx�ݒ�w�i = GraphicsDevice.CreateSpriteFromFile(_T("��Փx�ݒ���.png"));
	�Q�[���V�X�e���w�i = GraphicsDevice.CreateSpriteFromFile(_T("�Q�[���V�X�e��.png"));
	�Q�[����������w�i = GraphicsDevice.CreateSpriteFromFile(_T("�Q�[���������.png"));
	�v���C���[ = GraphicsDevice.CreateSpriteFromFile(_T("���@.png"));
	�v���C���[�� = GraphicsDevice.CreateSpriteFromFile(_T("���@�΂�1.png"));
	�v���C���[�� = GraphicsDevice.CreateSpriteFromFile(_T("���@�΂�2.png"));
	�Ԏ� = GraphicsDevice.CreateSpriteFromFile(_T("�Ԏ�.png"));
	�� = GraphicsDevice.CreateSpriteFromFile(_T("��.png"));
	�ǃp�g�J�[ = GraphicsDevice.CreateSpriteFromFile(_T("�p�g�J�[�΂�.png"));
	���s�� = GraphicsDevice.CreateSpriteFromFile(_T("���s��.png"));
	���s��2 = GraphicsDevice.CreateSpriteFromFile(_T("���s��2.png"));
	�ǐՃp�g�J�[ = GraphicsDevice.CreateSpriteFromFile(_T("�p�g�J�[.png"));
	�Փ˃G�t�F�N�g = GraphicsDevice.CreateSpriteFromFile(_T("�ԏՓ˃G�t�F�N�g.png"));
	���� = GraphicsDevice.CreateSpriteFromFile(_T("����.png"));
	����2 = GraphicsDevice.CreateSpriteFromFile(_T("����.png"));
	���z�g = GraphicsDevice.CreateSpriteFromFile(_T("���z�g.png"));
	�^�C���g = GraphicsDevice.CreateSpriteFromFile(_T("�^�C���g.png"));
	EX�^�C���g = GraphicsDevice.CreateSpriteFromFile(_T("EX�^�C���g.png"));
	�댯 = GraphicsDevice.CreateSpriteFromFile(_T("�댯.png"));
	�v���C���[2 = GraphicsDevice.CreateSpriteFromFile(_T("���@2.png"));
	�N���A��ʋ��z�g = GraphicsDevice.CreateSpriteFromFile(_T("�N���A��ʋ��z�g"));
	/*�t�H���g�X�^�[�g = GraphicsDevice.CreateSpriteFont(_T("MS�S�V�b�N"), 150);*/
	�t�H���g = GraphicsDevice.CreateSpriteFont(_T("MS�S�V�b�N"), 50);
	�t�H���g2 = GraphicsDevice.CreateSpriteFont(_T("MS�S�V�b�N"), 50);
	�t�H���g3 = GraphicsDevice.CreateSpriteFont(_T("MS�S�V�b�N"), 50);
	�t�H���g4 = GraphicsDevice.CreateSpriteFont(_T("MS�S�V�b�N"), 50);
	�t�H���g������� = GraphicsDevice.CreateSpriteFont(_T("MS�S�V�b�N"), 30);
	���Ӄt�H���g = GraphicsDevice.CreateSpriteFont(_T("�����ӂ����"), 100);

	�Q�[���v���CBGM = SoundDevice.CreateMusicFromFile(_T("���C��BGM.wav"));

	�Փ�SE = SoundDevice.CreateSoundFromFile(_T("�Փ�SE.wav"));
	���s��SE = SoundDevice.CreateSoundFromFile(_T("���s��SE.wav"));
	�G���W���N��SE = SoundDevice.CreateSoundFromFile(_T("�G���W����������.wav"));
	�ʉ�SE = SoundDevice.CreateSoundFromFile(_T("�ʉ�SE.wav"));
	�㉺�ړ�SE = SoundDevice.CreateSoundFromFile(_T("�㉺�ړ��u���[�LSE.wav"));
	�㉺�ړ�SE2 = SoundDevice.CreateSoundFromFile(_T("�㉺�ړ��u���[�LSE.wav"));
	����SE = SoundDevice.CreateSoundFromFile(_T("�Q�[���I�[�o�[����SE.wav"));
	�V���b�^�[SE = SoundDevice.CreateSoundFromFile(_T("�V���b�^�[SE.wav"));
	
	�T�C����SE = SoundDevice.CreateSoundFromFile(_T("�T�C����SE.wav"),true);
    �T�C����SE3D = �T�C����SE->GetSound3D();
	�T�C����SE2 = SoundDevice.CreateSoundFromFile(_T("�T�C����SE.wav"), true);
	�T�C����SE3D2 = �T�C����SE2->GetSound3D();
	�T�C����SE3 = SoundDevice.CreateSoundFromFile(_T("�T�C����SE.wav"));


	����Color = Color(255, 255, 255, 0);
	�_��_flag = true;
	�_�� = 0;
	�w�i_x = 0.0f;
	���_state = 0;
	���G_state = 0;
	���G = 0;
	���G2 = 0;
	�v���C���[_x = 500;
    �v���C���[_y = 370;
	�X�s�[�h_x = 0;
	�X�s�[�h_y = 0;
	�Ԏ�_x = 1300;
	�Ԏ�_y = 0;
	��_x = 500;
	��_y = 500;
	�ǐՃp�g�J�[_x = 100;
	�ǐՃp�g�J�[_y = 500;
	���s��_x = 1100;
	���s��_y = 280;
	���s��2_x = 400;
	���s��2_y = 280;
	��b = 0;
	�^�C���b = 60;
	�����^�C���b = 0;
	�����^�C���b2 = 0;
	�����^�C���b3 = 0;
	�n�[�h�����^�C���b3 = 0;
	�����^�C��_state = 0;
	�X�R�A = 100000000;
	�X�R�A2 = 0;
	�X�R�A3 = 0;
	�n�C�X�R�A = 0;
	�n�[�h�n�C�X�R�A = 0;
	�Փ�_state = 0;
	�Փ˕\������ = 0;
	�Փ˕\������2 = 0;
	�X�s�[�h���� = 1;
	�X�s�[�h�����b = 0;
	�X�s�[�h�����b2 = 0;
	����_x = 0;
	����_y = 0;
	����_state = 0;
	����2_x = 0;
	����2_y = 0;
	����2_state = 0;
	�ǐ�_state = 0;
	�v���C���[_state = 0;
	�v���C���[����_state = 0;
	�ߕ�_state = 0;
	�ߕ� = 0;
	�ߕ�2 = 0;
	����_state = 0;
	���� = 0;
	����2 = 0;
	�p�g�J�[�Ǖb�� = 0;
	�p�g�J�[�Ǖb��2 = 0;
	�p�g�J�[��_state = 0;
	�p�g�J�[�ǃ����_�� = 0;
	�ǃp�g�J�[_x = 1200;
	�ǃp�g�J�[2_x = 1200;
	�ǃp�g�J�[3_x = 1200;
	�ǃp�g�J�[4_x = 1200;
	�ǃp�g�J�[_y = 335;
	�ǃp�g�J�[2_y = 435;
	�ǃp�g�J�[3_y = 535;
	�ǃp�g�J�[4_y = 635;
	�Q�[�����[�h�ݒ�_state = 0;
	EX���[�h�b = 0;
	EX���[�h�b2 = 0;
	EX���[�h�b3 = 0;
	����_state = 0;
	�Փ˃G�t�F�N�g_x = 0;
	�Փ� = 0;
	�Փ�2 = 0;
	�X�s�[�h_state = 0;
	�X�s�[�h�^�C�� = 0;
	�v���C���[�`��_x = 0;
	�v���C���[�`��_state = 0;

	//�����l�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@ //�͈�
	/*�v���C���[_collision = Rect(�v���C���[_x + 15, �v���C���[_y + 25, �v���C���[_x + 120, �v���C���[_y + 65);
	�Ԏ�_collision = Rect(�Ԏ�_x + 5, �Ԏ�_y + 10, �Ԏ�_x + 105, �Ԏ�_y + 80);
	��_collision = Rect(��_x + 5, ��_y + 10, ��_x + 105, ��_y + 80);
	�ǃp�g�J�[_collision = Rect(�ǃp�g�J�[_x + 10, �ǃp�g�J�[_y + 15, �ǃp�g�J�[_x + 100, �ǃp�g�J�[_y + 80);
	�ǃp�g�J�[2_collision = Rect(�ǃp�g�J�[2_x + 10, �ǃp�g�J�[2_y + 15, �ǃp�g�J�[2_x + 100, �ǃp�g�J�[2_y + 80);
	�ǃp�g�J�[3_collision = Rect(�ǃp�g�J�[3_x + 10, �ǃp�g�J�[3_y + 15, �ǃp�g�J�[3_x + 100, �ǃp�g�J�[3_y + 80);
	�ǃp�g�J�[4_collision = Rect(�ǃp�g�J�[4_x + 10, �ǃp�g�J�[4_y + 15, �ǃp�g�J�[4_x + 100, �ǃp�g�J�[4_y + 80);*/

	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void GameMain::Finalize()
{
	// TODO: Add your finalization logic here

}

/// <summary>
/// Allows the game to run logic such as updating the world,
/// checking for collisions, gathering input, and playing audio.
/// </summary>
/// <returns>
/// Scene continued value.
/// </returns>
int GameMain::Update()
{
	// TODO: Add your update logic here

	//���ʏ���

	//�L�[�{�[�h
	Keystate = Keyboard->GetState();
	Key_buffer = Keyboard->GetBuffer();

	//�Q�[���p�b�h
	pad = GamePad(0)->GetState();
	pad_buffer = GamePad(0)->GetBuffer();

	�T�C����SE3D->SetPosition((�ǐՃp�g�J�[_x - 640) / 256, 0, 0); 128;

	if (�p�g�J�[�ǃ����_�� == 0) {
		�T�C����SE3D2->SetPosition((�ǃp�g�J�[_x - 640) / 256, 0, 0); 128;
	}
	else if(�p�g�J�[�ǃ����_�� == 1){
		�T�C����SE3D2->SetPosition((�ǃp�g�J�[_x - 640) / 256, 0, 0); 128;
	}
	else if (�p�g�J�[�ǃ����_�� == 2) {
		�T�C����SE3D2->SetPosition((�ǃp�g�J�[2_x - 640) / 256, 0, 0); 128;
	}
	else if (�p�g�J�[�ǃ����_�� == 3) {
		�T�C����SE3D2->SetPosition((�ǃp�g�J�[3_x - 640) / 256, 0, 0); 128;
	}
	else if (�p�g�J�[�ǃ����_�� == 4) {
		�T�C����SE3D2->SetPosition((�ǃp�g�J�[4_x - 640) / 256, 0, 0); 128;
	}

	//�����܂�

	if (���_state == �^�C�g�����) {
		�^�C�g��������();
		�^�C�g������();
	}
	else if (���_state == ���C�����) {
		���C������();
		�v���C���[����();
		�G�l�~�[����();
		�ǃG�l�~�[����();
		�����蔻�菈��();
	}
	else if (���_state == �������) {
		�����������();
	}
    else if (���_state == �Q�[���I�[�o�[���) {
		�Q�[���I�[�o�[����();
	}
	else if (���_state == �Q�[���N���A���) {
		�Q�[���N���A����();
	}
	else if (���_state == ��Փx�ݒ���) {
		��Փx�ݒ菈��();
	}

	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void GameMain::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_CornflowerBlue);

	GraphicsDevice.BeginScene();


	SpriteBatch.Begin();

	//�^�C�g�����
	if (���_state == 0) {
	�^�C�g���`��();
	}
	//�Q�[���v���C
	else if (���_state == 1) {
	���C���`��();
	�ǃG�l�~�[�`��();
	}
	//������@�m�F���
	else if (���_state == 2) {
	��������`��();
	}
	//�Q�[���I�[�o�[���
	else if (���_state == 3) {
	�Q�[���I�[�o�[�`��();
	}
	//�Q�[���N���A���
	else if (���_state == 4) {
	�Q�[���N���A�`��();
	}
	//�V���b�v���
	else if (���_state == 5) {
	��Փx�ݒ�`��();
	}

	SpriteBatch.End();

	GraphicsDevice.EndScene();

	Canvas canvas = GraphicsDevice.LockCanvas();

	Paint paint;

	paint.SetPaintColor(Color_Blue);
	canvas.DrawRect(�v���C���[_collision, paint);

	paint.SetPaintColor(Color_Yellow);
	canvas.DrawRect(�Ԏ�_collision, paint);

	paint.SetPaintColor(Color_Yellow);
	canvas.DrawRect(��_collision, paint);

	paint.SetPaintColor(Color_Red);
	canvas.DrawRect(�ǃp�g�J�[_collision, paint);

	paint.SetPaintColor(Color_Red);
	canvas.DrawRect(�ǃp�g�J�[2_collision, paint);

	paint.SetPaintColor(Color_Red);
	canvas.DrawRect(�ǃp�g�J�[3_collision, paint);

	paint.SetPaintColor(Color_Red);
	canvas.DrawRect(�ǃp�g�J�[4_collision, paint);

	GraphicsDevice.UnlockCanvas();
}

void GameMain::�^�C�g��������() {

	���G_state = 0;
	���G = 0;
	���G2 = 0;
	�v���C���[_x = 500;
	�v���C���[_y = 500;
	�Ԏ�_x = 1300;
	�Ԏ�_y = 385;
	��_x = 500;
	��_y = 650;
	�ǐՃp�g�J�[_x = 100;
	�ǐՃp�g�J�[_y = 500;
	���s��_x = 1100;
	���s��_y = 220;
	���s��2_x = 300;
	���s��2_y = 220;
	��b = 0;

	if (�Q�[�����[�h�ݒ�_state == 0) {
		�^�C���b = 60;
	}
	else if (�Q�[�����[�h�ݒ�_state == 1) {
		�^�C���b = 120;
	}

	�����^�C���b = 0;
	�����^�C���b2 = 0;
	�Փ�_state = 0;
	�Փ˕\������ = 0;
	�Փ˕\������2 = 0;
	�X�s�[�h���� = 1;
	�X�s�[�h�����b = 0;
	�X�s�[�h�����b2 = 0;
	����_x = 0;
	����_y = 0;
	����_state = 0;
	����2_x = 0;
	����2_y = 0;
	����2_state = 0;
	�ǐ�_state = 0;
	�v���C���[_state = 0;
	�v���C���[����_state = 0;
	�ߕ�_state = 0;
	�ߕ� = 0;
	�ߕ�2 = 0;
	����_state = 0;
	���� = 0;
	����2 = 0;
	�p�g�J�[�Ǖb�� = 0;
	�p�g�J�[�Ǖb��2 = 0;
	�p�g�J�[��_state = 0;
	�p�g�J�[�ǃ����_�� = 0;
	�ǃp�g�J�[_x = 1200;
	�ǃp�g�J�[2_x = 1200;
	�ǃp�g�J�[3_x = 1200;
	�ǃp�g�J�[4_x = 1200;
	�ǃp�g�J�[_y = 335;
	�ǃp�g�J�[2_y = 435;
	�ǃp�g�J�[3_y = 535;
	�ǃp�g�J�[4_y = 635;
	�X�s�[�h_state = 0;
	�X�s�[�h�^�C�� = 0;
	����Color = Color(255, 255, 255, 0);
	�_��_flag = true;
	�_�� = 0;
	����_state = 0;
	�Փ˃G�t�F�N�g_x = 0;
	�Փ� = 0;
	�Փ�2 = 0;
	EX���[�h�b = 0;
	EX���[�h�b2 = 0;
	�v���C���[�`��_x = 140;
	�v���C���[�`��_state = 0;
	�Q�[���v���CBGM->Stop();
	�T�C����SE->Stop();
	�T�C����SE2->Stop();
	�T�C����SE3->Stop();
	���s��SE->Stop();
	�Փ�SE->Stop();
	�ʉ�SE->Stop();
	����SE->Stop();
	�V���b�^�[SE->Stop();
	�㉺�ړ�SE->Stop();
	�㉺�ړ�SE2->Stop();
}

void GameMain::�^�C�g������() {

	if (Key_buffer.IsPressed(Keys_E) || pad_buffer.IsPressed(DIJOFS_BUTTON7)) {
		���_state = 1;
		�X�R�A = 100000000;
		�X�R�A2 = 0;
		�X�R�A3 = 0;
		�G���W���N��SE->Play();
	}
	if (Key_buffer.IsPressed(Keys_Q) || pad_buffer.IsPressed(DIJOFS_BUTTON6)) {
		���_state = 2;
		�G���W���N��SE->Play();
	}

	if (Key_buffer.IsPressed(Keys_F) || pad_buffer.IsPressed(DIJOFS_BUTTON1)) {
		���_state = 5;
	}

	//�N���A��ʂց@�f�o�b�N
	/*if (Key_buffer.IsPressed(Keys_U) || pad_buffer.IsPressed(DIJOFS_BUTTON1)) {
		���_state = 4;
		�X�R�A2 = 100000000;
	}*/
}

void GameMain::�^�C�g���`��() {

	SpriteBatch.Draw(*�X�^�[�g�w�i, Vector3(0.0f, 0.0f, 0.0f));
	/*SpriteBatch.DrawString(�t�H���g�X�^�[�g, Vector2(20, 10), Color(148, 0, 211), _T("dirty work"));*/
	SpriteBatch.DrawString(�t�H���g, Vector2(650, 660), Color(0, 255, 0), _T("Q ���̃Q�[���̐���"));
	if (�Q�[�����[�h�ݒ�_state == 0) {
		SpriteBatch.DrawString(�t�H���g2, Vector2(650, 560), Color(255, 0, 0), _T("�ŒZ���������^�C���F%d�b"), �����^�C���b3);
		SpriteBatch.DrawString(�t�H���g, Vector2(650, 510), Color(255, 255, 0), _T("�ő�擾���z�F%d��"), �n�C�X�R�A);
	}
	else if (�Q�[�����[�h�ݒ�_state == 1) {
		SpriteBatch.DrawString(�t�H���g2, Vector2(650, 560), Color(255, 0, 0), _T("�ŒZ���������^�C���F%d�b"), �n�[�h�����^�C���b3);
		SpriteBatch.DrawString(�t�H���g, Vector2(650, 510), Color(255, 255, 0), _T("�ő�擾���z�F%d��"),�n�[�h�n�C�X�R�A);
	}
	else if (�Q�[�����[�h�ݒ�_state == 2) {
		SpriteBatch.DrawString(�t�H���g2, Vector2(650, 560), Color(0, 0, 255), _T("�Œ������^�C���F%d�b"), EX���[�h�b3);
	}
	SpriteBatch.DrawString(�t�H���g3, Vector2(650, 610), Color(0, 200, 200), _T("F ��Փx�ݒ�"));
	SpriteBatch.DrawString(�t�H���g, Vector2(130, 270), Color(0, 255, 255), _T("E �Q�[���X�^�[�g"));

	if (�Q�[�����[�h�ݒ�_state == 0) {
		SpriteBatch.DrawString(�t�H���g, Vector2(10, 10), Color(255, 0, 255), _T("�m�[�}�����[�h"));
	}
	else if (�Q�[�����[�h�ݒ�_state == 1) {
		SpriteBatch.DrawString(�t�H���g, Vector2(10,10), Color(255, 0, 255), _T("�n�[�h���[�h"));
	}
	else if (�Q�[�����[�h�ݒ�_state == 2) {
		SpriteBatch.DrawString(�t�H���g, Vector2(10, 10), Color(255, 0, 255), _T("EX���[�h"));
	}
}

void GameMain::���C������() {

		//�����蔻��̊m�F
		/*�v���C���[_collision = Rect(�v���C���[_x + 15, �v���C���[_y + 25, �v���C���[_x + 120, �v���C���[_y + 65);
		�Ԏ�_collision = Rect(�Ԏ�_x + 5, �Ԏ�_y + 10, �Ԏ�_x + 105, �Ԏ�_y + 80);
		��_collision = Rect(��_x + 5, ��_y + 10, ��_x + 105, ��_y + 80);
		�ǃp�g�J�[_collision = Rect(�ǃp�g�J�[_x + 10, �ǃp�g�J�[_y + 15, �ǃp�g�J�[_x + 100, �ǃp�g�J�[_y + 80);
		�ǃp�g�J�[2_collision = Rect(�ǃp�g�J�[2_x + 10, �ǃp�g�J�[2_y + 15, �ǃp�g�J�[2_x + 100, �ǃp�g�J�[2_y + 80);
		�ǃp�g�J�[3_collision = Rect(�ǃp�g�J�[3_x + 10, �ǃp�g�J�[3_y + 15, �ǃp�g�J�[3_x + 100, �ǃp�g�J�[3_y + 80);
		�ǃp�g�J�[4_collision = Rect(�ǃp�g�J�[4_x + 10, �ǃp�g�J�[4_y + 15, �ǃp�g�J�[4_x + 100, �ǃp�g�J�[4_y + 80);*/

		if (!�Q�[���v���CBGM->IsPlaying())
			�Q�[���v���CBGM->Play();

		if (!�T�C����SE->IsPlaying())
			�T�C����SE->Play();

		if (!�T�C����SE2->IsPlaying())
			�T�C����SE2->Play();

		if (!���s��SE->IsPlaying())
			���s��SE->Play();

		if (�v���C���[_x <= �Ԏ�_x) {
			if (!�ʉ�SE->IsPlaying())
				�ʉ�SE->Play();
		}

		if (�v���C���[_x <= ��_x) {
			if (!�ʉ�SE->IsPlaying())
				�ʉ�SE->Play();
		}


		�w�i_x = �w�i_x - 38 - (�X�s�[�h���� / 100);
		if (�w�i_x <= -2720.0f) {
			�w�i_x = 0.0f;
		}

		if (�Q�[�����[�h�ݒ�_state == 0 || �Q�[�����[�h�ݒ�_state == 1) {

			if (�ߕ�_state == 0) {
				��b += 1;
				�X�R�A2 = �X�R�A;
				�X�R�A3 = �X�R�A2;

				//�Q�[���I�[�o�[
				if (�X�R�A < 0) {
					�X�R�A = 0;
					���_state = 3;
				}

				if (�v���C���[�`��_state == 0) {

					�v���C���[�`��_x = 1;

					if (��b == 1) {
						�v���C���[�`��_state = 1;
					}
				}
				else if (�v���C���[�`��_state == 1) {

					�v���C���[�`��_x = 140;

					if (��b == 1) {
						�v���C���[�`��_state = 0;
					}
				}

				if (��b == 60) {

					�^�C���b -= �X�s�[�h�^�C��;
					��b = 0;

					if (�X�s�[�h���� == 0) {
						�X�s�[�h_state = 0;
					}
					else if (�X�s�[�h���� == 20) {
						�X�s�[�h_state = 1;
					}
					else if (�X�s�[�h���� == 50) {
						�X�s�[�h_state = 2;
					}
				}

				if (�X�s�[�h_state == 0) {
					�X�s�[�h�^�C�� = 1;
				}
				else if (�X�s�[�h_state == 1) {
					�X�s�[�h�^�C�� = 2;
				}
				else if (�X�s�[�h_state == 2) {
					�X�s�[�h�^�C�� = 3;
				}

				//�N���A����
				if (�^�C���b <= -1) {
					�v���C���[_state = 2;
					����_state = 1;
				}
			}

			�����^�C���b += 1;

			if (�����^�C���b == 60) {
				�����^�C���b2 += 1;
				�����^�C���b = 0;
			}
		}
		else if (�Q�[�����[�h�ݒ�_state == 2) {
			EX���[�h�b += 1;

			if (EX���[�h�b == 60) {
				EX���[�h�b2 += 1;
				EX���[�h�b = 0;
			}

			if (�X�R�A < 0) {
				�X�R�A = 0;
				���_state = 3;
			}
		}

		if (�v���C���[_state == 2) {

			if (����_state == 1) {

				���� += 1;

				�v���C���[_x = �v���C���[_x + 10;
				�v���C���[����_state = 0;

				if (���� == 60) {
					����2 += 1;
					���� = 0;
				}

				if (����2 == 2) {
					���_state = 4;
				}
			}
		}

		if (�Q�[�����[�h�ݒ�_state == 0) {

			if (�^�C���b > 65) {
				�^�C���b = 65;
			}
		}
		else if (�Q�[�����[�h�ݒ�_state == 1) {

			if (�^�C���b > 125) {
				�^�C���b = 125;
			}
		}

		if (�_��_flag == true && �_�� >= 255)
		{
			�_��_flag = false;
		}

		if (�_��_flag == false && �_�� <= 0)
		{
			�_��_flag = true;
		}

		if (�_��_flag)
		{
			�_�� += 5;
		}
		else
		{
			�_�� -= 5;
		}
	}

void GameMain::�v���C���[����() {

	if (�v���C���[_state == 0) {

		if (Keystate.IsKeyDown(Keys_W) || pad.Buttons[3] != 0) {
			�X�s�[�h_y = �X�s�[�h_y - 0.2 - (�X�s�[�h���� / 1000);

			if (�X�s�[�h_y < -5) {
				�X�s�[�h_y = -5;
			}

			if (!�㉺�ړ�SE->IsPlaying())
				�㉺�ړ�SE->Play();

			�v���C���[����_state = 1;
		}

		if (Keystate.IsKeyDown(Keys_S) || pad.Buttons[0] != 0) {
			�X�s�[�h_y = �X�s�[�h_y + 0.2 + (�X�s�[�h���� / 1000);

			if (�X�s�[�h_y > 5) {
				�X�s�[�h_y = 5;
			}

			if (!�㉺�ړ�SE2->IsPlaying())
				�㉺�ړ�SE2->Play();

			�v���C���[����_state = 2;
		}

		if (Keystate.IsKeyUp(Keys_W) && pad.Buttons[0] == 0 && Keystate.IsKeyUp(Keys_S) && pad.Buttons[3] == 0) {
			if (�X�s�[�h_y > 0) {
				�X�s�[�h_y = �X�s�[�h_y - 0.1;
			}

			if (�X�s�[�h_y < 0) {
				�X�s�[�h_y = �X�s�[�h_y + 0.1;
			}

			�v���C���[����_state = 0;
		}

		if (�v���C���[_y > 295) {

			�X�s�[�h�����b = �X�s�[�h�����b + 1.0f;

			if (�X�s�[�h�����b == 30) {
				�X�s�[�h���� = �X�s�[�h���� + 1;
				�X�s�[�h�����b = 0;
			}
		}
		else if (�v���C���[_y < 295) {

			�X�s�[�h�����b2 = �X�s�[�h�����b2 + 2.0f;

			if (�X�s�[�h�����b2 == 30) {
				�X�s�[�h���� = �X�s�[�h���� - 1;
				�X�s�[�h�����b2 = 0;
			}
		}

		if (�X�s�[�h���� < -10) {
			�X�s�[�h���� = -10;
		}

		�v���C���[_x = �v���C���[_x + �X�s�[�h_x;
		�v���C���[_y = �v���C���[_y + �X�s�[�h_y;

		if (�v���C���[_x > 1000) {
			�v���C���[_x = 1000;
		}

		if (�v���C���[_x < 0) {
			�v���C���[_x = 0;
		}

		if (�v���C���[_y < 245) {
			�v���C���[_y = 245;
			�v���C���[����_state = 0;
		}

		if (�v���C���[_y > 650) {
			�v���C���[_y = 650;
			�v���C���[����_state = 0;
		}
	}
}

void GameMain::�G�l�~�[����() {

		�Ԏ�_x = �Ԏ�_x - MathHelper_Random(10, 20) - (�X�s�[�h���� / 100);
		if (�Ԏ�_x <= -130.0f) {
			�Ԏ�_x = 1300;
			MathHelper_Random(330, 650);
		}

		��_x = ��_x - MathHelper_Random(10, 20) - (�X�s�[�h���� / 100);
		if (��_x <= -130.0f) {
			��_x = 1300;
			��_y = MathHelper_Random(330, 650);
		}

		���s��_x = ���s��_x - 8 - (�X�s�[�h���� / 100);
		if (���s��_x <= -130.0f) {
			���s��_x = 1300;
			���s��_y = MathHelper_Random(245, 250);
		}

		���s��2_x = ���s��2_x - 8 - (�X�s�[�h���� / 100);
		if (���s��2_x <= -130.0f) {
			���s��2_x = 1300;
			���s��2_y = MathHelper_Random(245, 250);
		}

		if (�ǐՃp�g�J�[_y < �v���C���[_y) {
			�ǐՃp�g�J�[_y = �ǐՃp�g�J�[_y + 1;

			if (�ǐՃp�g�J�[_y == �v���C���[_y) {
				�ǐՃp�g�J�[_y = �v���C���[_y;
			}
		}
		else if (�ǐՃp�g�J�[_y > �v���C���[_y) {
			�ǐՃp�g�J�[_y = �ǐՃp�g�J�[_y - 1;

			if (�ǐՃp�g�J�[_y == �v���C���[_y) {
				�ǐՃp�g�J�[_y = �v���C���[_y;
			}
		}

		if (�Q�[�����[�h�ݒ�_state == 0) {

			if (�^�C���b > 55) {
				�ǐ�_state = 1;
			}
			else if (�^�C���b < 55) {
				�ǐ�_state = 2;
			}
		}
		else if (�Q�[�����[�h�ݒ�_state == 1) {

			if (�^�C���b > 115) {
				�ǐ�_state = 1;
			}
			else if (�^�C���b < 115) {
				�ǐ�_state = 2;
			}
		}

		if (�ǐ�_state == 1) {
			�ǐՃp�g�J�[_x = �ǐՃp�g�J�[_x + 0.1;
		}
		else if (�ǐ�_state == 2) {
			�ǐՃp�g�J�[_x = �ǐՃp�g�J�[_x - 0.01;
		}

		if (�ǐՃp�g�J�[_y < �v���C���[_x) {
			if (�ǐՃp�g�J�[_y > 650) {
				�ǐՃp�g�J�[_y = 650;
			}

			if (�ǐՃp�g�J�[_y < 295) {
				�ǐՃp�g�J�[_y = 295;
			}
		}
		else if (�ǐՃp�g�J�[_y > �v���C���[_x) {
			if (�ǐՃp�g�J�[_y > 650) {
				�ǐՃp�g�J�[_y = 650;
			}
		}
	}

void GameMain::�ǃG�l�~�[����() {

	if (����_state == 0) {

		�p�g�J�[�Ǖb�� += 1;

		if (�p�g�J�[�Ǖb�� == 60) {
			�p�g�J�[�Ǖb�� = 0;
			�p�g�J�[�Ǖb��2 += 1;
		}
		else if (�p�g�J�[�Ǖb��2 == 1) {
			�p�g�J�[�ǃ����_�� = MathHelper_Random(1, 4);
		}
		else if (�p�g�J�[�Ǖb��2 == 3) {
			�p�g�J�[��_state = 1;
			�ǃp�g�J�[_x = 1200;
			�ǃp�g�J�[2_x = 1200;
			�ǃp�g�J�[3_x = 1200;
			�ǃp�g�J�[4_x = 1200;
			�ǃp�g�J�[_y = 335;
			�ǃp�g�J�[2_y = 435;
			�ǃp�g�J�[3_y = 535;
			�ǃp�g�J�[4_y = 635;
		}
		else if (�p�g�J�[�Ǖb��2 == 5) {
			�p�g�J�[��_state = 2;
		}
		else if (�p�g�J�[�Ǖb��2 == 10) {
			�p�g�J�[�ǃ����_�� = 0;
			�p�g�J�[��_state = 3;
		}
		else if (�p�g�J�[�Ǖb��2 == 13) {
			�p�g�J�[�ǃ����_�� = MathHelper_Random(1, 4);
		}
		else if (�p�g�J�[�Ǖb��2 == 15) {
			�p�g�J�[��_state = 4;
			�ǃp�g�J�[_x = 1200;
			�ǃp�g�J�[2_x = 1200;
			�ǃp�g�J�[3_x = 1200;
			�ǃp�g�J�[4_x = 1200;
			�ǃp�g�J�[_y = 335;
			�ǃp�g�J�[2_y = 435;
			�ǃp�g�J�[3_y = 535;
			�ǃp�g�J�[4_y = 635;
		}
		else if (�p�g�J�[�Ǖb��2 == 20) {
			�p�g�J�[��_state = 5;
		}
		else if (�p�g�J�[�Ǖb��2 == 25) {
			�p�g�J�[�ǃ����_�� = 0;
			�p�g�J�[��_state = 6;
		}
		else if (�p�g�J�[�Ǖb��2 == 28) {
			�p�g�J�[�ǃ����_�� = MathHelper_Random(1, 4);
		}
		else if (�p�g�J�[�Ǖb��2 == 30) {
			�p�g�J�[��_state = 7;
			�ǃp�g�J�[_x = 1200;
			�ǃp�g�J�[2_x = 1200;
			�ǃp�g�J�[3_x = 1200;
			�ǃp�g�J�[4_x = 1200;
			�ǃp�g�J�[_y = 335;
			�ǃp�g�J�[2_y = 435;
			�ǃp�g�J�[3_y = 535;
			�ǃp�g�J�[4_y = 635;
		}
		else if (�p�g�J�[�Ǖb��2 == 35) {
			�p�g�J�[��_state = 8;
		}
		else if (�p�g�J�[�Ǖb��2 == 40) {
			�p�g�J�[�ǃ����_�� = 0;
			�p�g�J�[��_state = 9;
		}
		else if (�p�g�J�[�Ǖb��2 == 43) {
			�p�g�J�[�ǃ����_�� = MathHelper_Random(1, 4);
		}
		else if (�p�g�J�[�Ǖb��2 == 45) {
			�p�g�J�[��_state = 10;
			�ǃp�g�J�[_x = 1200;
			�ǃp�g�J�[2_x = 1200;
			�ǃp�g�J�[3_x = 1200;
			�ǃp�g�J�[4_x = 1200;
			�ǃp�g�J�[_y = 335;
			�ǃp�g�J�[2_y = 435;
			�ǃp�g�J�[3_y = 535;
			�ǃp�g�J�[4_y = 635;
		}
		else if (�p�g�J�[�Ǖb��2 == 50) {
			�p�g�J�[��_state = 11;
		}
		else if (�p�g�J�[�Ǖb��2 == 55) {
			�p�g�J�[�ǃ����_�� = 0;
			�p�g�J�[��_state = 12;
		}
		else if (�p�g�J�[�Ǖb��2 == 58) {
			�p�g�J�[�ǃ����_�� = MathHelper_Random(1, 4);
		}
		else if (�p�g�J�[�Ǖb��2 == 60) {
			�p�g�J�[��_state = 13;
			�ǃp�g�J�[_x = 1200;
			�ǃp�g�J�[2_x = 1200;
			�ǃp�g�J�[3_x = 1200;
			�ǃp�g�J�[4_x = 1200;
			�ǃp�g�J�[_y = 335;
			�ǃp�g�J�[2_y = 435;
			�ǃp�g�J�[3_y = 535;
			�ǃp�g�J�[4_y = 635;
		}
		else if (�p�g�J�[�Ǖb��2 == 65) {
		    �p�g�J�[��_state = 14;
		}
		else if (�p�g�J�[�Ǖb��2 == 70) {
		�p�g�J�[�ǃ����_�� = 0;
		�p�g�J�[��_state = 15;
		}
		else if (�p�g�J�[�Ǖb��2 == 73) {
		�p�g�J�[�ǃ����_�� = MathHelper_Random(1, 4);
		}
		else if (�p�g�J�[�Ǖb��2 == 75) {
		�p�g�J�[��_state = 16;
		�ǃp�g�J�[_x = 1200;
		�ǃp�g�J�[2_x = 1200;
		�ǃp�g�J�[3_x = 1200;
		�ǃp�g�J�[4_x = 1200;
		�ǃp�g�J�[_y = 335;
		�ǃp�g�J�[2_y = 435;
		�ǃp�g�J�[3_y = 535;
		�ǃp�g�J�[4_y = 635;
		}
		else if (�p�g�J�[�Ǖb��2 == 80) {
		�p�g�J�[��_state = 17;
		}
		else if (�p�g�J�[�Ǖb��2 == 85) {
		�p�g�J�[�ǃ����_�� = 0;
		�p�g�J�[��_state = 18;
		}
		else if (�p�g�J�[�Ǖb��2 == 88) {
		�p�g�J�[�ǃ����_�� = MathHelper_Random(1, 4);
		}
		else if (�p�g�J�[�Ǖb��2 == 90) {
		�p�g�J�[��_state = 19;
		�ǃp�g�J�[_x = 1200;
		�ǃp�g�J�[2_x = 1200;
		�ǃp�g�J�[3_x = 1200;
		�ǃp�g�J�[4_x = 1200;
		�ǃp�g�J�[_y = 335;
		�ǃp�g�J�[2_y = 435;
		�ǃp�g�J�[3_y = 535;
		�ǃp�g�J�[4_y = 635;
		}
		else if (�p�g�J�[�Ǖb��2 == 95) {
		�p�g�J�[��_state = 20;
		}
		else if (�p�g�J�[�Ǖb��2 == 100) {
		�p�g�J�[�ǃ����_�� = 0;
		�p�g�J�[��_state = 21;
		}
		else if (�p�g�J�[�Ǖb��2 == 103) {
		�p�g�J�[�ǃ����_�� = MathHelper_Random(1, 4);
		}
		else if (�p�g�J�[�Ǖb��2 == 105) {
		�p�g�J�[��_state = 22;
		�ǃp�g�J�[_x = 1200;
		�ǃp�g�J�[2_x = 1200;
		�ǃp�g�J�[3_x = 1200;
		�ǃp�g�J�[4_x = 1200;
		�ǃp�g�J�[_y = 335;
		�ǃp�g�J�[2_y = 435;
		�ǃp�g�J�[3_y = 535;
		�ǃp�g�J�[4_y = 635;
		}
		else if (�p�g�J�[�Ǖb��2 == 110) {
		�p�g�J�[��_state = 23;
		}
		else if (�p�g�J�[�Ǖb��2 == 115) {
		�p�g�J�[�ǃ����_�� = 0;
		�p�g�J�[��_state = 24;
		}
		else if (�p�g�J�[�Ǖb��2 == 120) {
		�p�g�J�[�Ǖb��2 = 85;
        }
		
		if (�p�g�J�[��_state == 2 || �p�g�J�[��_state == 5) {
			
			if (�p�g�J�[�ǃ����_�� == 1) {
				�ǃp�g�J�[_x = �ǃp�g�J�[_x - 10 - (�X�s�[�h���� / 100);
			}
			else if (�p�g�J�[�ǃ����_�� == 2) {
				�ǃp�g�J�[2_x = �ǃp�g�J�[2_x - 10 - (�X�s�[�h���� / 100);
			}
			else if (�p�g�J�[�ǃ����_�� == 3) {
				�ǃp�g�J�[3_x = �ǃp�g�J�[3_x - 10 - (�X�s�[�h���� / 100);
			}
			else if (�p�g�J�[�ǃ����_�� == 4) {
				�ǃp�g�J�[4_x = �ǃp�g�J�[4_x - 10 - (�X�s�[�h���� / 100);
			}
		}
		else if (�p�g�J�[��_state == 8 || �p�g�J�[��_state == 11) {

			if (�p�g�J�[�ǃ����_�� == 1) {
				�ǃp�g�J�[_x = �ǃp�g�J�[_x - 10 - (�X�s�[�h���� / 100);
				�ǃp�g�J�[2_x = �ǃp�g�J�[2_x - 10 - (�X�s�[�h���� / 100);
			}
			else if (�p�g�J�[�ǃ����_�� == 2) {
				�ǃp�g�J�[2_x = �ǃp�g�J�[2_x - 10 - (�X�s�[�h���� / 100);
				�ǃp�g�J�[4_x = �ǃp�g�J�[4_x - 10 - (�X�s�[�h���� / 100);
			}
			else if (�p�g�J�[�ǃ����_�� == 3) {
				�ǃp�g�J�[3_x = �ǃp�g�J�[3_x - 10 - (�X�s�[�h���� / 100);
				�ǃp�g�J�[_x = �ǃp�g�J�[_x - 10 - (�X�s�[�h���� / 100);
			}
			else if (�p�g�J�[�ǃ����_�� == 4) {
				�ǃp�g�J�[4_x = �ǃp�g�J�[4_x - 10 - (�X�s�[�h���� / 100);
				�ǃp�g�J�[3_x = �ǃp�g�J�[3_x - 10 - (�X�s�[�h���� / 100);
			}
		}
		else if (�p�g�J�[��_state == 14 || �p�g�J�[��_state == 17) {

			if (�p�g�J�[�ǃ����_�� == 1) {
				�ǃp�g�J�[_x = �ǃp�g�J�[_x - 10 - (�X�s�[�h���� / 100);
				�ǃp�g�J�[2_x = �ǃp�g�J�[2_x - 10 - (�X�s�[�h���� / 100);
				�ǃp�g�J�[3_x = �ǃp�g�J�[3_x - 10 - (�X�s�[�h���� / 100);
			}
			else if (�p�g�J�[�ǃ����_�� == 2) {
				�ǃp�g�J�[2_x = �ǃp�g�J�[2_x - 10 - (�X�s�[�h���� / 100);
				�ǃp�g�J�[4_x = �ǃp�g�J�[4_x - 10 - (�X�s�[�h���� / 100);
				�ǃp�g�J�[_x = �ǃp�g�J�[_x - 10 - (�X�s�[�h���� / 100);
			}
			else if (�p�g�J�[�ǃ����_�� == 3) {
				�ǃp�g�J�[3_x = �ǃp�g�J�[3_x - 10 - (�X�s�[�h���� / 100);
				�ǃp�g�J�[_x = �ǃp�g�J�[_x - 10 - (�X�s�[�h���� / 100);
				�ǃp�g�J�[4_x = �ǃp�g�J�[4_x - 10 - (�X�s�[�h���� / 100);
			}
			else if (�p�g�J�[�ǃ����_�� == 4) {
				�ǃp�g�J�[4_x = �ǃp�g�J�[4_x - 10 - (�X�s�[�h���� / 100);
				�ǃp�g�J�[3_x = �ǃp�g�J�[3_x - 10 - (�X�s�[�h���� / 100);
				�ǃp�g�J�[2_x = �ǃp�g�J�[2_x - 10 - (�X�s�[�h���� / 100);
			}
		}
		else if (�p�g�J�[��_state == 20 || �p�g�J�[��_state == 23) {

			if (�p�g�J�[�ǃ����_�� == 1) {
				�ǃp�g�J�[_x = �ǃp�g�J�[_x - 10 - (�X�s�[�h���� / 100);
				�ǃp�g�J�[2_x = �ǃp�g�J�[2_x - 10 - (�X�s�[�h���� / 100);
				�ǃp�g�J�[3_x = �ǃp�g�J�[3_x - 10 - (�X�s�[�h���� / 100);
				�ǃp�g�J�[4_x = �ǃp�g�J�[4_x - 10 - (�X�s�[�h���� / 100);
			}
			else if (�p�g�J�[�ǃ����_�� == 2) {
				�ǃp�g�J�[_x = �ǃp�g�J�[_x - 10 - (�X�s�[�h���� / 100);
				�ǃp�g�J�[2_x = �ǃp�g�J�[2_x - 10 - (�X�s�[�h���� / 100);
				�ǃp�g�J�[3_x = �ǃp�g�J�[3_x - 5 - (�X�s�[�h���� / 100);
				�ǃp�g�J�[4_x = �ǃp�g�J�[4_x - 5 - (�X�s�[�h���� / 100);
			}
			else if (�p�g�J�[�ǃ����_�� == 3) {
				�ǃp�g�J�[_x = �ǃp�g�J�[_x - 5 - (�X�s�[�h���� / 100);
				�ǃp�g�J�[2_x = �ǃp�g�J�[2_x - 5 - (�X�s�[�h���� / 100);
				�ǃp�g�J�[3_x = �ǃp�g�J�[3_x - 10 - (�X�s�[�h���� / 100);
				�ǃp�g�J�[4_x = �ǃp�g�J�[4_x - 10 - (�X�s�[�h���� / 100);
			}
			else if (�p�g�J�[�ǃ����_�� == 4) {
				�ǃp�g�J�[_x = �ǃp�g�J�[_x - 12 - (�X�s�[�h���� / 100);
				�ǃp�g�J�[2_x = �ǃp�g�J�[2_x - 9 - (�X�s�[�h���� / 100);
				�ǃp�g�J�[3_x = �ǃp�g�J�[3_x - 6 - (�X�s�[�h���� / 100);
				�ǃp�g�J�[4_x = �ǃp�g�J�[4_x - 3 - (�X�s�[�h���� / 100);
			}
		}
	}
}

void GameMain::�����蔻�菈��() {

	if (�v���C���[_state == 1) {

		if (�ߕ�_state == 1) {

			�ߕ� += 1;

			�v���C���[_x = �v���C���[_x + 3;
			�v���C���[_y = �v���C���[_y + 3;
			�v���C���[����_state = 2;

			if (�ߕ� == 60) {
				�ߕ�2 += 1;
				�ߕ� = 0;
			}

			if(�ߕ�2 == 3) {
				�X�R�A = 0;
			}
			else if (�ߕ�2 == 6) {
				���_state = 3;
			}
		}
	}
	else if (�v���C���[_state == 0) {

		if (���G_state == 1) {
			���G += 1;

			if (���G == 30) {
				���G2 += 1;
				���G = 0;
			}

			if (���G2 == 1) {
				���G = 0;
				���G2 = 0;
				���G_state = 0;
			}
		}

		if (�Փ�_state == 0) {
			�Փ˃G�t�F�N�g_x = 0;
			�Փ� = 0;
			�Փ�2 = 0;
		}
		else if (�Փ�_state == 1) {

			�Փ˕\������ += 1;

			if (�Փ˕\������ == 40) {
				�Փ˕\������2 += 1;
				�Փ˕\������ = 0;
			}

			if (�Փ˕\������2 == 1) {
				�Փ˕\������ = 0;
				�Փ˕\������2 = 0;
				�Փ�_state = 0;
			}

			�Փ� += 1;

			if (�Փ� == 10) {
				�Փ�2 += 1;
				�Փ� = 0;
			}

			if (�Փ�2 == 1) {
				�Փ˃G�t�F�N�g_x = 110;
			}
			else if (�Փ�2 == 2) {
				�Փ˃G�t�F�N�g_x = 220;
			}
			else if (�Փ�2 == 3) {
				�Փ˃G�t�F�N�g_x = 330;
			}
			else if (�Փ�2 == 4) {
				�Փ˃G�t�F�N�g_x = 440;
			}
		}

		if (����_state == 0) {
			����_x = �v���C���[_x;
			����_y = �v���C���[_y;
		}
		else if (����_state == 1) {

			����_x = ����_x - 10;

			if (����_x < -50) {
				����_state = 0;
			}
		}

		if (����2_state == 0) {
			����2_x = �v���C���[_x;
			����2_y = �v���C���[_y;
		}
		else if (����2_state == 1) {

			����2_x = ����2_x - 10;

			if (����2_x < -50) {
				����2_state = 0;
			}
		}

		if (���G_state == 0) {

			if (�v���C���[_x + 15 > �Ԏ�_x + 100.0f || �v���C���[_x + 125.0f < �Ԏ�_x + 5 ||
				�v���C���[_y + 25 > �Ԏ�_y + 75.0f || �v���C���[_y + 70.0f < �Ԏ�_y + 10) {
				// �������Ă��Ȃ�

			}
			else {
				// �������Ă���
				�X�R�A -= MathHelper_Random(3000000, 5000000);;
				���G_state = 1;
				�Փ�_state = 1;
				�X�s�[�h���� = 1;
				�X�s�[�h�����b = 0;
				����_state = 1;
				�^�C���b += 1;
				�X�s�[�h_state = 0;

				if (!�Փ�SE->IsPlaying())
					�Փ�SE->Play();
			}

			if (�v���C���[_x + 15 > ��_x + 100.0f || �v���C���[_x + 120.0f < ��_x + 10 ||
				�v���C���[_y + 25 > ��_y + 75.0f || �v���C���[_y + 65.0f < ��_y + 15) {
				// �������Ă��Ȃ�

			}
			else {
				// �������Ă���
				�X�R�A -= MathHelper_Random(3000000, 5000000);;
				���G_state = 1;
				�Փ�_state = 1;
				�X�s�[�h���� = 1;
				�X�s�[�h�����b = 0;
				����2_state = 1;
				�^�C���b += 1;
				�X�s�[�h_state = 0;

				if (!�Փ�SE->IsPlaying())
					�Փ�SE->Play();
			}

			if (�v���C���[_x > ���s��_x + 20.0f || �v���C���[_x + 120.0f < ���s��_x ||
				�v���C���[_y > ���s��_y + 80.0f || �v���C���[_y + 70.0f < ���s��_y) {
				// �������Ă��Ȃ�

			}
			else {
				// �������Ă���

			}

			if (�v���C���[_x > �ǐՃp�g�J�[_x + 140.0f || �v���C���[_x + 140.0f < �ǐՃp�g�J�[_x ||
				�v���C���[_y > �ǐՃp�g�J�[_y + 90.0f || �v���C���[_y + 88.0f < �ǐՃp�g�J�[_y) {
				// �������Ă��Ȃ�

			}
			else {
				// �������Ă���

				�ߕ�_state = 1;
				�v���C���[_state = 1;

				if (!�Փ�SE->IsPlaying())
					�Փ�SE->Play();

				if (!����SE->IsPlaying())
					����SE->Play();
			}

			/*�v���C���[_collision = Rect(�v���C���[_x + 15, �v���C���[_y + 25, �v���C���[_x + 120, �v���C���[_y + 65);
			�Ԏ�_collision = Rect(�Ԏ�_x + 5, �Ԏ�_y + 10, �Ԏ�_x + 105, �Ԏ�_y + 80);
			��_collision = Rect(��_x + 5, ��_y + 10, ��_x + 105, ��_y + 80);
			�ǃp�g�J�[_collision = Rect(�ǃp�g�J�[_x + 10, �ǃp�g�J�[_y + 15, �ǃp�g�J�[_x + 100, �ǃp�g�J�[_y + 80);
			�ǃp�g�J�[2_collision = Rect(�ǃp�g�J�[2_x + 10, �ǃp�g�J�[2_y + 15, �ǃp�g�J�[2_x + 100, �ǃp�g�J�[2_y + 80);
			�ǃp�g�J�[3_collision = Rect(�ǃp�g�J�[3_x + 10, �ǃp�g�J�[3_y + 15, �ǃp�g�J�[3_x + 100, �ǃp�g�J�[3_y + 80);
			�ǃp�g�J�[4_collision = Rect(�ǃp�g�J�[4_x + 10, �ǃp�g�J�[4_y + 15, �ǃp�g�J�[4_x + 100, �ǃp�g�J�[4_y + 80);*/

			if (�v���C���[_x + 15 > �ǃp�g�J�[_x + 100.0f || �v���C���[_x + 120.0f < �ǃp�g�J�[_x + 10 ||
				�v���C���[_y + 25 > �ǃp�g�J�[_y + 80.0f || �v���C���[_y + 65.0f < �ǃp�g�J�[_y + 15) {
				// �������Ă��Ȃ�

			}
			else {
				// �������Ă���

				�ߕ�_state = 1;
				�v���C���[_state = 1;

				if (!�Փ�SE->IsPlaying())
					�Փ�SE->Play();

				if (!����SE->IsPlaying())
					����SE->Play();
			}

			if (�v���C���[_x + 15 > �ǃp�g�J�[2_x + 100.0f || �v���C���[_x + 120.0f < �ǃp�g�J�[2_x + 10 ||
				�v���C���[_y + 25 > �ǃp�g�J�[2_y + 80.0f || �v���C���[_y + 65.0f < �ǃp�g�J�[2_y + 15) {
				// �������Ă��Ȃ�

			}
			else {
				// �������Ă���

				�ߕ�_state = 1;
				�v���C���[_state = 1;

				if (!�Փ�SE->IsPlaying())
					�Փ�SE->Play();

				if (!����SE->IsPlaying())
					����SE->Play();
			}

			if (�v���C���[_x + 15 > �ǃp�g�J�[3_x + 100.0f || �v���C���[_x + 120.0f < �ǃp�g�J�[3_x + 10 ||
				�v���C���[_y + 25 > �ǃp�g�J�[3_y + 80.0f || �v���C���[_y + 65.0f < �ǃp�g�J�[3_y + 15) {
				// �������Ă��Ȃ�

			}
			else {
				// �������Ă���

				�ߕ�_state = 1;
				�v���C���[_state = 1;

				if (!�Փ�SE->IsPlaying())
					�Փ�SE->Play();

				if (!����SE->IsPlaying())
					����SE->Play();
			}

			if (�v���C���[_x + 15 > �ǃp�g�J�[4_x + 100.0f || �v���C���[_x + 120.0f < �ǃp�g�J�[4_x + 10 ||
				�v���C���[_y + 25 > �ǃp�g�J�[4_y + 80.0f || �v���C���[_y + 65.0f < �ǃp�g�J�[4_y + 15) {
				// �������Ă��Ȃ�

			}
			else {
				// �������Ă���

				�ߕ�_state = 1;
				�v���C���[_state = 1;

				if (!�Փ�SE->IsPlaying())
					�Փ�SE->Play();

				if (!����SE->IsPlaying())
					����SE->Play();
			}

		}
	}
}

void GameMain::���C���`��() {

	SpriteBatch.Draw(*�Q�[���v���C�w�i, Vector3(�w�i_x, 0.0f, 3.0f));

	if (�v���C���[����_state == 0) {
		SpriteBatch.Draw(*�v���C���[, Vector3(�v���C���[_x, �v���C���[_y, 0.0f),RectWH(�v���C���[�`��_x, 0,140, 90));
	}
	else if (�v���C���[����_state == 1) {
		SpriteBatch.Draw(*�v���C���[��, Vector3(�v���C���[_x, �v���C���[_y, 0.0f));
	}
	else if (�v���C���[����_state == 2) {
		SpriteBatch.Draw(*�v���C���[��, Vector3(�v���C���[_x, �v���C���[_y, 0.0f));
	}

	SpriteBatch.Draw(*�Ԏ�, Vector3(�Ԏ�_x, �Ԏ�_y, 1.0f));
	SpriteBatch.Draw(*��, Vector3(��_x, ��_y, 1.0f));
	SpriteBatch.Draw(*���s��, Vector3(���s��_x, ���s��_y, 2.0f));
	SpriteBatch.Draw(*���s��2, Vector3(���s��2_x, ���s��2_y, 2.0f));
	SpriteBatch.Draw(*�ǐՃp�g�J�[, Vector3(�ǐՃp�g�J�[_x, �ǐՃp�g�J�[_y, 0.0f));
	SpriteBatch.Draw(*���z�g, Vector3(0.0f, 5.0f, 3.0f));

	if (�Փ�_state == 0) {
		SpriteBatch.DrawString(�t�H���g, Vector2(85, 18), Color(255, 255, 0), _T("%d��"), �X�R�A);
	}
	else if (�Փ�_state == 1) {
		SpriteBatch.DrawString(�t�H���g, Vector2(85, 18), Color(255, 0, 0), _T("%d��"), �X�R�A);
	}

	if (�Q�[�����[�h�ݒ�_state == 0 || �Q�[�����[�h�ݒ�_state == 1) {
		SpriteBatch.DrawString(�t�H���g2, Vector2(820, 22), Color(0, 0, 255), _T("%d�b"), �^�C���b);
		SpriteBatch.Draw(*�^�C���g, Vector3(500.0f, 0.0f, 3.0f));
	}
	else if (�Q�[�����[�h�ݒ�_state == 2) {
		SpriteBatch.DrawString(�t�H���g2, Vector2(700, 22), Color(0, 0, 255), _T("%d�b"), EX���[�h�b2);
		SpriteBatch.Draw(*EX�^�C���g, Vector3(600.0f, 0.0f, 3.0f));
	}

	SpriteBatch.DrawString(�t�H���g2, Vector2(1000, 22), Color(255, 0,0), _T("�X�s�[�h�F%d"), �X�s�[�h����);

	/*SpriteBatch.DrawString(�t�H���g2, Vector2(0, 200), Color(0, 0, 255), _T("�ǐՃp�g�J�[�X�s�[�h�F%f"), �ǐՃp�g�J�[_x);*/
	/*if (�ǐ�_state == 0||�ǐ�_state == 2) {
		SpriteBatch.DrawString(�t�H���g2, Vector2(0, 200), Color(0, 0, 255), _T("������"));
	}
	else if (�ǐ�_state == 1) {
		SpriteBatch.DrawString(�t�H���g2, Vector2(0, 200), Color(0, 0, 255), _T("�p�g�J�[�ڋߒ�"));
	}*/
	/*SpriteBatch.DrawString(�t�H���g2, Vector2(0, 250), Color(0, 0, 255), _T("��ԁF%d"), �p�g�J�[��_state);
	SpriteBatch.DrawString(�t�H���g2, Vector2(0, 300), Color(0, 0, 255), _T("�b���F%d"), �p�g�J�[�Ǖb��2);*/

	if (�Փ�_state == 1 && �v���C���[_state == 0) {
		//SpriteBatch.Draw(*�Փ˃G�t�F�N�g, Vector3((�v���C���[_x + 15),�v���C���[_y, 0.0f),RectWH(�Փ˃G�t�F�N�g_x,0,110,70));
		SpriteBatch.Draw(*�Փ˃G�t�F�N�g, Vector3((�v���C���[_x - 30),(�v���C���[_y + 90),0.0f), RectWH(�Փ˃G�t�F�N�g_x, 0, 110, 70), 1.0f, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector2(2, -2));
	}

	if (�ߕ�_state == 0) {

		if (����_state == 1) {
			SpriteBatch.Draw(*����, Vector3((����_x - 5), (����_y - 50), 0.0f));
		}

		if (����2_state == 1) {
			SpriteBatch.Draw(*����2, Vector3((����2_x - 5), (����2_y - 50), 0.0f));
		}
	}
}

void GameMain::�ǃG�l�~�[�`��() {

	if (�p�g�J�[��_state == 1 || �p�g�J�[��_state == 4) {

		if (�p�g�J�[�ǃ����_�� == 1) {
			SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 330), Color(255, 0, 0, �_��));
			SpriteBatch.Draw(*�댯, Vector3(1100, 330, 0.0f));
		}
		else if (�p�g�J�[�ǃ����_�� == 2) {
			SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 430), Color(255, 0, 0, �_��));
			SpriteBatch.Draw(*�댯, Vector3(1100, 430, 0.0f));
		}
		else if (�p�g�J�[�ǃ����_�� == 3) {
			SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 530), Color(255, 0, 0, �_��));
			SpriteBatch.Draw(*�댯, Vector3(1100, 530, 0.0f));
		}
		else if (�p�g�J�[�ǃ����_�� == 4) {
			SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 630), Color(255, 0, 0, �_��));
			SpriteBatch.Draw(*�댯, Vector3(1100, 630, 0.0f));
		}
	}
	else if (�p�g�J�[��_state == 2 || �p�g�J�[��_state == 5) {

		if (�p�g�J�[�ǃ����_�� == 1) {
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[_x, �ǃp�g�J�[_y, 0.0f));
		}
		else if (�p�g�J�[�ǃ����_�� == 2) {
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[2_x, �ǃp�g�J�[2_y, 0.0f));
		}
		else if (�p�g�J�[�ǃ����_�� == 3) {
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[3_x, �ǃp�g�J�[3_y, 0.0f));
		}
		else if (�p�g�J�[�ǃ����_�� == 4) {
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[4_x, �ǃp�g�J�[4_y, 0.0f));
		}
	}
	else if (�p�g�J�[��_state == 7 || �p�g�J�[��_state == 10) {

		if (�p�g�J�[�ǃ����_�� == 1) {
			SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 330), Color(255, 0, 0, �_��));
			SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 430), Color(255, 0, 0, �_��));
			SpriteBatch.Draw(*�댯, Vector3(1100, 330, 0.0f));
			SpriteBatch.Draw(*�댯, Vector3(1100, 430, 0.0f));
		}
		else if (�p�g�J�[�ǃ����_�� == 2) {
			SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 430), Color(255, 0, 0, �_��));
			SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 630), Color(255, 0, 0, �_��));
			SpriteBatch.Draw(*�댯, Vector3(1100, 430, 0.0f));
			SpriteBatch.Draw(*�댯, Vector3(1100, 630, 0.0f));
		}
		else if (�p�g�J�[�ǃ����_�� == 3) {
			SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 530), Color(255, 0, 0, �_��));
			SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 330), Color(255, 0, 0, �_��));
			SpriteBatch.Draw(*�댯, Vector3(1100, 530, 0.0f));
			SpriteBatch.Draw(*�댯, Vector3(1100, 330, 0.0f));
		}
		else if (�p�g�J�[�ǃ����_�� == 4) {
			SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 630), Color(255, 0, 0, �_��));
			SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 530), Color(255, 0, 0, �_��));
			SpriteBatch.Draw(*�댯, Vector3(1100, 630, 0.0f));
			SpriteBatch.Draw(*�댯, Vector3(1100, 530, 0.0f));
		}
	}
	else if (�p�g�J�[��_state == 8 || �p�g�J�[��_state == 11) {

		if (�p�g�J�[�ǃ����_�� == 1) {
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[_x, �ǃp�g�J�[_y, 0.0f));
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[2_x, �ǃp�g�J�[2_y, 0.0f));
		}
		else if (�p�g�J�[�ǃ����_�� == 2) {
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[2_x, �ǃp�g�J�[2_y, 0.0f));
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[4_x, �ǃp�g�J�[4_y, 0.0f));
		}
		else if (�p�g�J�[�ǃ����_�� == 3) {
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[3_x, �ǃp�g�J�[3_y, 0.0f));
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[_x, �ǃp�g�J�[_y, 0.0f));
		}
		else if (�p�g�J�[�ǃ����_�� == 4) {
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[4_x, �ǃp�g�J�[4_y, 0.0f));
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[3_x, �ǃp�g�J�[3_y, 0.0f));
		}
	}
	else if (�p�g�J�[��_state == 13 || �p�g�J�[��_state == 16) {

		if (�p�g�J�[�ǃ����_�� == 1) {
			SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 330), Color(255, 0, 0, �_��));
			SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 430), Color(255, 0, 0, �_��));
			SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 530), Color(255, 0, 0, �_��));
			SpriteBatch.Draw(*�댯, Vector3(1100, 330, 0.0f));
			SpriteBatch.Draw(*�댯, Vector3(1100, 430, 0.0f));
			SpriteBatch.Draw(*�댯, Vector3(1100, 530, 0.0f));
		}
		else if (�p�g�J�[�ǃ����_�� == 2) {
			SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 430), Color(255, 0, 0, �_��));
			SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 630), Color(255, 0, 0, �_��));
			SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 330), Color(255, 0, 0, �_��));
			SpriteBatch.Draw(*�댯, Vector3(1100, 430, 0.0f));
			SpriteBatch.Draw(*�댯, Vector3(1100, 630, 0.0f));
			SpriteBatch.Draw(*�댯, Vector3(1100, 330, 0.0f));
		}
		else if (�p�g�J�[�ǃ����_�� == 3) {
			SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 530), Color(255, 0, 0, �_��));
			SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 330), Color(255, 0, 0, �_��));
			SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 630), Color(255, 0, 0, �_��));
			SpriteBatch.Draw(*�댯, Vector3(1100, 530, 0.0f));
			SpriteBatch.Draw(*�댯, Vector3(1100, 330, 0.0f));
			SpriteBatch.Draw(*�댯, Vector3(1100, 630, 0.0f));
		}
		else if (�p�g�J�[�ǃ����_�� == 4) {
			SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 630), Color(255, 0, 0, �_��));
			SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 530), Color(255, 0, 0, �_��));
			SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 430), Color(255, 0, 0, �_��));
			SpriteBatch.Draw(*�댯, Vector3(1100, 630, 0.0f));
			SpriteBatch.Draw(*�댯, Vector3(1100, 530, 0.0f));
			SpriteBatch.Draw(*�댯, Vector3(1100, 430, 0.0f));
		}
	}
	else if (�p�g�J�[��_state == 14 || �p�g�J�[��_state == 17) {

		if (�p�g�J�[�ǃ����_�� == 1) {
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[_x, �ǃp�g�J�[_y, 0.0f));
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[2_x, �ǃp�g�J�[2_y, 0.0f));
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[3_x, �ǃp�g�J�[3_y, 0.0f));
		}
		else if (�p�g�J�[�ǃ����_�� == 2) {
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[2_x, �ǃp�g�J�[2_y, 0.0f));
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[4_x, �ǃp�g�J�[4_y, 0.0f));
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[_x, �ǃp�g�J�[_y, 0.0f));
		}
		else if (�p�g�J�[�ǃ����_�� == 3) {
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[3_x, �ǃp�g�J�[3_y, 0.0f));
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[_x, �ǃp�g�J�[_y, 0.0f));
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[4_x, �ǃp�g�J�[4_y, 0.0f));
		}
		else if (�p�g�J�[�ǃ����_�� == 4) {
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[4_x, �ǃp�g�J�[4_y, 0.0f));
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[3_x, �ǃp�g�J�[3_y, 0.0f));
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[2_x, �ǃp�g�J�[2_y, 0.0f));
		}
	}
	else if (�p�g�J�[��_state == 19 || �p�g�J�[��_state == 22) {

	if (�p�g�J�[�ǃ����_�� == 1) {
		SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 330), Color(255, 0, 0, �_��));
		SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 430), Color(255, 0, 0, �_��));
		SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 530), Color(255, 0, 0, �_��));
		SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 630), Color(255, 0, 0, �_��));
		SpriteBatch.Draw(*�댯, Vector3(1100, 330, 0.0f));
		SpriteBatch.Draw(*�댯, Vector3(1100, 430, 0.0f));
		SpriteBatch.Draw(*�댯, Vector3(1100, 530, 0.0f));
		SpriteBatch.Draw(*�댯, Vector3(1100, 630, 0.0f));
	}
	    else if (�p�g�J�[�ǃ����_�� == 2) {
		SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(900, 330), Color(255, 0, 0, �_��));
		SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(900, 430), Color(255, 0, 0, �_��));
		SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 530), Color(255, 0, 0, �_��));
		SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 630), Color(255, 0, 0, �_��));
		SpriteBatch.Draw(*�댯, Vector3(1000, 330, 0.0f));
		SpriteBatch.Draw(*�댯, Vector3(1000, 430, 0.0f));
		SpriteBatch.Draw(*�댯, Vector3(1100, 530, 0.0f));
		SpriteBatch.Draw(*�댯, Vector3(1100, 630, 0.0f));
	}
	    else if (�p�g�J�[�ǃ����_�� == 3) {
		SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 330), Color(255, 0, 0, �_��));
		SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 430), Color(255, 0, 0, �_��));
		SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(900, 530), Color(255, 0, 0, �_��));
		SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(900, 630), Color(255, 0, 0, �_��));
		SpriteBatch.Draw(*�댯, Vector3(1100, 330, 0.0f));
		SpriteBatch.Draw(*�댯, Vector3(1100, 430, 0.0f));
		SpriteBatch.Draw(*�댯, Vector3(1000, 530, 0.0f));
		SpriteBatch.Draw(*�댯, Vector3(1000, 630, 0.0f));
	}
	    else if (�p�g�J�[�ǃ����_�� == 4) {
		SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(900, 330), Color(255, 0, 0, �_��));
		SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(950, 430), Color(255, 0, 0, �_��));
		SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1000, 530), Color(255, 0, 0, �_��));
		SpriteBatch.DrawString(���Ӄt�H���g, _T("!!"), Vector2(1050, 630), Color(255, 0, 0, �_��));
		SpriteBatch.Draw(*�댯, Vector3(1150, 330, 0.0f));
		SpriteBatch.Draw(*�댯, Vector3(1100, 430, 0.0f));
		SpriteBatch.Draw(*�댯, Vector3(1050, 530, 0.0f));
		SpriteBatch.Draw(*�댯, Vector3(1000, 630, 0.0f));
	}
	}
	else if (�p�g�J�[��_state == 20 || �p�g�J�[��_state == 23) {

		if (�p�g�J�[�ǃ����_�� == 1) {
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[_x, �ǃp�g�J�[_y, 0.0f));
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[2_x, �ǃp�g�J�[2_y, 0.0f));
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[3_x, �ǃp�g�J�[3_y, 0.0f));
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[4_x, �ǃp�g�J�[4_y, 0.0f));
		}
		else if (�p�g�J�[�ǃ����_�� == 2) {
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[_x, �ǃp�g�J�[_y, 0.0f));
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[2_x, �ǃp�g�J�[2_y, 0.0f));
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[3_x, �ǃp�g�J�[3_y, 0.0f));
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[4_x, �ǃp�g�J�[4_y, 0.0f));
		}
		else if (�p�g�J�[�ǃ����_�� == 3) {
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[_x, �ǃp�g�J�[_y, 0.0f));
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[2_x, �ǃp�g�J�[2_y, 0.0f));
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[3_x, �ǃp�g�J�[3_y, 0.0f));
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[4_x, �ǃp�g�J�[4_y, 0.0f));
		}
		else if (�p�g�J�[�ǃ����_�� == 4) {
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[_x, �ǃp�g�J�[_y, 0.0f));
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[2_x, �ǃp�g�J�[2_y, 0.0f));
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[3_x, �ǃp�g�J�[3_y, 0.0f));
			SpriteBatch.Draw(*�ǃp�g�J�[, Vector3(�ǃp�g�J�[4_x, �ǃp�g�J�[4_y, 0.0f));
		}
	}
}

void GameMain::�����������() {

	�w�i_x = �w�i_x - 38 - (�X�s�[�h���� / 100);
	if (�w�i_x <= -2720.0f) {
		�w�i_x = 0.0f;
	}

	if (Keystate.IsKeyDown(Keys_W) || pad.Buttons[3] != 0) {
		�X�s�[�h_y = �X�s�[�h_y - 0.2 - (�X�s�[�h���� / 1000);

		if (�X�s�[�h_y < -10) {
			�X�s�[�h_y = -10;
		}

		if (!�㉺�ړ�SE->IsPlaying())
			�㉺�ړ�SE->Play();

		�v���C���[����_state = 1;
	}

	if (Keystate.IsKeyDown(Keys_S) || pad.Buttons[0] != 0) {
		�X�s�[�h_y = �X�s�[�h_y + 0.2 + (�X�s�[�h���� / 1000);

		if (�X�s�[�h_y > 10) {
			�X�s�[�h_y = 10;
		}

		if (!�㉺�ړ�SE2->IsPlaying())
			�㉺�ړ�SE2->Play();

		�v���C���[����_state = 2;
	}

	if (Keystate.IsKeyUp(Keys_W) && pad.Buttons[0] == 0 && Keystate.IsKeyUp(Keys_S) && pad.Buttons[3] == 0) {
		if (�X�s�[�h_y > 0) {
			�X�s�[�h_y = �X�s�[�h_y - 0.1;
		}

		if (�X�s�[�h_y < 0) {
			�X�s�[�h_y = �X�s�[�h_y + 0.1;
		}

		�v���C���[����_state = 0;
	}

	if (�v���C���[_y > 295) {

		�X�s�[�h�����b = �X�s�[�h�����b + 1.0f;

		if (�X�s�[�h�����b == 30) {
			�X�s�[�h���� = �X�s�[�h���� + 1;
			�X�s�[�h�����b = 0;
		}
	}
	else if (�v���C���[_y < 295) {

		�X�s�[�h�����b2 = �X�s�[�h�����b2 + 2.0f;

		if (�X�s�[�h�����b2 == 30) {
			�X�s�[�h���� = �X�s�[�h���� - 1;
			�X�s�[�h�����b2 = 0;
		}
	}

	if (�X�s�[�h���� < -10) {
		�X�s�[�h���� = -10;
	}

	�v���C���[_x = �v���C���[_x + �X�s�[�h_x;
	�v���C���[_y = �v���C���[_y + �X�s�[�h_y;

	if (�v���C���[_x > 1000) {
		�v���C���[_x = 1000;
	}

	if (�v���C���[_x < 0) {
		�v���C���[_x = 0;
	}

	if (�v���C���[_y < 245) {
		�v���C���[_y = 245;
		�v���C���[����_state = 0;
		if (�X�s�[�h_y <= -6)
			�X�s�[�h_y = -5;
	}

	if (�v���C���[_y > 650) {
		�v���C���[_y = 650;
		�v���C���[����_state = 0;
		if (�X�s�[�h_y >= 6)
			�X�s�[�h_y = 5;
	}

	if (����_state == 0) {

		if (Key_buffer.IsPressed(Keys_E) || pad_buffer.IsPressed(DIJOFS_BUTTON7)) {
			���_state = 0;
			�G���W���N��SE->Stop();
		}

		if (Key_buffer.IsPressed(Keys_Q) || pad_buffer.IsPressed(DIJOFS_BUTTON7)) {
			����_state = 1;
		}
	}
	else if (����_state == 1) {

		if (Key_buffer.IsPressed(Keys_E) || pad_buffer.IsPressed(DIJOFS_BUTTON7)) {
			����_state = 0;
		}

	}

	if (!���s��SE->IsPlaying())
		���s��SE->Play();
}

void GameMain::��������`��() {

	SpriteBatch.Draw(*�Q�[���v���C�w�i, Vector3(�w�i_x, 0.0f, 10.0f));

	if (�v���C���[_state == 0) {

		if (�v���C���[����_state == 0) {
			SpriteBatch.Draw(*�v���C���[2, Vector3(�v���C���[_x, �v���C���[_y, 0.0f));
		}
		else if (�v���C���[����_state == 1) {
			SpriteBatch.Draw(*�v���C���[��, Vector3(�v���C���[_x, �v���C���[_y, 0.0f));
		}
		else if (�v���C���[����_state == 2) {
			SpriteBatch.Draw(*�v���C���[��, Vector3(�v���C���[_x, �v���C���[_y, 0.0f));
		}
	}

	if (����_state == 0) {
		SpriteBatch.Draw(*�Q�[����������w�i, Vector3(0.0f, 0.0f, 0.0f));
		SpriteBatch.DrawString(�t�H���g, Vector2(30, 10), Color(255, 0, 0), _T("Q �Q�[���V�X�e���@�@�@�@�@�@   �@   �@�@�@    E �^�C�g���֖߂�"));
		SpriteBatch.DrawString(�t�H���g, Vector2(30, 70), Color(255, 0, 0), _T("�Q�[���v���C���̑�����@"));
		SpriteBatch.DrawString(�t�H���g, Vector2(30, 120), Color(255, 0, 0), _T("�L�[�{�[�h: ��ւ̈ړ� W, ���ւ̈ړ� S"));
		SpriteBatch.DrawString(�t�H���g, Vector2(30, 170), Color(255, 0, 0), _T("�Q�[���p�b�h: ��ւ̈ړ� 3�{�^��, ���ւ̈ړ� 0�{�^��"));
		SpriteBatch.DrawString(�t�H���g, Vector2(30, 220), Color(255, 0, 0), _T("E�L�[ =  7�{�^��, Q�L�[ = 6�{�^��, F�L�[ = 1�{�^��"));
	}
	else if (����_state == 1) {
		SpriteBatch.Draw(*�Q�[���V�X�e���w�i, Vector3(0.0f, 0.0f, 0.0f));
		SpriteBatch.DrawString(�t�H���g�������, Vector2(30, 10), Color(124, 252, 0), _T("�Q�[���V�X�e���̐���"));
		SpriteBatch.DrawString(�t�H���g�������, Vector2(30, 40), Color(255, 241, 0), _T("�� = �X�R�A�A���C�t�B�G�ɏՓ˂��邱�ƂŌ���A�O�ɂȂ�����Q�[���I�[�o�[�B"));
		SpriteBatch.DrawString(�t�H���g�������, Vector2(30, 70), Color(148, 0, 211), _T("�^�C�� = ���Ԍo�߂Ō����Ă����A�^�C�����O�ɂȂ�����Q�[���N���A�B"));
		SpriteBatch.DrawString(�t�H���g�������, Vector2(30, 100), Color(255, 0, 0), _T("�G = �p�g�J�[�A��ʎԁB�������Ă����v = ���s�ҁB"));
		SpriteBatch.DrawString(�t�H���g�������, Vector2(30, 130), Color(255, 140, 0), _T("�G�����������Ή������Ă����A�G�Ȃǂ̈ړ��X�s�[�h�������Ȃ�A�v���C���[�̑��삪�����Ȃ�A"));
		SpriteBatch.DrawString(�t�H���g�������, Vector2(30, 160), Color(255, 140, 0), _T("�^�C���̌���b����������B�����͓G�ƏՓ˂��Ȃ��̂ň��u�����X�s�[�h���x���Ȃ�A�^�C����"));
		SpriteBatch.DrawString(�t�H���g�������, Vector2(30, 190), Color(255, 140, 0), _T("�����Ă����B�^�C����55�b�𒴂���ƌ������p�g�J�[���ڋ߂��Ă���B���̃p�g�J�[�ɓ�������"));
		SpriteBatch.DrawString(�t�H���g�������, Vector2(30, 220), Color(255, 140, 0), _T("�ꍇ�̓Q�[���I�[�o�[�ƂȂ�B��莞�Ԃŕǂ̃p�g�J�[�������_���i�S�p�^�[��)�ŏo������B"));
		SpriteBatch.DrawString(�t�H���g�������, Vector2(30, 250), Color(255, 140, 0), _T("�o������ꏊ�́y!!�z���\�����ꂽ���B���Ԃ��o�ĂΌo�قǂ��̃p�g�J�[�͑����o������B"));
		SpriteBatch.DrawString(�t�H���g�������, Vector2(30, 280), Color(255, 140, 0), _T("���̃p�g�J�[�ɓ��������ꍇ�͑ߕ߂���ăQ�[���I�[�o�[�ƂȂ�B"));
		SpriteBatch.DrawString(�t�H���g�������, Vector2(30, 310), Color(255, 140, 0), _T("�X�s�[�h30�ȏ�ň�b�œ�b����B�X�s�[�h50�ȏ�ň�b�ŎO�b����B�@�@�@�@E �����ʂɖ߂�"));
	}
}

void GameMain::�Q�[���I�[�o�[����() {

	�Q�[���v���CBGM->Stop();
	�T�C����SE->Stop();
	�T�C����SE2->Stop();
	���s��SE->Stop();
	�Փ�SE->Stop();
	�ʉ�SE->Stop();

	if (!�T�C����SE3->IsPlaying())
		�T�C����SE3->Play();

	if (!�V���b�^�[SE->IsPlaying())
		�V���b�^�[SE->Play();

	if (�n�C�X�R�A < �X�R�A3) {
		�n�C�X�R�A = �X�R�A3;
	}

	if(�Q�[�����[�h�ݒ�_state == 2) {

		if (EX���[�h�b3 < EX���[�h�b2) {
			EX���[�h�b3 = EX���[�h�b2;
		}
	}

	if (Key_buffer.IsPressed(Keys_E) || pad_buffer.IsPressed(DIJOFS_BUTTON7)) {
		���_state = 0;
	}
}

void GameMain::�Q�[���I�[�o�[�`��() {

	SpriteBatch.Draw(*�Q�[���I�[�o�[�w�i, Vector3(0.0f, 0.0f, 0.0f));
	SpriteBatch.DrawString(�t�H���g, Vector2(0, 20), Color(0, 255, 0), _T("�X�R�A�F%d"), �X�R�A2);
	SpriteBatch.DrawString(�t�H���g2, Vector2(0, 100), Color(0, 0, 255), _T("�^�C���F%d�b"),EX���[�h�b2);
	SpriteBatch.DrawString(�t�H���g3, Vector2(900, 640), Color(255, 255, 0), _T("E �^�C�g���֖߂�"));
}

void GameMain::�Q�[���N���A����() {

	�Q�[���v���CBGM->Stop();
	�T�C����SE->Stop();
	�T�C����SE2->Stop();
	���s��SE->Stop();
	�Փ�SE->Stop();
	�ʉ�SE->Stop();

	if (�Q�[�����[�h�ݒ�_state == 0) {

		if (�����^�C��_state == 0) {
			�����^�C���b3 = �����^�C���b2;
			�����^�C��_state = 1;
		}
		else if (�����^�C��_state == 1) {

			if (�����^�C���b2 < �����^�C���b3) {
				�����^�C���b3 = �����^�C���b2;
			}
		}

		if (�n�C�X�R�A < �X�R�A3) {
			�n�C�X�R�A = �X�R�A3;
		}
	}
	if (�Q�[�����[�h�ݒ�_state == 1) {

		if (�����^�C��_state == 0) {
			�n�[�h�����^�C���b3 = �����^�C���b2;
			�����^�C��_state = 1;
		}
		else if (�����^�C��_state == 1) {

			if (�����^�C���b2 < �n�[�h�����^�C���b3) {
				�n�[�h�����^�C���b3 = �����^�C���b2;
			}
		}

		if (�n�[�h�n�C�X�R�A < �X�R�A3) {
			�n�[�h�n�C�X�R�A = �X�R�A3;
		}
	}

	if (Key_buffer.IsPressed(Keys_E) || pad_buffer.IsPressed(DIJOFS_BUTTON7)) {
		���_state = 0;
	}
}

void GameMain::�Q�[���N���A�`��() {

	SpriteBatch.Draw(*�N���A�w�i, Vector3(0.0f, 0.0f, 0.0f));
	SpriteBatch.Draw(*�N���A��ʋ��z�g, Vector3(460.0f, 160.0f, 0.0f));
	SpriteBatch.DrawString(�t�H���g, Vector2(430, 185), Color(255, 255, 0), _T("��V:%d��"), �X�R�A2);
	SpriteBatch.DrawString(�t�H���g2, Vector2(0, 640), Color(0, 0, 255), _T("����̓��������^�C���F%d�b"),�����^�C���b2);
	SpriteBatch.DrawString(�t�H���g, Vector2(900, 640), Color(255, 0, 0), _T("E �^�C�g���֖߂�"));
}

void GameMain::��Փx�ݒ菈��() {

	if (�Q�[�����[�h�ݒ�_state == 0) {

		if (Key_buffer.IsPressed(Keys_W) || pad_buffer.IsPressed(DIJOFS_BUTTON3)) {
			�Q�[�����[�h�ݒ�_state = 1;
		}
	}
	else if (�Q�[�����[�h�ݒ�_state == 1) {

		if (Key_buffer.IsPressed(Keys_W) || pad_buffer.IsPressed(DIJOFS_BUTTON3)) {
			�Q�[�����[�h�ݒ�_state = 2;
		}
	}
	else if (�Q�[�����[�h�ݒ�_state == 2) {

		if (Key_buffer.IsPressed(Keys_W) || pad_buffer.IsPressed(DIJOFS_BUTTON3)) {
			�Q�[�����[�h�ݒ�_state = 0;
		}
	}

	if (Key_buffer.IsPressed(Keys_E) || pad_buffer.IsPressed(DIJOFS_BUTTON7)) {
		���_state = 0;
	}
}

void GameMain::��Փx�ݒ�`��() {

	SpriteBatch.Draw(*��Փx�ݒ�w�i, Vector3(0.0f, 0.0f, 0.0f));
	/*SpriteBatch.DrawString(�t�H���g3, Vector2(10, 50), Color(255, 140, 0), _T("�^�C���̐ݒ�(60 or 120) ���m�[�}�����[�h�̂ݓK���B"));
	SpriteBatch.DrawString(�t�H���g3, Vector2(10, 100), Color(255, 140, 0), _T("W �ŕύX�B���݂̃^�C�� = % d"),�^�C���b�ݒ�);*/
	SpriteBatch.DrawString(�t�H���g3, Vector2(10, 50), Color(255, 140, 0), _T("�Q�[�����[�h�̐ݒ�"));

	if (�Q�[�����[�h�ݒ�_state == 0) {
		SpriteBatch.DrawString(�t�H���g3, Vector2(10, 100), Color(255, 140, 0), _T("W �ŕύX�B���݂̃Q�[�����[�h = �m�[�}�����[�h"));
	}
	else if (�Q�[�����[�h�ݒ�_state == 1) {
		SpriteBatch.DrawString(�t�H���g3, Vector2(10, 100), Color(255, 140, 0), _T("W �ŕύX�B���݂̃Q�[�����[�h = �n�[�h���[�h"));
	}
	else if (�Q�[�����[�h�ݒ�_state == 2) {
		SpriteBatch.DrawString(�t�H���g3, Vector2(10, 100), Color(255, 140, 0), _T("W �ŕύX�B���݂̃Q�[�����[�h = EX���[�h"));
	}

	SpriteBatch.DrawString(�t�H���g3, Vector2(10, 150), Color(255, 140, 0), _T("�m�[�}�����[�h = ��{�I�ȃQ�[�����[�h�B"));
	SpriteBatch.DrawString(�t�H���g3, Vector2(10, 200), Color(255, 140, 0), _T("�n�[�h���[�h = �m�[�}�����[�h���^�C����60�b�������Q�[�����[�h�B"));
	SpriteBatch.DrawString(�t�H���g3, Vector2(10, 250), Color(255, 140, 0), _T("EX���[�h = �ǂꂾ�������������ł��邩��ڎw���Q�[�����[�h�B"));
	SpriteBatch.DrawString(�t�H���g3, Vector2(900, 640), Color(0, 255, 0), _T("E �^�C�g���֖߂�"));
}