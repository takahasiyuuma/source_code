//
// MainScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"
#include <time.h>

extern void ExitGame() noexcept;

// Initialize a variable and audio resources.
void MainScene::Initialize()
{
	engine_se      = make_unique<SoundEffect>(DXTK->AudioEngine, L"SE走行中.wav");
	engine_se_loop = engine_se->CreateInstance();
	engine_se_loop ->Stop(true);

	abrupt_steering_up_se      = make_unique<SoundEffect>(DXTK->AudioEngine, L"SE急ハンドル.wav");
	abrupt_steering_up_se_loop = abrupt_steering_up_se->CreateInstance();

	abrupt_steering_down_se      = make_unique<SoundEffect>(DXTK->AudioEngine, L"SE急ハンドル.wav");
	abrupt_steering_down_se_loop = abrupt_steering_down_se->CreateInstance();

	bgm      = make_unique<SoundEffect>(DXTK->AudioEngine, L"BGMメイン.wav");
	bgm_loop = bgm->CreateInstance();
	bgm_loop ->Stop(true);

	player_x               = 500;
	player_y               = 500;
	main_bg_x              = 0;
	speed                  = 100;
	speed_x                = 0;
	speed_y                = 0;
	acceleration_up        = 0;
	acceleration_down      = 0;
	player_direction_state = 0;
	alpha                  = 0.0f;
	elapsedTime            = 0.0f;
	enemy_red_x            = 0.0f;
	enemy_red_y            = 0.0f;
	enemy_blue_x           = 0.0f;
	enemy_blue_y           = 0.0f;
	enemy_police_x         = 0.0f;
	enemy_police_y         = 0.0f;
	next_scene_flag        = false;
	start_flag             = false;
	escape_flag            = false;
	next_scene             = NextScene::Continue;

	for (int i = 0; i < POLICE_WALL; i++) {
		enemy_police_wall_x[i] = 0.0f;
		enemy_police_wall_y[i] = 0.0f;
	}

	//srand関数を使って現在の歴時刻で初期化
	srand((unsigned int)time(NULL));
}

// Allocate all memory the Direct3D and Direct2D resources.
void MainScene::LoadAssets()
{
	ResourceUpload.CreateDescriptorHeap(DXTK->PrimaryDevice, 11);//←表示する画像の数
	ResourceUpload.ResourceUploadBegin(DXTK->PrimaryDevice);
	sprite_batch = ResourceUpload.CreateSpriteBatch();

	D3D12_VIEWPORT viewport = {
		0.0f, 0.0f,
		static_cast<float>(DXTK->ScreenWidth), static_cast<float>(DXTK->ScreenHeight),
		D3D12_MIN_DEPTH, D3D12_MAX_DEPTH
	};
	sprite_batch->SetViewport(viewport);

	sprite_main_screen       = ResourceUpload.CreateTexture(L"ゲームプレイ画面.png", 0);
	sprite_player            = ResourceUpload.CreateTexture(L"自機.png", 1);
	sprite_player_up         = ResourceUpload.CreateTexture(L"自機斜め上.png", 2);
	sprite_player_down       = ResourceUpload.CreateTexture(L"自機斜め下.png", 3);
	sprite_time_frame        = ResourceUpload.CreateTexture(L"タイム枠.png", 4);
	sprite_money_frame       = ResourceUpload.CreateTexture(L"金額枠.png", 5);
	sprite_enemy_red         = ResourceUpload.CreateTexture(L"赤車.png", 6);
	sprite_enemy_blue        = ResourceUpload.CreateTexture(L"青車.png", 7);
	sprite_enemy_police      = ResourceUpload.CreateTexture(L"パトカー.png", 8);
	sprite_enemy_police_wall = ResourceUpload.CreateTexture(L"パトカー壁.png", 9);
	sprite_danger            = ResourceUpload.CreateTexture(L"危険.png", 10);

	ResourceUpload.ResourceUploadEnd(DXTK->PrimaryCommandQueue);
}

// Releasing resources required for termination.
void MainScene::Terminate()
{
	DXTK->AudioEngine->Reset();
	DXTK->WaitForGpu();
}

// Direct3D resource cleanup.
void MainScene::OnDeviceLost()
{

}

// Restart any looped sounds here
void MainScene::OnRestartSound()
{
	engine_se_loop->Play(true);
	bgm_loop      ->Play(true);
}

// Updates the scene.
NextScene MainScene::Update(const float deltaTime)
{
	// If you use 'deltaTime', remove it.
	UNREFERENCED_PARAMETER(deltaTime);

	// TODO: Add your game logic here.

		//フェードイン終了までスタートしないようにstart_flagで管理↓ flase=停止 true=開始
	if (!start_flag) {
		//タイトル画面からのロード後のフェードイン↓
		if (alpha <= 1.0f) {
			alpha += (0.35f * deltaTime);
		}
		else {
			//フェードイン終了したらstart_flagをtrueに↓
			start_flag = true;
		}
	}
	else {
		bgm_loop->Play(true);
		engine_se_loop->Play(true);

		if (!next_scene_flag) {

		}
		else
		{
			//フェードアウト↓
			elapsedTime += deltaTime;
			alpha -= (0.35f * deltaTime);
			if (elapsedTime >= 4.3f)
				return next_scene;
		}

		main_bg_update(deltaTime);
		player_update(deltaTime);
	}

	return NextScene::Continue;
}

// Draws the scene.
void MainScene::Render()
{
	// TODO: Add your rendering code here.
	DXTK->Clear(PrimaryAdapter, Colors::Black);

	ID3D12DescriptorHeap* heaps[] = { ResourceUpload.GetDescriptorHeap() };
	DXTK->PrimaryCommandList->SetDescriptorHeaps(_countof(heaps), heaps);
	sprite_batch->Begin(DXTK->PrimaryCommandList);

	main_bg_draw();
	player_draw();

	sprite_batch->End();

	DXTK->ExecutePrimaryCommandLists();

	DXTK->Direct2DBeginDraw();
	DXTK->Direct2D->SetTransform(D2D1::Matrix3x2F::Identity());

	ComPtr<ID2D1SolidColorBrush> text_brush;
	ComPtr<IDWriteTextFormat>    text_format;
	WCHAR* text_string;
	D2D1_RECT_F text_rect;

	//---

	DXTK->Direct2D->CreateSolidColorBrush(
		D2D1::ColorF(0.9f, 0.3f, 0.4f, alpha),
		&text_brush
	);
	//赤、青、緑、透明度
	DXTK->DirectWrite->CreateTextFormat(
		L"ＭＳ ゴシック", NULL, DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		50, // サイズ
		L"ja-JP", &text_format
	);
	WCHAR high_score_text[256];//intなら %d、floatなら %f
	swprintf_s(high_score_text, 256, L"%d", speed);
	D2D1_RECT_F high_score_text_rect = D2D1::RectF(1022, 0, 1280, 720);
	DXTK->Direct2D->DrawText(
		high_score_text, lstrlen(high_score_text),
		text_format.Get(), &high_score_text_rect, text_brush.Get()
	);

	//---

	DXTK->Direct2D->CreateSolidColorBrush(
		D2D1::ColorF(0.9f, 0.3f, 0.4f, alpha),
		&text_brush
	);
	//赤、青、緑、透明度
	DXTK->DirectWrite->CreateTextFormat(
		L"ＭＳ ゴシック", NULL, DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		50, // サイズ
		L"ja-JP", &text_format
	);
	WCHAR high_score_text[256];//intなら %d、floatなら %f
	swprintf_s(high_score_text, 256, L"%d",speed);
	D2D1_RECT_F high_score_text_rect = D2D1::RectF(1022, 0, 1280, 720);
	DXTK->Direct2D->DrawText(
		high_score_text, lstrlen(high_score_text),
		text_format.Get(), &high_score_text_rect, text_brush.Get()
	);

	//---

	DXTK->Direct2DEndDraw();
}

void MainScene::main_bg_update(const float deltaTime)
{
	main_bg_x = main_bg_x - 20 - (speed / 100) * deltaTime;
	if (main_bg_x <= -2720.0f) {
		main_bg_x = 0.0f;
	}
}

void MainScene::main_bg_draw()
{
	sprite_batch->Draw(
		sprite_main_screen,
		XMUINT2(4000, 720),
		SimpleMath::Vector2(main_bg_x, 0.0f),
		SimpleMath::Vector4(alpha, alpha, alpha, alpha)
	);

	sprite_batch->Draw(
		sprite_time_frame,
		XMUINT2(452, 84),
		SimpleMath::Vector2(500.0f, 0.0f),
		SimpleMath::Vector4(alpha, alpha, alpha, alpha)
	);

	sprite_batch->Draw(
		sprite_money_frame,
		XMUINT2(441, 74),
		SimpleMath::Vector2(0.0f, 5.0f),
		SimpleMath::Vector4(alpha, alpha, alpha, alpha)
	);
}

void MainScene::player_update(const float deltaTime)
{
	if (!DXTK->KeyState->S) {

		if (DXTK->KeyState->W) {
			speed_y = speed_y - (2.0 + (speed / 10)) * deltaTime;

			if (speed_y < -10) {
				speed_y = -10;
			}

			if (abrupt_steering_up_se_loop->GetState() != SoundState::PLAYING) {
				abrupt_steering_up_se_loop->Play(false);
			}

			player_direction_state = 1;
		}
	}

	if (!DXTK->KeyState->W) {

		if (DXTK->KeyState->S) {
			speed_y = speed_y + (2.0 + (speed / 10)) * deltaTime;

			if (speed_y > 10) {
				speed_y = 10;
			}

			if (abrupt_steering_down_se_loop->GetState() != SoundState::PLAYING) {
				abrupt_steering_down_se_loop->Play(false);
			}

			player_direction_state = 2;
		}
	}

	if (!DXTK->KeyState->W && !DXTK->KeyState->S) {

		if (speed_y > 0) {
			speed_y = speed_y - 2.5 * deltaTime;
		}

		if (speed_y < 0) {
			speed_y = speed_y + 2.5 * deltaTime;
		}

		player_direction_state = 0;
	}

	if (player_y >= 298) {

		acceleration_up = acceleration_up + deltaTime;

		if (acceleration_up >= 0.5f) {
			speed = speed + 1;
			acceleration_up = 0;
		}
	}
	else if (player_y <= 297) {

		acceleration_down = acceleration_down + deltaTime;

		if (acceleration_down >= 0.1f) {
			speed = speed - 1;
			acceleration_down = 0;
		}
	}

	if (speed < 80) {
		speed = 80;
	}

	player_x = player_x + speed_x;
	player_y = player_y + speed_y;

	if (player_x > 1000) {
		player_x = 1000;
	}

	if (player_x < 0) {
		player_x = 0;
	}

	if (player_y < 245) {
		player_y = 245;
		player_direction_state = 0;
		if (speed_y <= -6)
			speed_y = -5;
	}

	if (player_y > 650) {
		player_y = 650;
		player_direction_state = 0;
		if (speed_y >= 6)
			speed_y = 5;
	}
}

void MainScene::player_draw()
{
	if (player_direction_state == 0) {

		sprite_batch->Draw(
			sprite_player,
			XMUINT2(139, 88),
			SimpleMath::Vector2(player_x, player_y),
			SimpleMath::Vector4(alpha, alpha, alpha, alpha)
		);
	}
	else if (player_direction_state == 1) {

		sprite_batch->Draw(
			sprite_player_up,
			XMUINT2(139, 88),
			SimpleMath::Vector2(player_x, player_y),
			SimpleMath::Vector4(alpha, alpha, alpha, alpha)
		);
	}
	else if (player_direction_state == 2) {

		sprite_batch->Draw(
			sprite_player_down,
			XMUINT2(139, 88),
			SimpleMath::Vector2(player_x, player_y),
			SimpleMath::Vector4(alpha, alpha, alpha, alpha)
		);
	}
}

void MainScene::enemy_update(const float deltaTime)
{

}

void MainScene::enemy_draw()
{
	sprite_batch->Draw(
		sprite_enemy_red,
		XMUINT2(136, 97),
		SimpleMath::Vector2(enemy_red_x, enemy_red_y),
		SimpleMath::Vector4(alpha, alpha, alpha, alpha)
	);

	sprite_batch->Draw(
		sprite_enemy_blue,
		XMUINT2(136, 97),
		SimpleMath::Vector2(enemy_blue_x, enemy_blue_y),
		SimpleMath::Vector4(alpha, alpha, alpha, alpha)
	);

	sprite_batch->Draw(
		sprite_enemy_police,
		XMUINT2(139, 89),
		SimpleMath::Vector2(enemy_police_x, enemy_police_y),
		SimpleMath::Vector4(alpha, alpha, alpha, alpha)
	);
}

void MainScene::police_wall_update(const float deltaTime)
{
	if (!escape_flag) {

		police_wall_decimals += 1;

		if (police_wall_decimals == 60) {
			police_wall_decimals = 0;
			police_wall_seconds += 1;
		}
		else if (police_wall_seconds == 1) {
			police_wall_random = rand() % 4 + 1;//1～4の数値をランダムで取得
		}
		else if (police_wall_seconds == 3) {
			//パトカーの座標の初期化＆ステート変更
			police_wall_state = 1;
			for (int i = 0; i < POLICE_WALL; i++) {
				enemy_police_wall_x[i] = 1200;
				enemy_police_wall_y[i] = 335 + (100 * i);
			}
		}
		else if (police_wall_seconds == 5) {
			police_wall_state = 2;
		}
		else if (police_wall_seconds == 10) {
			police_wall_random = 0;
			police_wall_state = 3;
		}
		else if (police_wall_seconds == 13) {
			police_wall_random = rand() % 4 + 1;//1～4の数値をランダムで取得
		}
		else if (police_wall_seconds == 15) {
			//パトカーの座標の初期化＆ステート変更
			police_wall_state = 4;
			for (int i = 0; i < POLICE_WALL; i++) {
				enemy_police_wall_x[i] = 1200;
				enemy_police_wall_y[i] = 335 + (100 * i);
			}
		}
		else if (police_wall_seconds == 20) {
			police_wall_state = 5;
		}
		else if (police_wall_seconds == 25) {
			police_wall_random = 0;
			police_wall_state = 6;
		}
		else if (police_wall_seconds == 28) {
			police_wall_random = rand() % 4 + 1;//1～4の数値をランダムで取得
		}
		else if (police_wall_seconds == 30) {
			//パトカーの座標の初期化＆ステート変更
			police_wall_state = 7;
			for (int i = 0; i < POLICE_WALL; i++) {
				enemy_police_wall_x[i] = 1200;
				enemy_police_wall_y[i] = 335 + (100 * i);
			}
		}
		else if (police_wall_seconds == 35) {
			police_wall_state = 8;
		}
		else if (police_wall_seconds == 40) {
			police_wall_random = 0;
			police_wall_state = 9;
		}
		else if (police_wall_seconds == 43) {
			police_wall_random = rand() % 4 + 1;//1～4の数値をランダムで取得
		}
		else if (police_wall_seconds == 45) {
			//パトカーの座標の初期化＆ステート変更
			police_wall_state = 10;
			for (int i = 0; i < POLICE_WALL; i++) {
				enemy_police_wall_x[i] = 1200;
				enemy_police_wall_y[i] = 335 + (100 * i);
			}
		}
		else if (police_wall_seconds == 50) {
			police_wall_state = 11;
		}
		else if (police_wall_seconds == 55) {
			police_wall_random = 0;
			police_wall_state = 12;
		}
		else if (police_wall_seconds == 58) {
			police_wall_random = rand() % 4 + 1;//1～4の数値をランダムで取得
		}
		else if (police_wall_seconds == 60) {
			//パトカーの座標の初期化＆ステート変更
			police_wall_state = 13;
			for (int i = 0; i < POLICE_WALL; i++) {
				enemy_police_wall_x[i] = 1200;
				enemy_police_wall_y[i] = 335 + (100 * i);
			}
		}
		else if (police_wall_seconds == 65) {
			police_wall_state = 14;
		}
		else if (police_wall_seconds == 70) {
			police_wall_random = 0;
			police_wall_state = 15;
		}
		else if (police_wall_seconds == 73) {
			police_wall_random = rand() % 4 + 1;//1～4の数値をランダムで取得
		}
		else if (police_wall_seconds == 75) {
		    //パトカーの座標の初期化＆ステート変更
			police_wall_state = 16;
			for (int i = 0; i < POLICE_WALL; i++) {
				enemy_police_wall_x[i] = 1200;
				enemy_police_wall_y[i] = 335 + (100 * i);
			}
		}
		else if (police_wall_seconds == 80) {
			police_wall_state = 17;
		}
		else if (police_wall_seconds == 85) {
			police_wall_random = 0;
			police_wall_state = 18;
		}
		else if (police_wall_seconds == 88) {
			police_wall_random = rand() % 4 + 1;//1～4の数値をランダムで取得
		}
		else if (police_wall_seconds == 90) {
		    //パトカーの座標の初期化＆ステート変更
			police_wall_state = 19;
			for (int i = 0; i < POLICE_WALL; i++) {
				enemy_police_wall_x[i] = 1200;
				enemy_police_wall_y[i] = 335 + (100 * i);
			}
		}
		else if (police_wall_seconds == 95) {
			police_wall_state = 20;
		}
		else if (police_wall_seconds == 100) {
			police_wall_random = 0;
			police_wall_state = 21;
		}
		else if (police_wall_seconds == 103) {
			police_wall_random = rand() % 4 + 1;//1～4の数値をランダムで取得
		}
		else if (police_wall_seconds == 105) {
		    //パトカーの座標の初期化＆ステート変更
			police_wall_state = 22;
			for (int i = 0; i < POLICE_WALL; i++) {
				enemy_police_wall_x[i] = 1200;
				enemy_police_wall_y[i] = 335 + (100 * i);
			}
		}
		else if (police_wall_seconds == 110) {
			police_wall_state = 23;
		}
		else if (police_wall_seconds == 115) {
			police_wall_random = 0;
			police_wall_state = 24;
		}
		else if (police_wall_seconds == 120) {
		    //85秒に戻してループさせる
			police_wall_seconds = 85;
		}

		if (police_wall_state == 2 || police_wall_state == 5) {
			//一回目の壁移動
			switch (police_wall_random)
			{
			case 1:
				enemy_police_wall_x[0] = enemy_police_wall_x[0] - 10 - (speed / 100);
				break;
			case 2:
				enemy_police_wall_x[1] = enemy_police_wall_x[1] - 10 - (speed / 100);
				break;
			case 3:
				enemy_police_wall_x[2] = enemy_police_wall_x[2] - 10 - (speed / 100);
				break;
			case 4:
				enemy_police_wall_x[3] = enemy_police_wall_x[3] - 10 - (speed / 100);
				break;
			default:
				break;
			}
		}
		else if (police_wall_state == 8 || police_wall_state == 11) {
			//二回目の壁移動
			switch (police_wall_random)
			{
			case 1:
				enemy_police_wall_x[0] = enemy_police_wall_x[0] - 10 - (speed / 100);
				enemy_police_wall_x[1] = enemy_police_wall_x[1] - 10 - (speed / 100);
				break;
			case 2:
				enemy_police_wall_x[1] = enemy_police_wall_x[1] - 10 - (speed / 100);
				enemy_police_wall_x[3] = enemy_police_wall_x[3] - 10 - (speed / 100);
				break;
			case 3:
				enemy_police_wall_x[0] = enemy_police_wall_x[0] - 10 - (speed / 100);
				enemy_police_wall_x[2] = enemy_police_wall_x[2] - 10 - (speed / 100);
				break;
			case 4:
				enemy_police_wall_x[2] = enemy_police_wall_x[2] - 10 - (speed / 100);
				enemy_police_wall_x[3] = enemy_police_wall_x[3] - 10 - (speed / 100);
				break;
			default:
				break;
			}
		}
		else if (police_wall_state == 14 || police_wall_state == 17) {
			//三回目の壁移動
			switch (police_wall_random)
			{
			case 1:
				enemy_police_wall_x[0] = enemy_police_wall_x[0] - 10 - (speed / 100);
				enemy_police_wall_x[1] = enemy_police_wall_x[1] - 10 - (speed / 100);
				enemy_police_wall_x[2] = enemy_police_wall_x[2] - 10 - (speed / 100);
				break;
			case 2:
				enemy_police_wall_x[0] = enemy_police_wall_x[0] - 10 - (speed / 100);
				enemy_police_wall_x[1] = enemy_police_wall_x[1] - 10 - (speed / 100);
				enemy_police_wall_x[3] = enemy_police_wall_x[3] - 10 - (speed / 100);
				break;
			case 3:
				enemy_police_wall_x[0] = enemy_police_wall_x[0] - 10 - (speed / 100);
				enemy_police_wall_x[2] = enemy_police_wall_x[2] - 10 - (speed / 100);
				enemy_police_wall_x[3] = enemy_police_wall_x[3] - 10 - (speed / 100);
				break;
			case 4:
				enemy_police_wall_x[1] = enemy_police_wall_x[1] - 10 - (speed / 100);
				enemy_police_wall_x[2] = enemy_police_wall_x[2] - 10 - (speed / 100);
				enemy_police_wall_x[3] = enemy_police_wall_x[3] - 10 - (speed / 100);
				break;
			default:
				break;
			}
		}
		else if (police_wall_state == 20 || police_wall_state == 23) {
			//四回目の壁移動
			switch (police_wall_random)
			{
			case 1:
				enemy_police_wall_x[0] = enemy_police_wall_x[0] - 10 - (speed / 100);
				enemy_police_wall_x[1] = enemy_police_wall_x[1] - 10 - (speed / 100);
				enemy_police_wall_x[2] = enemy_police_wall_x[2] - 10 - (speed / 100);
				enemy_police_wall_x[3] = enemy_police_wall_x[3] - 10 - (speed / 100);
				break;
			case 2:
				enemy_police_wall_x[0] = enemy_police_wall_x[0] - 10 - (speed / 100);
				enemy_police_wall_x[1] = enemy_police_wall_x[1] - 10 - (speed / 100);
				enemy_police_wall_x[2] = enemy_police_wall_x[2] - 5 - (speed / 100);
				enemy_police_wall_x[3] = enemy_police_wall_x[3] - 5 - (speed / 100);
				break;
			case 3:
				enemy_police_wall_x[0] = enemy_police_wall_x[0] - 5 - (speed / 100);
				enemy_police_wall_x[1] = enemy_police_wall_x[1] - 5 - (speed / 100);
				enemy_police_wall_x[2] = enemy_police_wall_x[2] - 10 - (speed / 100);
				enemy_police_wall_x[3] = enemy_police_wall_x[3] - 10 - (speed / 100);
				break;
			case 4:
				enemy_police_wall_x[0] = enemy_police_wall_x[0] - 12 - (speed / 100);
				enemy_police_wall_x[1] = enemy_police_wall_x[1] - 9 - (speed / 100);
				enemy_police_wall_x[2] = enemy_police_wall_x[2] - 6 - (speed / 100);
				enemy_police_wall_x[3] = enemy_police_wall_x[3] - 3 - (speed / 100);
				break;
			default:
				break;
			}
		}
	}
}

void MainScene::police_wall_draw()
{
	if (police_wall_state == 1 || police_wall_state == 4) {
		switch (police_wall_random)
		{
		case 1:
			sprite_batch->Draw(
				sprite_danger,
				XMUINT2(100, 100),
				SimpleMath::Vector2(1100, 330),
				SimpleMath::Vector4(alpha_danger, alpha_danger, alpha_danger, alpha_danger)
			);
			break;
		case 2:
			sprite_batch->Draw(
				sprite_danger,
				XMUINT2(100, 100),
				SimpleMath::Vector2(1100, 430),
				SimpleMath::Vector4(alpha_danger, alpha_danger, alpha_danger, alpha_danger)
			);
			break;
		case 3:
			sprite_batch->Draw(
				sprite_danger,
				XMUINT2(100, 100),
				SimpleMath::Vector2(1100, 530),
				SimpleMath::Vector4(alpha_danger, alpha_danger, alpha_danger, alpha_danger)
			);
			break;
		case 4:
			sprite_batch->Draw(
				sprite_danger,
				XMUINT2(100, 100),
				SimpleMath::Vector2(1100, 630),
				SimpleMath::Vector4(alpha_danger, alpha_danger, alpha_danger, alpha_danger)
			);
			break;
		default:
			break;
		}
	}
	else if (police_wall_state == 2 || police_wall_state == 5) {
		switch (police_wall_random)
		{
		case 1:
			sprite_batch->Draw(
				sprite_enemy_police_wall,
				XMUINT2(107, 98),
				SimpleMath::Vector2(enemy_police_wall_x[0], enemy_police_wall_y[0]),
				SimpleMath::Vector4(alpha_danger, alpha_danger, alpha_danger, alpha_danger)
			);
			break;
		case 2:
			sprite_batch->Draw(
				sprite_enemy_police_wall,
				XMUINT2(107, 98),
				SimpleMath::Vector2(enemy_police_wall_x[1], enemy_police_wall_y[1]),
				SimpleMath::Vector4(alpha_danger, alpha_danger, alpha_danger, alpha_danger)
			);
			break;
		case 3:
			sprite_batch->Draw(
				sprite_enemy_police_wall,
				XMUINT2(107, 98),
				SimpleMath::Vector2(enemy_police_wall_x[2], enemy_police_wall_y[2]),
				SimpleMath::Vector4(alpha_danger, alpha_danger, alpha_danger, alpha_danger)
			);
			break;
		case 4:
			sprite_batch->Draw(
				sprite_enemy_police_wall,
				XMUINT2(107, 98),
				SimpleMath::Vector2(enemy_police_wall_x[3], enemy_police_wall_y[3]),
				SimpleMath::Vector4(alpha_danger, alpha_danger, alpha_danger, alpha_danger)
			);
			break;
		default:
			break;
		}
	}
	else if (police_wall_state == 7 || police_wall_state == 10) {
		//ランダム数値にあった座標に危険マーク画像を表示
		switch (police_wall_random)
		{
		case 1:
				sprite_batch->Draw(
					sprite_danger,
					XMUINT2(100, 100),
					SimpleMath::Vector2(1100, 330),
					SimpleMath::Vector4(alpha_danger, alpha_danger, alpha_danger, alpha_danger)
				);

				sprite_batch->Draw(
					sprite_danger,
					XMUINT2(100, 100),
					SimpleMath::Vector2(1100, 430),
					SimpleMath::Vector4(alpha_danger, alpha_danger, alpha_danger, alpha_danger)
				);
			break;
		case 2:
			sprite_batch->Draw(
				sprite_danger,
				XMUINT2(100, 100),
				SimpleMath::Vector2(1100, 430),
				SimpleMath::Vector4(alpha_danger, alpha_danger, alpha_danger, alpha_danger)
			);

			sprite_batch->Draw(
				sprite_danger,
				XMUINT2(100, 100),
				SimpleMath::Vector2(1100, 630),
				SimpleMath::Vector4(alpha_danger, alpha_danger, alpha_danger, alpha_danger)
			);
			break;
		case 3:
			sprite_batch->Draw(
				sprite_danger,
				XMUINT2(100, 100),
				SimpleMath::Vector2(1100, 330),
				SimpleMath::Vector4(alpha_danger, alpha_danger, alpha_danger, alpha_danger)
			);

			sprite_batch->Draw(
				sprite_danger,
				XMUINT2(100, 100),
				SimpleMath::Vector2(1100, 530),
				SimpleMath::Vector4(alpha_danger, alpha_danger, alpha_danger, alpha_danger)
			);
			break;
		case 4:
			sprite_batch->Draw(
				sprite_danger,
				XMUINT2(100, 100),
				SimpleMath::Vector2(1100, 530),
				SimpleMath::Vector4(alpha_danger, alpha_danger, alpha_danger, alpha_danger)
			);

			sprite_batch->Draw(
				sprite_danger,
				XMUINT2(100, 100),
				SimpleMath::Vector2(1100, 630),
				SimpleMath::Vector4(alpha_danger, alpha_danger, alpha_danger, alpha_danger)
			);
			break;
		default:
			break;
		}
	}
	else if (police_wall_state == 8 || police_wall_state == 11) {
		switch (police_wall_random)
		{
		case 1:
			sprite_batch->Draw(
				sprite_enemy_police_wall,
				XMUINT2(107, 98),
				SimpleMath::Vector2(enemy_police_wall_x[0], enemy_police_wall_y[0]),
				SimpleMath::Vector4(alpha, alpha, alpha, alpha)
			);

			sprite_batch->Draw(
				sprite_enemy_police_wall,
				XMUINT2(107, 98),
				SimpleMath::Vector2(enemy_police_wall_x[1], enemy_police_wall_y[1]),
				SimpleMath::Vector4(alpha, alpha, alpha, alpha)
			);
			break;
		case 2:
			sprite_batch->Draw(
				sprite_enemy_police_wall,
				XMUINT2(107, 98),
				SimpleMath::Vector2(enemy_police_wall_x[1], enemy_police_wall_y[1]),
				SimpleMath::Vector4(alpha, alpha, alpha, alpha)
			);

			sprite_batch->Draw(
				sprite_enemy_police_wall,
				XMUINT2(107, 98),
				SimpleMath::Vector2(enemy_police_wall_x[3], enemy_police_wall_y[3]),
				SimpleMath::Vector4(alpha, alpha, alpha, alpha)
			);
			break;
		case 3:
			sprite_batch->Draw(
				sprite_enemy_police_wall,
				XMUINT2(107, 98),
				SimpleMath::Vector2(enemy_police_wall_x[0], enemy_police_wall_y[0]),
				SimpleMath::Vector4(alpha, alpha, alpha, alpha)
			);

			sprite_batch->Draw(
				sprite_enemy_police_wall,
				XMUINT2(107, 98),
				SimpleMath::Vector2(enemy_police_wall_x[2], enemy_police_wall_y[2]),
				SimpleMath::Vector4(alpha, alpha, alpha, alpha)
			);
			break;
		case 4:
			sprite_batch->Draw(
				sprite_enemy_police_wall,
				XMUINT2(107, 98),
				SimpleMath::Vector2(enemy_police_wall_x[2], enemy_police_wall_y[2]),
				SimpleMath::Vector4(alpha, alpha, alpha, alpha)
			);

			sprite_batch->Draw(
				sprite_enemy_police_wall,
				XMUINT2(107, 98),
				SimpleMath::Vector2(enemy_police_wall_x[3], enemy_police_wall_y[3]),
				SimpleMath::Vector4(alpha, alpha, alpha, alpha)
			);
			break;
		default:
			break;
		}
	}
	else if (police_wall_state == 13 || police_wall_state == 16) {
	//ランダム数値にあった座標に危険マーク画像を表示
	switch (police_wall_random)
	{
	case 1:
		sprite_batch->Draw(
			sprite_danger,
			XMUINT2(100, 100),
			SimpleMath::Vector2(1100, 330),
			SimpleMath::Vector4(alpha_danger, alpha_danger, alpha_danger, alpha_danger)
		);

		sprite_batch->Draw(
			sprite_danger,
			XMUINT2(100, 100),
			SimpleMath::Vector2(1100, 430),
			SimpleMath::Vector4(alpha_danger, alpha_danger, alpha_danger, alpha_danger)
		);

		sprite_batch->Draw(
			sprite_danger,
			XMUINT2(100, 100),
			SimpleMath::Vector2(1100, 530),
			SimpleMath::Vector4(alpha_danger, alpha_danger, alpha_danger, alpha_danger)
		);
		break;
	case 2:
		sprite_batch->Draw(
			sprite_danger,
			XMUINT2(100, 100),
			SimpleMath::Vector2(1100, 430),
			SimpleMath::Vector4(alpha_danger, alpha_danger, alpha_danger, alpha_danger)
		);

		sprite_batch->Draw(
			sprite_danger,
			XMUINT2(100, 100),
			SimpleMath::Vector2(1100, 630),
			SimpleMath::Vector4(alpha_danger, alpha_danger, alpha_danger, alpha_danger)
		);
		break;
	case 3:
		sprite_batch->Draw(
			sprite_danger,
			XMUINT2(100, 100),
			SimpleMath::Vector2(1100, 330),
			SimpleMath::Vector4(alpha_danger, alpha_danger, alpha_danger, alpha_danger)
		);

		sprite_batch->Draw(
			sprite_danger,
			XMUINT2(100, 100),
			SimpleMath::Vector2(1100, 530),
			SimpleMath::Vector4(alpha_danger, alpha_danger, alpha_danger, alpha_danger)
		);
		break;
	case 4:
		sprite_batch->Draw(
			sprite_danger,
			XMUINT2(100, 100),
			SimpleMath::Vector2(1100, 530),
			SimpleMath::Vector4(alpha_danger, alpha_danger, alpha_danger, alpha_danger)
		);

		sprite_batch->Draw(
			sprite_danger,
			XMUINT2(100, 100),
			SimpleMath::Vector2(1100, 630),
			SimpleMath::Vector4(alpha_danger, alpha_danger, alpha_danger, alpha_danger)
		);
		break;
	default:
		break;
	}
		if (パトカー壁ランダム == 1) {
			SpriteBatch.Draw(*危険, Vector3(1100, 330, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1100, 430, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1100, 530, 0.0f));
		}
		else if (パトカー壁ランダム == 2) {
			SpriteBatch.Draw(*危険, Vector3(1100, 430, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1100, 630, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1100, 330, 0.0f));
		}
		else if (パトカー壁ランダム == 3) {
			SpriteBatch.Draw(*危険, Vector3(1100, 530, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1100, 330, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1100, 630, 0.0f));
		}
		else if (パトカー壁ランダム == 4) {
			SpriteBatch.Draw(*危険, Vector3(1100, 630, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1100, 530, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1100, 430, 0.0f));
		}
	}
	else if (police_wall_state == 14 || police_wall_state == 17) {

		if (パトカー壁ランダム == 1) {
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー_x, 壁パトカー_y, 0.0f));
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー2_x, 壁パトカー2_y, 0.0f));
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー3_x, 壁パトカー3_y, 0.0f));
		}
		else if (パトカー壁ランダム == 2) {
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー2_x, 壁パトカー2_y, 0.0f));
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー4_x, 壁パトカー4_y, 0.0f));
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー_x, 壁パトカー_y, 0.0f));
		}
		else if (パトカー壁ランダム == 3) {
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー3_x, 壁パトカー3_y, 0.0f));
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー_x, 壁パトカー_y, 0.0f));
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー4_x, 壁パトカー4_y, 0.0f));
		}
		else if (パトカー壁ランダム == 4) {
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー4_x, 壁パトカー4_y, 0.0f));
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー3_x, 壁パトカー3_y, 0.0f));
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー2_x, 壁パトカー2_y, 0.0f));
		}
	}
	else if (police_wall_state == 19 || police_wall_state == 22) {

		if (パトカー壁ランダム == 1) {
			SpriteBatch.Draw(*危険, Vector3(1100, 330, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1100, 430, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1100, 530, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1100, 630, 0.0f));
		}
		else if (パトカー壁ランダム == 2) {
			SpriteBatch.Draw(*危険, Vector3(1000, 330, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1000, 430, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1100, 530, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1100, 630, 0.0f));
		}
		else if (パトカー壁ランダム == 3) {
			SpriteBatch.Draw(*危険, Vector3(1100, 330, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1100, 430, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1000, 530, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1000, 630, 0.0f));
		}
		else if (パトカー壁ランダム == 4) {
			SpriteBatch.Draw(*危険, Vector3(1150, 330, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1100, 430, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1050, 530, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1000, 630, 0.0f));
		}
	}
	else if (police_wall_state == 20 || police_wall_state == 23) {

		if (パトカー壁ランダム == 1) {
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー_x, 壁パトカー_y, 0.0f));
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー2_x, 壁パトカー2_y, 0.0f));
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー3_x, 壁パトカー3_y, 0.0f));
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー4_x, 壁パトカー4_y, 0.0f));
		}
		else if (パトカー壁ランダム == 2) {
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー_x, 壁パトカー_y, 0.0f));
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー2_x, 壁パトカー2_y, 0.0f));
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー3_x, 壁パトカー3_y, 0.0f));
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー4_x, 壁パトカー4_y, 0.0f));
		}
		else if (パトカー壁ランダム == 3) {
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー_x, 壁パトカー_y, 0.0f));
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー2_x, 壁パトカー2_y, 0.0f));
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー3_x, 壁パトカー3_y, 0.0f));
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー4_x, 壁パトカー4_y, 0.0f));
		}
		else if (パトカー壁ランダム == 4) {
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー_x, 壁パトカー_y, 0.0f));
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー2_x, 壁パトカー2_y, 0.0f));
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー3_x, 壁パトカー3_y, 0.0f));
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー4_x, 壁パトカー4_y, 0.0f));
		}
	}
}