// #include "Extension\DirectX11\DXGraphics11.hpp"
#include "StdAfx.h"
#include "GameMain.h"

int GameMain::score = 0;
int GameMain::perfect_ = 0;
int GameMain::good_ = 0;
int GameMain::miss_ = 0;

#include <fstream>

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load all of your content.
/// Initialize will enumerate through any components and initialize them as well.
/// </summary>
bool GameMain::Initialize()
{
	DefaultFont = GraphicsDevice.CreateDefaultFont();

	GraphicsDevice.SetRenderState(NormalizeNormals_Enable);
	//GraphicsDevice.SetRenderState(Specular_Enable);
	//GraphicsDevice.SetRenderState(CullMode_None);

	����Initialize();
	iwai_Initialize();
	�R��_Initialize();

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
int GameMain::Update()
{
	����Main();
	iwai_Update();
	�R��_Update();
	//�����蔻�蓯�m�̋����𑪂��Ĕ���
	if (�J�n_state == 5)
	{
		return GAME_SCENE(new clearScene);
	}
	//���ؗp
	if (key_buf.IsPressed(Keys_A))
	{
		return GAME_SCENE(new clearScene);
	}

	return 0;

}
void GameMain::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_CornflowerBlue);

	GraphicsDevice.BeginScene();

	�R��_Draw();

	SpriteBatch.Begin();

	����Draw();
	iwai_Draw();

	SpriteBatch.End();

	GraphicsDevice.EndScene();

	Canvas canvas = GraphicsDevice.LockCanvas();

	Paint paint;

	//paint.SetPaintColor(Color_Blue);
	//canvas.DrawRect(miss_collision, paint);
	//paint.SetPaintColor(Color_Red);
	//canvas.DrawRect(good_collision, paint);
	//paint.SetPaintColor(Color_Green);
	//canvas.DrawRect(perfect_collision, paint);
	//paint.SetPaintColor(Color_Blue);
	//canvas.DrawRect(Tv_collision, paint);
	//paint.SetPaintColor(Color_Blue);
	//canvas.DrawRect(�����蔻��_collision, paint);
	//paint.SetPaintColor(Color_Blue);
	//canvas.DrawRect(����e���r_collision, paint);
	for (int i = 0; i < ���̐�; i++) {

		//paint.SetPaintColor(Color_Blue);
		//canvas.DrawRect(�K�X��_collision[i], paint);
		if (��_state[i] == 1) {
		//	paint.SetPaintColor(Color_Red);
		//	canvas.DrawRect(�e���r_collision[i], paint);
		}
		else if (��_state[i] == 2) {
		//	paint.SetPaintColor(Color_Red);
		//	canvas.DrawRect(�J����_collision[i], paint);
		}
		else if (��_state[i] == 3) {
		//	paint.SetPaintColor(Color_Red);
		//	canvas.DrawRect(�d�q�����W_collision[i], paint);
		}
	}
	GraphicsDevice.UnlockCanvas();
}
void GameMain::iwai_Initialize() {
	player = GraphicsDevice.CreateSpriteFromFile(_T("�v���C���[�L����_20.png"));
	player_swing = GraphicsDevice.CreateSpriteFromFile(_T("player2.png"));
	map = GraphicsDevice.CreateSpriteFromFile(_T("map.png"));
	perfect = GraphicsDevice.CreateSpriteFromFile(_T("perfect.png"));
	good = GraphicsDevice.CreateSpriteFromFile(_T("good.png"));
	miss = GraphicsDevice.CreateSpriteFromFile(_T("miss.png"));
	life = GraphicsDevice.CreateSpriteFromFile(_T("life.png"));
	Tv = GraphicsDevice.CreateSpriteFromFile(_T("Tv.png"));
//	good_point = GraphicsDevice.CreateSpriteFromFile(_T("good_point.png"));
//	perfect_point = GraphicsDevice.CreateSpriteFromFile(_T("Perfect_point.png"));
	circle = GraphicsDevice.CreateSpriteFromFile(_T("circle.png"));
	hit_point = GraphicsDevice.CreateSpriteFromFile(_T("hit_point.png"));
	good_se = SoundDevice.CreateSoundFromFile(_T("good.wav"));
	perfect_se = SoundDevice.CreateSoundFromFile(_T("perfect.wav"));
	miss_se = SoundDevice.CreateSoundFromFile(_T("��U��.wav"));
	ready = GraphicsDevice.CreateSpriteFromFile(_T("ready.png"));
	go = GraphicsDevice.CreateSpriteFromFile(_T("go.png"));
	txt = GraphicsDevice.CreateSpriteFont(_T("ContinueAL"), 50);
	player_x = 150;
	player_y = 350;
	swing_flg = 0;
	Tv_x = 1200;
	Tv_y = 400;
	life_y = 0;
	clip_x = 0;
	perfect_x = 280;
	perfect_y = 400;
	good_x = 300;
	good_y = 400;
	miss_x = 300;
	miss_y = 400;
	GameMain::score = 0;
	swing_flg = false;
	Tv_alpha = 1;
	hard_speed = 1;
	big_go = 1;
	alpha_go = 1;
	combo = 0;
	GameMain::perfect_ = 0;
	GameMain::good_ = 0;
	GameMain::miss_ = 0;
	for (int i = 0; i < ���̐�; i++)
	{
		hitcount[i] = false;
		big[i] = 1.1;
		circle_alpha[i] = 0;
		�e���r_aplha[i] = 1;
		�J����_aplha[i] = 1;
		�d�q�����W_aplha[i] = 1;
	}
}
void GameMain::iwai_Draw() {
	// TODO: Add your drawing code here
	//GraphicsDevice.Clear(Color_CornflowerBlue);

	//GraphicsDevice.BeginScene();
	
	//SpriteBatch.Begin();
	SpriteBatch.Draw(*map, Vector3(0, 0, 0));
	SpriteBatch.Draw(*Tv, Vector3(Tv_x, Tv_y, 0), Tv_alpha);
//	SpriteBatch.Draw(*good_point, Vector3(good_x, good_y, 0));
//	SpriteBatch.Draw(*perfect_point, Vector3(perfect_x, perfect_y, 0));
	SpriteBatch.Draw(*hit_point, Vector3(300, 400, -100));
	for (int i = 0; i < ���̐�; i++)
	{
		SpriteBatch.Draw(*circle, Vector3(200, 300, -10), circle_alpha[i], Vector3(0, 0, 1), Vector3(200, 200, 0), Vector2(big[i], big[i]));
	}
	SpriteBatch.Draw(*player, Vector3(player_x, player_y, 0), RectWH(clip_x, 0, 350, 300));
	if (hit_test == 1)SpriteBatch.Draw(*perfect, Vector3(300, 400, 0));
	if (hit_test == 2)SpriteBatch.Draw(*good, Vector3(280, 400, 0));
	if (hit_test == 3)SpriteBatch.Draw(*miss, Vector3(280, 400, 0));
	SpriteBatch.DrawString(DefaultFont, Vector2(350, 0), Color(0, 0, 0), _T("����:%f"), range);
	SpriteBatch.DrawString(DefaultFont, Vector2(350, 20), Color(0, 0, 0), _T("�^�C��:%d"), ��b);
	SpriteBatch.DrawString(DefaultFont, Vector2(350, 40), Color(0, 0, 0), _T("�X�R�A:%d"), score);
	SpriteBatch.DrawString(DefaultFont, Vector2(350, 60), Color(0, 0, 0), _T("�j��:%f"), explosion->GetTrackPosition(0));
	if(combo >= 2)SpriteBatch.DrawString(txt, Vector2(0, 40), Color(255, 162,235), _T("%d�R���{"), combo);
	if(count >1430)SpriteBatch.Draw(*ready, Vector3(400, 160, 0));
	if(count <=1430 && count >= 1320)SpriteBatch.Draw(*go, Vector3(430,160, 0),alpha_go, Vector3(0, 0,0), Vector3(122, 112, 0), Vector2(big_go, big_go));
}
void GameMain::iwai_Update() {

	count--;

	if (titleScene::hard == 2)
	{
		for (int i = 0; i < ���̐�; i++)
		{
			circle_alpha[i] = 0;
		}
	}
	good_collision = Rect(good_x, good_y, good_x + 200.0f, good_y + 200.0f);
	perfect_collision = Rect(perfect_x + 70, perfect_y, perfect_x + 170.0f, perfect_y + 200.0f);
	miss_collision = Rect(miss_x , miss_y + 0, miss_x + 300.0f, Tv_y + 200.0f);
		if (key_buf.IsPressed(Keys_Space) && swing_flg == false)
		{
			for (int i = 0; i < ���̐�; i++)
			{
				swing_flg = true;
				if (perfect_collision.Intersect(�e���r_collision[i]) && hitcount[i] == false|| perfect_collision.Intersect(�J����_collision[i]) && hitcount[i] == false|| perfect_collision.Intersect(�d�q�����W_collision[i]) && hitcount[i] == false)
				{
					combo++;
					hit_test = 1;
					score += 250 + combo*50 ;
					hitcount[i] = true;
					perfect_se->Play();
					explosion->SetTrackPosition(0, 0);
					explosion->SetTrackEnable(0, true);
					�e���r_aplha[i] = 0;
					�J����_aplha[i] = 0;
					�d�q�����W_aplha[i] = 0;
					perfect_++;
				}
				else if (good_collision.Intersect(�e���r_collision[i]) && hitcount[i] == false || good_collision.Intersect(�J����_collision[i]) && hitcount[i] == false || good_collision.Intersect(�d�q�����W_collision[i]) && hitcount[i] == false)
				{
					combo++;
					hit_test = 2;
					score += 500 + combo * 50;
					hitcount[i] = true;
					good_se->Play();
					explosion->SetTrackEnable(0, true);
					�e���r_aplha[i] = 0;
					�J����_aplha[i] = 0;
					�d�q�����W_aplha[i] = 0;
					good_++;
				}
				else if (miss_collision.Intersect(�e���r_collision[i]) && hitcount[i] == false || miss_collision.Intersect(�J����_collision[i]) && hitcount[i] == false || miss_collision.Intersect(�d�q�����W_collision[i]) && hitcount[i] == false)
				{
					if (titleScene::hard == 2)
					{
					}
					else
					{
						hit_test = 3;
						miss_se->Play();
						combo = 0;
						hitcount[i] = true;
						�e���r_aplha[i] = 0;
						�J����_aplha[i] = 0;
						�d�q�����W_aplha[i] = 0;
						miss_++;
					}
				}
			}
		}

	//if (keyboard.IsKeyUp(Keys_Space) && swing_flg == true)
	//{
	//	clip_x = 0;
	//	hit_test = 0;
	//	swing_flg = false;
	//}
	range = Tv_x - player_x;
	if (swing_flg == true)
	{
		clip_x += 350;
	}
	if (clip_x >= 6650)
	{
		clip_x = 0;
		hit_test = 0;
		swing_flg = false;
	}
	for (int i = 0; i < ���̐�; i++)
	{
		if (big[i] <= 0)
		{
			big[i] = 0;
		}
	}
	if (count <=1430)
	{
		big_go += 0.025;
		alpha_go -= 0.01;
	}
	if (alpha_go <= 0)
	{
		alpha_go = 0;
	}
}
void GameMain::����Initialize() {

	�w�i = GraphicsDevice.CreateSpriteFromFile(_T("�w�i.png"));
	iwai_Initialize();

	�w�i = GraphicsDevice.CreateSpriteFromFile(_T("�w�i.png"));
	�v���C���[ = GraphicsDevice.CreateSpriteFromFile(_T("�v���C���[.png"));
	�e���r = GraphicsDevice.CreateSpriteFromFile(_T("�e���r.png"));
	�J���� = GraphicsDevice.CreateSpriteFromFile(_T("�J����.png"));
	�d�q�����W = GraphicsDevice.CreateSpriteFromFile(_T("�d�q�����W.png"));
	�����蔻�� = GraphicsDevice.CreateSpriteFromFile(_T("�����蔻��.png"));
	�t�H���g = GraphicsDevice.CreateSpriteFont(_T("MS�S�V�b�N"), 50);
	����e���r = GraphicsDevice.CreateSpriteFromFile(_T("����e���r.png"));
	�K�X�� = GraphicsDevice.CreateSpriteFromFile(_T("�K�X��.png"));

	MediaManager.Attach(GraphicsDevice);

	���[�r�[ = MediaManager.CreateMediaFromFile(_T("���{�b�g�H��.mp3"));

	�J�������x = 15 ;
	�d�q�����W���x = 6 / titleScene::hard;
	�e���r���x = 10 * titleScene::hard;
	����e���r���x = 5 * titleScene::hard;
	�b = 0;
	��b = 0;
	�J�n_state = 0;
	���[�r�[���� = 0;
	�f�o�b�N = 0;
	����e���r�A�Ő� = 15 * titleScene::hard;
	����e���r_state = 0;
	�t�H���g_state = 0;

	for (int i = 0; i < ���̐�; i++) {
		�S�[��[i] = 100 + (150 * i);
		�e���r_x[i] = 0;
		�e���r_y[i] = 400;
		�J����_x[i] = 0;
		�J����_y[i] = 400;
		�d�q�����W_x[i] = 0;
		�d�q�����W_y[i] = 400;
		�K�X��_x[i] = 0;
		�K�X��_y[i] = 400;
		//�e���r����_state[i] = 0;
		�X�s�[�h_y[i] = 7;
		�V�[�^[i] = 0;
		t[i] = 0;
	}

	��_state[0] = 1;

	for (int i = 1; i < ���̐�; i++) {
		��_state[i] = MathHelper_Random(1, 3);
	}

	�v���C���[_x = 100;
	�v���C���[_y = 400;
	�����蔻��_x = 200;
	�����蔻��_y = 500;
	����e���r_x = 1000;
	����e���r_y = 200;
	//�e���r���� = 5;
	�|�C���g[0] = Vector3(1280, 400, 0);
	�|�C���g[1] = Vector3(800, 300, 0);
	�|�C���g[2] = Vector3(700, 300, 0);
	�|�C���g[3] = Vector3(500, 400, 0);


	/*std::ifstream game_file("�Q�[���f�[�^.txt");
	std::string dummy_line;

	game_file >> �^�C�~���O[0];

	game_file >> �^�C�~���O[1];

	game_file >> �^�C�~���O[2];

	game_file >> �^�C�~���O[3];

	game_file >> �^�C�~���O[4];*/
}

void GameMain::����Main() {

	keyboard = Keyboard->GetState();
	key_buf = Keyboard->GetBuffer();
	// TODO: Add your update logic here

	���[�r�[���� = ���[�r�[->GetPosition() / 100000;

	�b += 1;

	if (�b == 60) {
		��b += 1;
		�b = 0;
	}

	if (��b == 3) {
		�J�n_state = 1;
	}
	else if (��b == 45) {
		�J�n_state = 2;
		�t�H���g_state = 1;
	}
	else if (��b == 53) {
		���[�r�[->Stop();
	}
	else if (��b == 55) {
		�J�n_state = 4;
	}
	else if (��b == 58) {
		�J�n_state = 5;
	}

	if (�J�n_state == 1 || �J�n_state == 2) {

		���[�r�[->Play();

		for (int i = 0; i < ���̐�; i++) {

			�����蔻��_collision = Rect(�����蔻��_x, �����蔻��_y, �����蔻��_x + 150, �����蔻��_y + 90);

			if (��_state[i] == 1) {
				�e���r_x[i] = �v���C���[_x + (�S�[��[i] - ���[�r�[����) * �e���r���x;
				�e���r_collision[i] = Rect(�e���r_x[i], �e���r_y[i], �e���r_x[i] + 100, �e���r_y[i] + 250);
				if (�e���r_x[i] < 1280)
				{
					big[i] -= 0.0138;
					circle_alpha[i] = 0.5;
				}
			}
			else if (��_state[i] == 2) {
				�J����_x[i] = �v���C���[_x + (�S�[��[i] - ���[�r�[����) * �J�������x;
				�J����_collision[i] = Rect(�J����_x[i], �J����_y[i], �J����_x[i] + 100, �J����_y[i] + 70);

				if (�J����_x[i] < 1280) {
					Vector3 bezier = Vector3_Bezier(�|�C���g[0], �|�C���g[1], �|�C���g[2], �|�C���g[3], t[i]);
					�J����_x[i] = bezier.x;
					�J����_y[i] = bezier.y;
					t[i] = t[i] + 0.02f * titleScene::hard;
					�J����_collision[i] = Rect(bezier.x, bezier.y, bezier.x + 60, bezier.y + 64);
					big[i] -= 0.013;
					circle_alpha[i] = 0.5;
				}
			}
			else if (��_state[i] == 3) {
				�d�q�����W_x[i] = �v���C���[_x + (�S�[��[i] - ���[�r�[����) * �d�q�����W���x;
				�d�q�����W_collision[i] = Rect(�d�q�����W_x[i] - 3, �d�q�����W_y[i], �d�q�����W_x[i] + 100, �d�q�����W_y[i] + 150);

				if (�d�q�����W_x[i] < 1280) {
						big[i] -= 0.0085;
						circle_alpha[i] = 0.5;
					�d�q�����W_x[i] = �d�q�����W_x[i] - 2;
					////                                             �����������h�b�g�����@�@���ŏ��̕`��ʒu�@ 
					�d�q�����W_y[i] = MathHelper_Sin(�V�[�^[i]) * 90 * titleScene::hard + 400;
					�V�[�^[i] = �V�[�^[i] + 1;
				}
			}
			else if (��_state[i] == 4) {
				�K�X��_x[i] = �v���C���[_x + (�S�[��[i] - ���[�r�[����) * �d�q�����W���x;
				�K�X��_collision[i] = Rect(�K�X��_x[i], �K�X��_y[i], �K�X��_x[i] + 75, �K�X��_y[i] + 150);
				if (�K�X��_x[i] < 1280)
				{
					big[i] -= 0.0138;
					circle_alpha[i] = 0.5;
				}
			}

			if (�J�n_state == 1) {

				if (�e���r_x[i] < -400) {
					��_state[i] = 0;
					//�e���r����_state[i] = 0;
					�X�s�[�h_y[i] = 0;
				}

				if (�J����_x[i] < -400) {
					��_state[i] = 0;
					//�e���r����_state[i] = 0;
					�X�s�[�h_y[i] = 0;
				}

				if (�J����_y[i] > 1000) {
					��_state[i] = 0;
					//�e���r����_state[i] = 0;
					�X�s�[�h_y[i] = 0;
				}

				if (�d�q�����W_x[i] < -400) {
					��_state[i] = 0;
					//�e���r����_state[i] = 0;
					�X�s�[�h_y[i] = 0;
				}

				if (�K�X��_x[i] < -400) {
					��_state[i] = 0;
					//�e���r����_state[i] = 0;
					�X�s�[�h_y[i] = 0;
				}
			}
			else if (�J�n_state == 2) {

				if (�e���r_x[i] < -500) {
					��_state[i] = 0;
					//�e���r����_state[i] = 0;
					�J�n_state = 3;
				}

				if (�J����_x[i] < -500) {
					��_state[i] = 0;
					//�e���r����_state[i] = 0;
					�J�n_state = 3;
				}

				if (�J����_y[i] < 900) {
					��_state[i] = 0;
					//�e���r����_state[i] = 0;
					�X�s�[�h_y[i] = 0;
					�J�n_state = 3;
				}

				if (�d�q�����W_x[i] < -500) {
					��_state[i] = 0;
					//�e���r����_state[i] = 0;
					�J�n_state = 3;
				}

				if (�K�X��_x[i] < -500) {
					��_state[i] = 0;
					//�e���r����_state[i] = 0;
					�J�n_state = 3;
				}
			}
		}
	}
	else if (�J�n_state == 3) {
		����e���r_collision = Rect(����e���r_x, ����e���r_y, ����e���r_x + 150, ����e���r_y + 500);
		����e���r_x = ����e���r_x - ����e���r���x;

		if (����e���r_state == 0) {

			if (key_buf.IsPressed(Keys_Space)) {

				if (perfect_collision.Intersect(����e���r_collision)){
					����e���r�A�Ő� -= 1;
					����e���r_x += 60;
					perfect_se->Play();
					explosion->SetTrackPosition(0, 0);
					explosion->SetTrackEnable(0, true);
				}
			}

			if (����e���r�A�Ő� <= 0) {
				����e���r_state = 1;
			}

			if (����e���r_x < 100) {

			}
		}
		else if (����e���r_state == 1) {
			explosion->SetTrackPosition(0, 0);
			explosion->SetTrackEnable(0, true);
		}
	}
}
void GameMain::����Draw()
{/*
	GraphicsDevice.Clear(Color_CornflowerBlue);

	GraphicsDevice.BeginScene();


	SpriteBatch.Begin();*/
	SpriteBatch.DrawString(�t�H���g, Vector2(0, 0), Color(255, 255, 255), _T("%ld"), ���[�r�[->GetPosition() / 100000);
	SpriteBatch.DrawString(�t�H���g, Vector2(500, 0), Color(255, 255, 255), _T("%d"), ��b);

	if (�J�n_state == 5) {
		SpriteBatch.DrawString(�t�H���g, Vector2(1000, 0), Color(255, 255, 255), _T("�N���A"));
	}
	SpriteBatch.Draw(*�w�i, Vector3(0.0f, 0.0f, 10.0f));
	//	SpriteBatch.Draw(*�v���C���[, Vector3(�v���C���[_x, �v���C���[_y, 0.0f));
	//SpriteBatch.Draw(*�����蔻��, Vector3(�����蔻��_x, �����蔻��_y, 0.0f));

	if (�f�o�b�N == 1) {
		SpriteBatch.DrawString(�t�H���g, Vector2(1000, 50), Color(255, 255, 255), _T("�������Ă�"));
	}

	if (�t�H���g_state == 1 && ����e���r_state == 0) {
		
	}

	if (�J�n_state == 1 || �J�n_state == 2) {

		for (int i = 0; i < ���̐�; i++)
		{

			if (��_state[i] == 1) {
				SpriteBatch.Draw(*�e���r, Vector3(�e���r_x[i], �e���r_y[i], 0.0f),�e���r_aplha[i]);
			}
			else if (��_state[i] == 2) {
				SpriteBatch.Draw(*�J����, Vector3(�J����_x[i], �J����_y[i], 0.0f), �J����_aplha[i]);
			}
			else if (��_state[i] == 3) {
				SpriteBatch.Draw(*�d�q�����W, Vector3(�d�q�����W_x[i], �d�q�����W_y[i], 0.0f));
			}
			else if (��_state[i] == 4) {
				SpriteBatch.Draw(*�K�X��, Vector3(�K�X��_x[i], �K�X��_y[i], 0.0f));
			}
		}
	}
	else if (�J�n_state == 3 && ����e���r_state == 0) {

		SpriteBatch.DrawString(�t�H���g, Vector2(300,300), Color(255, 255, 255), _T("8K�e���r�̗�:%d"),����e���r�A�Ő�);
		SpriteBatch.DrawString(�t�H���g, Vector2(700, 200), Color(0, 255, 255), _T("�A�ł���8K�e���r����!!"));
		SpriteBatch.Draw(*����e���r, Vector3(����e���r_x, ����e���r_y, 10.0f));
	}
}
void GameMain::�R��_Initialize()
{
	Light light;
	light.Type = Light_Directional;
	light.Direction = Vector3(0, -1, 1);
	light.Diffuse = Color(1.0f, 1.0f, 1.0f);
	light.Ambient = Color(1.0f, 1.0f, 1.0f);
	light.Specular = Color(1.0f, 1.0f, 1.0f);
	GraphicsDevice.SetLight(light);

	explosion = GraphicsDevice.CreateAnimationModelFromFile(_T("bakuha.x"), Compute_NormalTangent);
	explosion->SetScale(30.0f, -30.0f, 1.0f);//�傫��
	explosion->SetPosition(400, 500, -10000);

	Material material;
	material.Diffuse = Color(1.0f, 1.0f, 1.0f);
	material.Ambient = Color(0.5f, 0.5f, 0.5f);
	material.Specular = Color(1.0f, 1.0f, 1.0f);
	material.Power = 10.0f;
	explosion->SetMaterial(material);

	explosion->SetTrackEnable(0, false);
	explosion->SetTrackLoopMode(0, AnimationLoopMode_Once);

	auto frame = explosion->GetTrackPosition(0);

	camera->SetView(Vector3(0, 0, -10), Vector3(0, 0, 0));
	camera->SetOrthographicOffCenter(0, 1280, 720, 0, -10000, 10000);
	//explosion->SetPosition(0, 0, 0);
	//camera->SetPerspectiveFieldOfView(45.0f, 16.0f / 9.0f, 0.1f, 10000.0f);
	GraphicsDevice.SetCamera(camera);
}
void GameMain::�R��_Update()
{
	explosion->AdvanceTime(GameTimer.GetElapsedSecond());
	if (explosion->GetTrackPosition(0) >= 0.5)
		{
			explosion->SetTrackEnable(0, false);
		}
}
void GameMain::�R��_Draw()
{
		explosion->Draw();
}