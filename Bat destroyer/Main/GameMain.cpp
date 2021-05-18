// #include "Extension\DirectX11\DXGraphics11.hpp"
#include "StdAfx.h"
#include "GameMain.h"

//clear.cppで取得できるように
int GameMain::score    = 0;
int GameMain::perfect_ = 0;
int GameMain::good_    = 0;
int GameMain::miss_    = 0;

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

	takahasi_Initialize();
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
	takahasi_Main();
	iwai_Update();
	３ｄ_Update();

	//当たり判定同士の距離を測って判定
	if (start_state == 5)
	{
		return GAME_SCENE(new clearScene);
	}

	//検証用
	//if (key_buf.IsPressed(Keys_A))
	//{
	//	return GAME_SCENE(new clearScene);
	//}

	return 0;
}
void GameMain::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_CornflowerBlue);

	GraphicsDevice.BeginScene();

	３ｄ_Draw();

	SpriteBatch.Begin();

	takahasi_Draw();
	iwai_Draw();

	SpriteBatch.End();

	GraphicsDevice.EndScene();

	//当たり判定のデバック用
	Canvas canvas = GraphicsDevice.LockCanvas();
	Paint  paint;

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
	for (int i = 0; i < object_max; i++) {

		//paint.SetPaintColor(Color_Blue);
		//canvas.DrawRect(ガス缶_collision[i], paint);
		if (object_state[i] == 1) {
		//	paint.SetPaintColor(Color_Red);
		//	canvas.DrawRect(テレビ_collision[i], paint);
		}
		else if (object_state[i] == 2) {
		//	paint.SetPaintColor(Color_Red);
		//	canvas.DrawRect(カメラ_collision[i], paint);
		}
		else if (object_state[i] == 3) {
		//	paint.SetPaintColor(Color_Red);
		//	canvas.DrawRect(電子レンジ_collision[i], paint);
		}
	}
	GraphicsDevice.UnlockCanvas();
	//ここまで
}
void GameMain::iwai_Initialize() {

	//チームの方が作成したところなので省略
	
}
void GameMain::iwai_Draw() {
	
	//チームの方が作成したところなので省略
	
}
void GameMain::iwai_Update() {

	//チームの方が作成したところなので省略
	
}
void GameMain::takahasi_Initialize() {

	iwai_Initialize();

	bg        = GraphicsDevice.CreateSpriteFromFile(_T("背景.png"));
	ta_player = GraphicsDevice.CreateSpriteFromFile(_T("プレイヤー.png"));
	tv        = GraphicsDevice.CreateSpriteFromFile(_T("テレビ.png"));
	ta_camera = GraphicsDevice.CreateSpriteFromFile(_T("カメラ.png"));
	microwave = GraphicsDevice.CreateSpriteFromFile(_T("電子レンジ.png"));
	hit       = GraphicsDevice.CreateSpriteFromFile(_T("当たり判定.png"));
	font      = GraphicsDevice.CreateSpriteFont    (_T("MSゴシック"), 50);
	car       = GraphicsDevice.CreateSpriteFromFile(_T("巨大テレビ.png"));
	gas       = GraphicsDevice.CreateSpriteFromFile(_T("ガス缶.png"));
	movie     = MediaManager.  CreateMediaFromFile (_T("ロボット工場.mp3")); //BGM

	MediaManager.Attach(GraphicsDevice);

	//変数の初期化
	camera_speed    = 15 ;
	microwave_speed = 6  / titleScene::hard;
	tv_speed        = 10 * titleScene::hard;
	car_speed       = 5  * titleScene::hard;
	ta_time         = 0;
	second_1        = 0;
	start_state     = 0;
	movie_time      = 0;
	debug           = 0;
	car_hit         = 15 * titleScene::hard;
	car_state       = 0;
	font_state      = 0;

	ta_player_x = 100;
	ta_player_y = 400;
	hit_x       = 200;
	hit_y       = 500;
	car_x       = 1000;
	car_y       = 200;
	point[0]    = Vector3(1280, 400, 0);
	point[1]    = Vector3(800, 300, 0);
	point[2]    = Vector3(700, 300, 0);
	point[3]    = Vector3(500, 400, 0);

	//変数(配列)の初期化
	for (int i = 0; i < object_max; i++) {
		goal[i]        = 100 + (150 * i);
		tv_x[i]        = 0;
		tv_y[i]        = 400;
		camera_x[i]    = 0;
		camera_y[i]    = 400;
		microwave_x[i] = 0;
		microwave_y[i] = 400;
		gas_x[i]       = 0;
		gas_y[i]       = 400;
		speed_y[i]     = 7;
		theta[i]       = 0;
		t[i]           = 0;
	}

	//最初に出てくる物を設定
	object_state[0] = 1;

	//出現する物をランダムで設定
	for (int i = 1; i < object_max; i++) {
		object_state[i] = MathHelper_Random(1, 3);
	}
}

void GameMain::takahasi_Main() {

	keyboard   = Keyboard->GetState();
	key_buf    = Keyboard->GetBuffer();
	movie_time = movie->GetPosition() / 100000;

	//タイムの処理、start_state変更
	ta_time += 1;
	if (ta_time == 60) {
		second_1 += 1;
		ta_time   = 0;
	}

	if (second_1 == 3) {
		start_state = 1;
	}
	else if (second_1 == 45) {
		start_state = 2;
		font_state  = 1;
	}
	else if (second_1 == 53) {
		movie->Stop();
	}
	else if (second_1 == 55) {
		start_state = 4;
	}
	else if (second_1 == 58) {
		start_state = 5;
	}

	if (start_state == 1 || start_state == 2) {

		movie->Play();

		//当たり判定
		for (int i = 0; i < object_max; i++) {

			hit_collision = Rect(hit_x, hit_y, hit_x + 150, hit_y + 90);

			if (object_state[i] == 1) {
				//テレビ
				tv_x[i]         = ta_player_x + (goal[i] - movie_time) * tv_speed;
				tv_collision[i] = Rect(tv_x[i], tv_y[i], tv_x[i] + 100, tv_y[i] + 250);

				if (tv_x[i] < 1280)
				{
					big[i]         -= 0.0138;
					circle_alpha[i] = 0.5;
				}
			}
			else if (object_state[i] == 2) {
				//カメラ
				camera_x[i]         = ta_player_x + (goal[i] - movie_time) * camera_speed;
				camera_collision[i] = Rect(camera_x[i], camera_y[i], camera_x[i] + 100, camera_y[i] + 70);

				if (camera_x[i] < 1280) {
					//ベジェ曲線
					Vector3 bezier      = Vector3_Bezier(point[0], point[1], point[2], point[3], t[i]);
					camera_x[i]         = bezier.x;
					camera_y[i]         = bezier.y;
					t[i]                = t[i] + 0.02f * titleScene::hard;
					camera_collision[i] = Rect(bezier.x, bezier.y, bezier.x + 60, bezier.y + 64);
					big[i]             -= 0.013;
					circle_alpha[i]     = 0.5;
				}
			}
			else if (object_state[i] == 3) {
				//電子レンジ
				microwave_x[i]         = ta_player_x + (goal[i] - movie_time) * microwave_speed;
				microwave_collision[i] = Rect(microwave_x[i] - 3, microwave_y[i], microwave_x[i] + 100, microwave_y[i] + 150);

				if (microwave_x[i] < 1280) {
					big[i]         -= 0.0085;
					circle_alpha[i] = 0.5;
					microwave_x[i]  = microwave_x[i] - 2; //     動かしたいドット数↓　　↓最初の描画位置　 
					microwave_y[i]  = MathHelper_Sin(theta[i]) * 90 * titleScene::hard + 400;
					theta[i]        = theta[i] + 1;
				}
			}
			else if (object_state[i] == 4) {
				//ガス缶
				//gas_x[i]         = ta_player_x + (goal[i] - movie_time) * microwave_speed;
				//gas_collision[i] = Rect(gas_x[i], gas_y[i], gas_x[i] + 75, gas_y[i] + 150);
				//if (gas_x[i] < 1280)
				//{
				//	big[i]         -= 0.0138;
				//	circle_alpha[i] = 0.5;
				//}
			}


			if (start_state == 1) {

				if (tv_x[i] < -400) {
					object_state[i] = 0;
					speed_y[i]      = 0;
				}

				if (camera_x[i] < -400) {
					object_state[i] = 0;
					speed_y[i]      = 0;
				}

				if (camera_y[i] > 1000) {
					object_state[i] = 0;
					speed_y[i]      = 0;
				}

				if (microwave_x[i] < -400) {
					object_state[i] = 0;
					speed_y[i]      = 0;
				}

				if (gas_x[i] < -400) {
					object_state[i] = 0;
					speed_y[i]      = 0;
				}
			}
			else if (start_state == 2) {

				if (tv_x[i] < -500) {
					object_state[i] = 0;
					start_state     = 3;
				}

				if (camera_x[i] < -500) {
					object_state[i] = 0;
					start_state     = 3;
				}

				if (camera_y[i] < 900) {
					object_state[i] = 0;
					speed_y[i]      = 0;
					start_state     = 3;
				}

				if (microwave_x[i] < -500) {
					object_state[i] = 0;
					start_state     = 3;
				}

				if (gas_x[i] < -500) {
					object_state[i] = 0;
					start_state     = 3;
				}
			}
		}
	}
	else if (start_state == 3) {
		car_collision = Rect(car_x, car_y, car_x + 150, car_y + 500);
		car_x         = car_x - car_speed;

		if (car_state == 0) {

			if (key_buf.IsPressed(Keys_Space)) {

				if (perfect_collision.Intersect(car_collision)){
					car_hit  -= 1;
					car_x    += 60;
					perfect_se->Play();
					explosion ->SetTrackPosition(0, 0);
					explosion ->SetTrackEnable(0, true);
				}
			}

			if (car_hit <= 0) {
				car_state = 1;
			}
		}
		else if (car_state == 1) {
			explosion->SetTrackPosition(0, 0);
			explosion->SetTrackEnable(0, true);
		}
	}
}
void GameMain::takahasi_Draw()
{
	//デバック用
	//if (debug == 1) {
	//	SpriteBatch.DrawString(font, Vector2(1000, 50), Color(255, 255, 255), _T("当たってる"));
	//}

	//曲がずれないようにmovie->Getpositionで曲の位置を取得
	SpriteBatch.DrawString(font, Vector2(0, 0),   Color(255, 255, 255), _T("%ld"), movie->GetPosition() / 100000);
	SpriteBatch.DrawString(font, Vector2(500, 0), Color(255, 255, 255), _T("%d"),  second_1);
	SpriteBatch.Draw      (*bg,  Vector3(0.0f, 0.0f, 10.0f));

	if (start_state == 5) {
		SpriteBatch.DrawString(font, Vector2(1000, 0), Color(255, 255, 255), _T("クリア"));
	}

	if (start_state == 1 || start_state == 2) {

		for (int i = 0; i < object_max; i++)
		{
			if (object_state[i] == 1) {
				//テレビ
				SpriteBatch.Draw(*tv, Vector3(tv_x[i], tv_y[i], 0.0f),tv_aplha[i]);
			}
			else if (object_state[i] == 2) {
				//カメラ
				SpriteBatch.Draw(*ta_camera, Vector3(camera_x[i], camera_y[i], 0.0f), camera_aplha[i]);
			}
			else if (object_state[i] == 3) {
				//電子レンジ
				SpriteBatch.Draw(*microwave, Vector3(microwave_x[i], microwave_y[i], 0.0f));
			}
			else if (object_state[i] == 4) {
				//ガス缶
				//SpriteBatch.Draw(*gas, Vector3(gas_x[i], gas_y[i], 0.0f));
			}
		}
	}
	else if (start_state == 3 && car_state == 0) {

		//SpriteBatch.DrawString(font,    Vector2(300,300),  Color(255, 255, 255), _T("8Kテレビ体力:%d"),car_hit);
		//SpriteBatch.DrawString(font,    Vector2(700, 200), Color(0, 255, 255),   _T("連打して8Kテレビを壊せ!!"));
		SpriteBatch.Draw      (*car,    Vector3(car_x, car_y, 10.0f));
	}
}
void GameMain::３ｄ_Initialize()
{
	//ライト
	Light light;
	light.Type      = Light_Directional;
	light.Direction = Vector3(0, -1, 1);
	light.Diffuse   = Color  (1.0f, 1.0f, 1.0f);
	light.Ambient   = Color  (1.0f, 1.0f, 1.0f);
	light.Specular  = Color  (1.0f, 1.0f, 1.0f);
	GraphicsDevice.SetLight  (light);

	explosion = GraphicsDevice.CreateAnimationModelFromFile(_T("bakuha.x"), Compute_NormalTangent);
	explosion ->SetScale   (30.0f, -30.0f, 1.0f);//大きさ
	explosion ->SetPosition(400, 500, -10000);

	//マテリアル
	Material material;
	material.Diffuse  = Color(1.0f, 1.0f, 1.0f);
	material.Ambient  = Color(0.5f, 0.5f, 0.5f);
	material.Specular = Color(1.0f, 1.0f, 1.0f);
	material.Power    = 10.0f;

	explosion->SetMaterial     (material);
	explosion->SetTrackEnable  (0, false);
	explosion->SetTrackLoopMode(0, AnimationLoopMode_Once);

	auto frame = explosion->GetTrackPosition(0);

	//カメラ
	camera->SetView                 (Vector3(0, 0, -10), Vector3(0, 0, 0));
	camera->SetOrthographicOffCenter(0, 1280, 720, 0, -10000, 10000);
	GraphicsDevice.SetCamera        (camera);
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
