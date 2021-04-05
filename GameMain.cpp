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

	髙橋Initialize();
	iwai_Initialize();
	３ｄ_Initialize();

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
	髙橋Main();
	iwai_Update();
	３ｄ_Update();
	//当たり判定同士の距離を測って判定
	if (開始_state == 5)
	{
		return GAME_SCENE(new clearScene);
	}
	//検証用
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

	３ｄ_Draw();

	SpriteBatch.Begin();

	髙橋Draw();
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
	//canvas.DrawRect(当たり判定_collision, paint);
	//paint.SetPaintColor(Color_Blue);
	//canvas.DrawRect(巨大テレビ_collision, paint);
	for (int i = 0; i < 物の数; i++) {

		//paint.SetPaintColor(Color_Blue);
		//canvas.DrawRect(ガス缶_collision[i], paint);
		if (物_state[i] == 1) {
		//	paint.SetPaintColor(Color_Red);
		//	canvas.DrawRect(テレビ_collision[i], paint);
		}
		else if (物_state[i] == 2) {
		//	paint.SetPaintColor(Color_Red);
		//	canvas.DrawRect(カメラ_collision[i], paint);
		}
		else if (物_state[i] == 3) {
		//	paint.SetPaintColor(Color_Red);
		//	canvas.DrawRect(電子レンジ_collision[i], paint);
		}
	}
	GraphicsDevice.UnlockCanvas();
}
void GameMain::iwai_Initialize() {
	player = GraphicsDevice.CreateSpriteFromFile(_T("プレイヤーキャラ_20.png"));
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
	miss_se = SoundDevice.CreateSoundFromFile(_T("空振り.wav"));
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
	for (int i = 0; i < 物の数; i++)
	{
		hitcount[i] = false;
		big[i] = 1.1;
		circle_alpha[i] = 0;
		テレビ_aplha[i] = 1;
		カメラ_aplha[i] = 1;
		電子レンジ_aplha[i] = 1;
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
	for (int i = 0; i < 物の数; i++)
	{
		SpriteBatch.Draw(*circle, Vector3(200, 300, -10), circle_alpha[i], Vector3(0, 0, 1), Vector3(200, 200, 0), Vector2(big[i], big[i]));
	}
	SpriteBatch.Draw(*player, Vector3(player_x, player_y, 0), RectWH(clip_x, 0, 350, 300));
	if (hit_test == 1)SpriteBatch.Draw(*perfect, Vector3(300, 400, 0));
	if (hit_test == 2)SpriteBatch.Draw(*good, Vector3(280, 400, 0));
	if (hit_test == 3)SpriteBatch.Draw(*miss, Vector3(280, 400, 0));
	SpriteBatch.DrawString(DefaultFont, Vector2(350, 0), Color(0, 0, 0), _T("距離:%f"), range);
	SpriteBatch.DrawString(DefaultFont, Vector2(350, 20), Color(0, 0, 0), _T("タイム:%d"), 一秒);
	SpriteBatch.DrawString(DefaultFont, Vector2(350, 40), Color(0, 0, 0), _T("スコア:%d"), score);
	SpriteBatch.DrawString(DefaultFont, Vector2(350, 60), Color(0, 0, 0), _T("破壊:%f"), explosion->GetTrackPosition(0));
	if(combo >= 2)SpriteBatch.DrawString(txt, Vector2(0, 40), Color(255, 162,235), _T("%dコンボ"), combo);
	if(count >1430)SpriteBatch.Draw(*ready, Vector3(400, 160, 0));
	if(count <=1430 && count >= 1320)SpriteBatch.Draw(*go, Vector3(430,160, 0),alpha_go, Vector3(0, 0,0), Vector3(122, 112, 0), Vector2(big_go, big_go));
}
void GameMain::iwai_Update() {

	count--;

	if (titleScene::hard == 2)
	{
		for (int i = 0; i < 物の数; i++)
		{
			circle_alpha[i] = 0;
		}
	}
	good_collision = Rect(good_x, good_y, good_x + 200.0f, good_y + 200.0f);
	perfect_collision = Rect(perfect_x + 70, perfect_y, perfect_x + 170.0f, perfect_y + 200.0f);
	miss_collision = Rect(miss_x , miss_y + 0, miss_x + 300.0f, Tv_y + 200.0f);
		if (key_buf.IsPressed(Keys_Space) && swing_flg == false)
		{
			for (int i = 0; i < 物の数; i++)
			{
				swing_flg = true;
				if (perfect_collision.Intersect(テレビ_collision[i]) && hitcount[i] == false|| perfect_collision.Intersect(カメラ_collision[i]) && hitcount[i] == false|| perfect_collision.Intersect(電子レンジ_collision[i]) && hitcount[i] == false)
				{
					combo++;
					hit_test = 1;
					score += 250 + combo*50 ;
					hitcount[i] = true;
					perfect_se->Play();
					explosion->SetTrackPosition(0, 0);
					explosion->SetTrackEnable(0, true);
					テレビ_aplha[i] = 0;
					カメラ_aplha[i] = 0;
					電子レンジ_aplha[i] = 0;
					perfect_++;
				}
				else if (good_collision.Intersect(テレビ_collision[i]) && hitcount[i] == false || good_collision.Intersect(カメラ_collision[i]) && hitcount[i] == false || good_collision.Intersect(電子レンジ_collision[i]) && hitcount[i] == false)
				{
					combo++;
					hit_test = 2;
					score += 500 + combo * 50;
					hitcount[i] = true;
					good_se->Play();
					explosion->SetTrackEnable(0, true);
					テレビ_aplha[i] = 0;
					カメラ_aplha[i] = 0;
					電子レンジ_aplha[i] = 0;
					good_++;
				}
				else if (miss_collision.Intersect(テレビ_collision[i]) && hitcount[i] == false || miss_collision.Intersect(カメラ_collision[i]) && hitcount[i] == false || miss_collision.Intersect(電子レンジ_collision[i]) && hitcount[i] == false)
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
						テレビ_aplha[i] = 0;
						カメラ_aplha[i] = 0;
						電子レンジ_aplha[i] = 0;
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
	for (int i = 0; i < 物の数; i++)
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
void GameMain::髙橋Initialize() {

	背景 = GraphicsDevice.CreateSpriteFromFile(_T("背景.png"));
	iwai_Initialize();

	背景 = GraphicsDevice.CreateSpriteFromFile(_T("背景.png"));
	プレイヤー = GraphicsDevice.CreateSpriteFromFile(_T("プレイヤー.png"));
	テレビ = GraphicsDevice.CreateSpriteFromFile(_T("テレビ.png"));
	カメラ = GraphicsDevice.CreateSpriteFromFile(_T("カメラ.png"));
	電子レンジ = GraphicsDevice.CreateSpriteFromFile(_T("電子レンジ.png"));
	当たり判定 = GraphicsDevice.CreateSpriteFromFile(_T("当たり判定.png"));
	フォント = GraphicsDevice.CreateSpriteFont(_T("MSゴシック"), 50);
	巨大テレビ = GraphicsDevice.CreateSpriteFromFile(_T("巨大テレビ.png"));
	ガス缶 = GraphicsDevice.CreateSpriteFromFile(_T("ガス缶.png"));

	MediaManager.Attach(GraphicsDevice);

	ムービー = MediaManager.CreateMediaFromFile(_T("ロボット工場.mp3"));

	カメラ速度 = 15 ;
	電子レンジ速度 = 6 / titleScene::hard;
	テレビ速度 = 10 * titleScene::hard;
	巨大テレビ速度 = 5 * titleScene::hard;
	秒 = 0;
	一秒 = 0;
	開始_state = 0;
	ムービー時間 = 0;
	デバック = 0;
	巨大テレビ連打数 = 15 * titleScene::hard;
	巨大テレビ_state = 0;
	フォント_state = 0;

	for (int i = 0; i < 物の数; i++) {
		ゴール[i] = 100 + (150 * i);
		テレビ_x[i] = 0;
		テレビ_y[i] = 400;
		カメラ_x[i] = 0;
		カメラ_y[i] = 400;
		電子レンジ_x[i] = 0;
		電子レンジ_y[i] = 400;
		ガス缶_x[i] = 0;
		ガス缶_y[i] = 400;
		//テレビ動き_state[i] = 0;
		スピード_y[i] = 7;
		シータ[i] = 0;
		t[i] = 0;
	}

	物_state[0] = 1;

	for (int i = 1; i < 物の数; i++) {
		物_state[i] = MathHelper_Random(1, 3);
	}

	プレイヤー_x = 100;
	プレイヤー_y = 400;
	当たり判定_x = 200;
	当たり判定_y = 500;
	巨大テレビ_x = 1000;
	巨大テレビ_y = 200;
	//テレビ動き = 5;
	ポイント[0] = Vector3(1280, 400, 0);
	ポイント[1] = Vector3(800, 300, 0);
	ポイント[2] = Vector3(700, 300, 0);
	ポイント[3] = Vector3(500, 400, 0);


	/*std::ifstream game_file("ゲームデータ.txt");
	std::string dummy_line;

	game_file >> タイミング[0];

	game_file >> タイミング[1];

	game_file >> タイミング[2];

	game_file >> タイミング[3];

	game_file >> タイミング[4];*/
}

void GameMain::髙橋Main() {

	keyboard = Keyboard->GetState();
	key_buf = Keyboard->GetBuffer();
	// TODO: Add your update logic here

	ムービー時間 = ムービー->GetPosition() / 100000;

	秒 += 1;

	if (秒 == 60) {
		一秒 += 1;
		秒 = 0;
	}

	if (一秒 == 3) {
		開始_state = 1;
	}
	else if (一秒 == 45) {
		開始_state = 2;
		フォント_state = 1;
	}
	else if (一秒 == 53) {
		ムービー->Stop();
	}
	else if (一秒 == 55) {
		開始_state = 4;
	}
	else if (一秒 == 58) {
		開始_state = 5;
	}

	if (開始_state == 1 || 開始_state == 2) {

		ムービー->Play();

		for (int i = 0; i < 物の数; i++) {

			当たり判定_collision = Rect(当たり判定_x, 当たり判定_y, 当たり判定_x + 150, 当たり判定_y + 90);

			if (物_state[i] == 1) {
				テレビ_x[i] = プレイヤー_x + (ゴール[i] - ムービー時間) * テレビ速度;
				テレビ_collision[i] = Rect(テレビ_x[i], テレビ_y[i], テレビ_x[i] + 100, テレビ_y[i] + 250);
				if (テレビ_x[i] < 1280)
				{
					big[i] -= 0.0138;
					circle_alpha[i] = 0.5;
				}
			}
			else if (物_state[i] == 2) {
				カメラ_x[i] = プレイヤー_x + (ゴール[i] - ムービー時間) * カメラ速度;
				カメラ_collision[i] = Rect(カメラ_x[i], カメラ_y[i], カメラ_x[i] + 100, カメラ_y[i] + 70);

				if (カメラ_x[i] < 1280) {
					Vector3 bezier = Vector3_Bezier(ポイント[0], ポイント[1], ポイント[2], ポイント[3], t[i]);
					カメラ_x[i] = bezier.x;
					カメラ_y[i] = bezier.y;
					t[i] = t[i] + 0.02f * titleScene::hard;
					カメラ_collision[i] = Rect(bezier.x, bezier.y, bezier.x + 60, bezier.y + 64);
					big[i] -= 0.013;
					circle_alpha[i] = 0.5;
				}
			}
			else if (物_state[i] == 3) {
				電子レンジ_x[i] = プレイヤー_x + (ゴール[i] - ムービー時間) * 電子レンジ速度;
				電子レンジ_collision[i] = Rect(電子レンジ_x[i] - 3, 電子レンジ_y[i], 電子レンジ_x[i] + 100, 電子レンジ_y[i] + 150);

				if (電子レンジ_x[i] < 1280) {
						big[i] -= 0.0085;
						circle_alpha[i] = 0.5;
					電子レンジ_x[i] = 電子レンジ_x[i] - 2;
					////                                             動かしたいドット数↓　　↓最初の描画位置　 
					電子レンジ_y[i] = MathHelper_Sin(シータ[i]) * 90 * titleScene::hard + 400;
					シータ[i] = シータ[i] + 1;
				}
			}
			else if (物_state[i] == 4) {
				ガス缶_x[i] = プレイヤー_x + (ゴール[i] - ムービー時間) * 電子レンジ速度;
				ガス缶_collision[i] = Rect(ガス缶_x[i], ガス缶_y[i], ガス缶_x[i] + 75, ガス缶_y[i] + 150);
				if (ガス缶_x[i] < 1280)
				{
					big[i] -= 0.0138;
					circle_alpha[i] = 0.5;
				}
			}

			if (開始_state == 1) {

				if (テレビ_x[i] < -400) {
					物_state[i] = 0;
					//テレビ動き_state[i] = 0;
					スピード_y[i] = 0;
				}

				if (カメラ_x[i] < -400) {
					物_state[i] = 0;
					//テレビ動き_state[i] = 0;
					スピード_y[i] = 0;
				}

				if (カメラ_y[i] > 1000) {
					物_state[i] = 0;
					//テレビ動き_state[i] = 0;
					スピード_y[i] = 0;
				}

				if (電子レンジ_x[i] < -400) {
					物_state[i] = 0;
					//テレビ動き_state[i] = 0;
					スピード_y[i] = 0;
				}

				if (ガス缶_x[i] < -400) {
					物_state[i] = 0;
					//テレビ動き_state[i] = 0;
					スピード_y[i] = 0;
				}
			}
			else if (開始_state == 2) {

				if (テレビ_x[i] < -500) {
					物_state[i] = 0;
					//テレビ動き_state[i] = 0;
					開始_state = 3;
				}

				if (カメラ_x[i] < -500) {
					物_state[i] = 0;
					//テレビ動き_state[i] = 0;
					開始_state = 3;
				}

				if (カメラ_y[i] < 900) {
					物_state[i] = 0;
					//テレビ動き_state[i] = 0;
					スピード_y[i] = 0;
					開始_state = 3;
				}

				if (電子レンジ_x[i] < -500) {
					物_state[i] = 0;
					//テレビ動き_state[i] = 0;
					開始_state = 3;
				}

				if (ガス缶_x[i] < -500) {
					物_state[i] = 0;
					//テレビ動き_state[i] = 0;
					開始_state = 3;
				}
			}
		}
	}
	else if (開始_state == 3) {
		巨大テレビ_collision = Rect(巨大テレビ_x, 巨大テレビ_y, 巨大テレビ_x + 150, 巨大テレビ_y + 500);
		巨大テレビ_x = 巨大テレビ_x - 巨大テレビ速度;

		if (巨大テレビ_state == 0) {

			if (key_buf.IsPressed(Keys_Space)) {

				if (perfect_collision.Intersect(巨大テレビ_collision)){
					巨大テレビ連打数 -= 1;
					巨大テレビ_x += 60;
					perfect_se->Play();
					explosion->SetTrackPosition(0, 0);
					explosion->SetTrackEnable(0, true);
				}
			}

			if (巨大テレビ連打数 <= 0) {
				巨大テレビ_state = 1;
			}

			if (巨大テレビ_x < 100) {

			}
		}
		else if (巨大テレビ_state == 1) {
			explosion->SetTrackPosition(0, 0);
			explosion->SetTrackEnable(0, true);
		}
	}
}
void GameMain::髙橋Draw()
{/*
	GraphicsDevice.Clear(Color_CornflowerBlue);

	GraphicsDevice.BeginScene();


	SpriteBatch.Begin();*/
	SpriteBatch.DrawString(フォント, Vector2(0, 0), Color(255, 255, 255), _T("%ld"), ムービー->GetPosition() / 100000);
	SpriteBatch.DrawString(フォント, Vector2(500, 0), Color(255, 255, 255), _T("%d"), 一秒);

	if (開始_state == 5) {
		SpriteBatch.DrawString(フォント, Vector2(1000, 0), Color(255, 255, 255), _T("クリア"));
	}
	SpriteBatch.Draw(*背景, Vector3(0.0f, 0.0f, 10.0f));
	//	SpriteBatch.Draw(*プレイヤー, Vector3(プレイヤー_x, プレイヤー_y, 0.0f));
	//SpriteBatch.Draw(*当たり判定, Vector3(当たり判定_x, 当たり判定_y, 0.0f));

	if (デバック == 1) {
		SpriteBatch.DrawString(フォント, Vector2(1000, 50), Color(255, 255, 255), _T("当たってる"));
	}

	if (フォント_state == 1 && 巨大テレビ_state == 0) {
		
	}

	if (開始_state == 1 || 開始_state == 2) {

		for (int i = 0; i < 物の数; i++)
		{

			if (物_state[i] == 1) {
				SpriteBatch.Draw(*テレビ, Vector3(テレビ_x[i], テレビ_y[i], 0.0f),テレビ_aplha[i]);
			}
			else if (物_state[i] == 2) {
				SpriteBatch.Draw(*カメラ, Vector3(カメラ_x[i], カメラ_y[i], 0.0f), カメラ_aplha[i]);
			}
			else if (物_state[i] == 3) {
				SpriteBatch.Draw(*電子レンジ, Vector3(電子レンジ_x[i], 電子レンジ_y[i], 0.0f));
			}
			else if (物_state[i] == 4) {
				SpriteBatch.Draw(*ガス缶, Vector3(ガス缶_x[i], ガス缶_y[i], 0.0f));
			}
		}
	}
	else if (開始_state == 3 && 巨大テレビ_state == 0) {

		SpriteBatch.DrawString(フォント, Vector2(300,300), Color(255, 255, 255), _T("8Kテレビ体力:%d"),巨大テレビ連打数);
		SpriteBatch.DrawString(フォント, Vector2(700, 200), Color(0, 255, 255), _T("連打して8Kテレビを壊せ!!"));
		SpriteBatch.Draw(*巨大テレビ, Vector3(巨大テレビ_x, 巨大テレビ_y, 10.0f));
	}
}
void GameMain::３ｄ_Initialize()
{
	Light light;
	light.Type = Light_Directional;
	light.Direction = Vector3(0, -1, 1);
	light.Diffuse = Color(1.0f, 1.0f, 1.0f);
	light.Ambient = Color(1.0f, 1.0f, 1.0f);
	light.Specular = Color(1.0f, 1.0f, 1.0f);
	GraphicsDevice.SetLight(light);

	explosion = GraphicsDevice.CreateAnimationModelFromFile(_T("bakuha.x"), Compute_NormalTangent);
	explosion->SetScale(30.0f, -30.0f, 1.0f);//大きさ
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
void GameMain::３ｄ_Update()
{
	explosion->AdvanceTime(GameTimer.GetElapsedSecond());
	if (explosion->GetTrackPosition(0) >= 0.5)
		{
			explosion->SetTrackEnable(0, false);
		}
}
void GameMain::３ｄ_Draw()
{
		explosion->Draw();
}