//
// DescriptionScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"

extern void ExitGame() noexcept;

// Initialize a variable and audio resources.
void DescriptionScene::Initialize()
{
	engine_se      = make_unique<SoundEffect>(DXTK->AudioEngine, L"SE走行中.wav");
	engine_se_loop = engine_se->CreateInstance();
	engine_se_loop ->Stop(true);

	abrupt_steering_up_se      = make_unique<SoundEffect>(DXTK->AudioEngine, L"SE急ハンドル.wav");
	abrupt_steering_up_se_loop = abrupt_steering_up_se->CreateInstance();

	abrupt_steering_down_se      = make_unique<SoundEffect>(DXTK->AudioEngine, L"SE急ハンドル.wav");
	abrupt_steering_down_se_loop = abrupt_steering_down_se->CreateInstance();

	engine_stop_se    = make_unique<SoundEffect>(DXTK->AudioEngine, L"SEエンジン停止音.wav");
	decision_sound_se = make_unique<SoundEffect>(DXTK->AudioEngine, L"SE決定音.wav");

	bgm      = make_unique<SoundEffect>(DXTK->AudioEngine, L"BGM説明.wav");
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
	description_state      = 0;
	alpha                  = 0.0f;
	elapsedTime            = 0.0f;
	next_scene_flag        = false;
	start_flag             = false;
	next_scene             = NextScene::Continue;
}

// Allocate all memory the Direct3D and Direct2D resources.
void DescriptionScene::LoadAssets()
{
	ResourceUpload.CreateDescriptorHeap(DXTK->PrimaryDevice, 6);//←表示する画像の数
	ResourceUpload.ResourceUploadBegin(DXTK->PrimaryDevice);
	sprite_batch = ResourceUpload.CreateSpriteBatch();

	D3D12_VIEWPORT viewport = {
		0.0f, 0.0f,
		static_cast<float>(DXTK->ScreenWidth), static_cast<float>(DXTK->ScreenHeight),
		D3D12_MIN_DEPTH, D3D12_MAX_DEPTH
	};
	sprite_batch->SetViewport(viewport);

	sprite_main_screen        = ResourceUpload.CreateTexture(L"ゲームプレイ画面.png", 0);
	sprite_player             = ResourceUpload.CreateTexture(L"自機.png", 1);
	sprite_player_up          = ResourceUpload.CreateTexture(L"自機斜め上.png", 2);
	sprite_player_down        = ResourceUpload.CreateTexture(L"自機斜め下.png", 3);
	sprite_explanation_window = ResourceUpload.CreateTexture(L"ゲーム操作説明.png", 4);
	sprite_game_system_window = ResourceUpload.CreateTexture(L"ゲームシステム.png", 5);

	ResourceUpload.ResourceUploadEnd(DXTK->PrimaryCommandQueue);
}

// Releasing resources required for termination.
void DescriptionScene::Terminate()
{
	DXTK->AudioEngine->Reset();
	DXTK->WaitForGpu();
}

// Direct3D resource cleanup.
void DescriptionScene::OnDeviceLost()
{

}

// Restart any looped sounds here
void DescriptionScene::OnRestartSound()
{
	engine_se_loop->Play(true);
	bgm_loop      ->Play(true);
}

// Updates the scene.
NextScene DescriptionScene::Update(const float deltaTime)
{
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
		//ゲーム操作説明画面時の処理↓
		if (description_state == 0) {
			if (!next_scene_flag) {
				//ゲームシステム説明画面を表示する↓
				if (DXTK->KeyEvent->pressed.Q) {
					decision_sound_se ->Play();
					description_state = 1;
				}
				//タイトル画面へ戻る↓
				if (DXTK->KeyEvent->pressed.E) {
					engine_stop_se  ->Play();
					next_scene_flag = true;
					next_scene      = NextScene::TitleScene;
					//タイトル画面へ
				}
			}
			else
			{
				//フェードアウト↓
				elapsedTime += deltaTime;
				alpha -= (0.35f * deltaTime);
				if (elapsedTime >= 4.3f)
					return next_scene;
			}
		}//ゲームシステム操作説明画面時の処理↓
		else if (description_state == 1) {
			//ゲーム操作説明画面へ戻る↓
			if (DXTK->KeyEvent->pressed.Q) {
				decision_sound_se ->Play();
				description_state = 0;
			}
		}

		main_bg_update(deltaTime);
		player_update(deltaTime);
	}

	return NextScene::Continue;
}

// Draws the scene.
void DescriptionScene::Render()
{
	// TODO: Add your rendering code here.
	DXTK->Clear(PrimaryAdapter, Colors::Black);

	ID3D12DescriptorHeap* heaps[] = { ResourceUpload.GetDescriptorHeap() };
	DXTK->PrimaryCommandList->SetDescriptorHeaps(_countof(heaps), heaps);
	sprite_batch->Begin(DXTK->PrimaryCommandList);

	main_bg_draw();
	player_draw();
	description_draw();

	sprite_batch->End();

	DXTK->ExecutePrimaryCommandLists();

	DXTK->Direct2DBeginDraw();
	DXTK->Direct2D->SetTransform(D2D1::Matrix3x2F::Identity());

	if (description_state == 0) {

		description_state_0_text_draw();
	}
	else if (description_state == 1) {

		description_state_1_text_draw();
	}

	DXTK->Direct2DEndDraw();
}

void DescriptionScene::main_bg_update(const float deltaTime)
{
	main_bg_x = main_bg_x - 20 - (speed / 100) * deltaTime;
	if (main_bg_x <= -2720.0f) {
		main_bg_x = 0.0f;
	}
}

void DescriptionScene::main_bg_draw()
{
	sprite_batch->Draw(
		sprite_main_screen,
		XMUINT2(4000, 720),
		SimpleMath::Vector2(main_bg_x, 0.0f),
		SimpleMath::Vector4(alpha, alpha, alpha, alpha)
	);
}

void DescriptionScene::player_update(const float deltaTime)
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

void DescriptionScene::player_draw()
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

void DescriptionScene::description_draw()
{
	if (description_state == 0) {

		sprite_batch->Draw(
			sprite_explanation_window,
			XMUINT2(1288, 300),
			SimpleMath::Vector2(0.0f, 0.0f),
			SimpleMath::Vector4(alpha, alpha, alpha, alpha)
		);
	}
	else if (description_state == 1) {

		sprite_batch->Draw(
			sprite_game_system_window,
			XMUINT2(1288, 370),
			SimpleMath::Vector2(0.0f, 0.0f),
			SimpleMath::Vector4(alpha, alpha, alpha, alpha)
		);
	}
}

void DescriptionScene::description_state_0_text_draw()
{
	ComPtr<ID2D1SolidColorBrush> text_brush;
	ComPtr<IDWriteTextFormat>    text_format;
	WCHAR* text_string;
	D2D1_RECT_F text_rect;

	//---

	DXTK->Direct2D->CreateSolidColorBrush(
		D2D1::ColorF(0.6f, 1.0f, 0.0f, alpha),
		&text_brush
	);
	//赤、青、緑、透明度
	DXTK->DirectWrite->CreateTextFormat(
		L"ＭＳ ゴシック", NULL, DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		50, // サイズ
		L"ja-JP", &text_format
	);
	text_string = L"Q ゲームシステム　　　　　　    　　E タイトルへ";
	text_rect = D2D1::RectF(35, 10, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	text_string = L"ゲームプレイ中の操作方法";
	text_rect = D2D1::RectF(35, 60, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	text_string = L"キーボード: 上への移動 Wキー, 下への移動 Sキー";
	text_rect = D2D1::RectF(35, 110, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);
}

void DescriptionScene::description_state_1_text_draw()
{
	ComPtr<ID2D1SolidColorBrush> text_brush;
	ComPtr<IDWriteTextFormat>    text_format;
	WCHAR* text_string;
	D2D1_RECT_F text_rect;

	//---

	DXTK->Direct2D->CreateSolidColorBrush(
		D2D1::ColorF(0.6f, 1.0f, 0.0f, alpha),
		&text_brush
	);
	//赤、青、緑、透明度
	DXTK->DirectWrite->CreateTextFormat(
		L"ＭＳ ゴシック", NULL, DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		30, // サイズ
		L"ja-JP", &text_format
	);
	text_string = L"ゲームシステムの説明";
	text_rect = D2D1::RectF(35, 10, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	DXTK->Direct2D->CreateSolidColorBrush(
		D2D1::ColorF(1.0f, 1.0f, 0.0f, alpha),
		&text_brush
	);
	//赤、青、緑、透明度
	DXTK->DirectWrite->CreateTextFormat(
		L"ＭＳ ゴシック", NULL, DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		30, // サイズ
		L"ja-JP", &text_format
	);
	text_string = L"＄　　 = スコア、ライフ。敵に衝突することで減り、0になったらゲームオーバー。";
	text_rect = D2D1::RectF(30, 40, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	DXTK->Direct2D->CreateSolidColorBrush(
		D2D1::ColorF(0.6f, 0.0f, 1.0f, alpha),
		&text_brush
	);
	//赤、青、緑、透明度
	DXTK->DirectWrite->CreateTextFormat(
		L"ＭＳ ゴシック", NULL, DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		30, // サイズ
		L"ja-JP", &text_format
	);
	text_string = L"タイム = 時間経過で減っていき、タイムが0になったらゲームクリア。";
	text_rect = D2D1::RectF(30, 70, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	DXTK->Direct2D->CreateSolidColorBrush(
		D2D1::ColorF(1.0f, 0.0f, 0.0f, alpha),
		&text_brush
	);
	//赤、青、緑、透明度
	DXTK->DirectWrite->CreateTextFormat(
		L"ＭＳ ゴシック", NULL, DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		30, // サイズ
		L"ja-JP", &text_format
	);
	text_string = L"敵　　 = パトカー、一般車。当たるとパトカーの場合は即死、一般車の場合は＄が減る。";
	text_rect = D2D1::RectF(30, 100, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	DXTK->Direct2D->CreateSolidColorBrush(
		D2D1::ColorF(0.6f, 1.0f, 0.0f, alpha),
		&text_brush
	);
	//赤、青、緑、透明度
	DXTK->DirectWrite->CreateTextFormat(
		L"ＭＳ ゴシック", NULL, DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		30, // サイズ
		L"ja-JP", &text_format
	);
	text_string = L"敵に当たらずに避け続ければ加速し、プレイヤーの操作が速くなったり、一秒で減る";
	text_rect = D2D1::RectF(30, 130, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	text_string = L"タイムが増える。スピード30以上で2秒、スピード50以上で3秒減るようになる。歩道を";
	text_rect = D2D1::RectF(30, 160, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	text_string = L"走るとスピードが落ちていき、タイムも増える。タイムが55秒を超えると後方のパトカーが";
	text_rect = D2D1::RectF(30, 190, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	text_string = L"接近してくる。一定時間で道路を封鎖しているパトカーが出現する。そのパトカーの出現";
	text_rect = D2D1::RectF(30, 220, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	text_string = L"位置は【!!】が表示された車線。時間が経てば経つほど道路を封鎖するパトカーが増える。";
	text_rect = D2D1::RectF(30, 250, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	text_string = L"                                                                         Q で戻る";
	text_rect = D2D1::RectF(30, 300, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);
}