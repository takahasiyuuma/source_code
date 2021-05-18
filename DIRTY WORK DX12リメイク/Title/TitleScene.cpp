//
// TitleScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"

int TitleScene::スコア = 100;
int TitleScene::スコア2 = 0;
int TitleScene::スコア3 = 0;
int TitleScene::ハイスコア = 0;
int TitleScene::逃走タイム秒3 = 0;
int TitleScene::ハードハイスコア = 0;
int TitleScene::ハード逃走タイム秒3 = 0;

extern void ExitGame() noexcept;

// Initialize a variable and audio resources.
void TitleScene::Initialize()
{
	bgm = make_unique<SoundEffect>(DXTK->AudioEngine, L"BGMタイトル.wav");
	bgm_loop = bgm->CreateInstance();
	bgm_loop->Stop(true);

	engine_start_up_se = make_unique<SoundEffect>(DXTK->AudioEngine, L"SEエンジン始動音.wav");
	decision_sound_se  = make_unique<SoundEffect>(DXTK->AudioEngine, L"SE決定音.wav");

	title_state   = 0;
	elapsedTime   = 0.0f;
	alpha         = 0.0f;
	player_mini_x = 40;
	player_mini_y = 270;
	nextSceneFlag = false;
	start_flag    = false;
	nextScene     = NextScene::Continue;
}

// Allocate all memory the Direct3D and Direct2D resources.
void TitleScene::LoadAssets()
{
	ResourceUpload.CreateDescriptorHeap(DXTK->PrimaryDevice, 2);//←表示する画像の数
	ResourceUpload.ResourceUploadBegin(DXTK->PrimaryDevice);
	sprite_batch = ResourceUpload.CreateSpriteBatch();

	D3D12_VIEWPORT viewport = {
		0.0f, 0.0f,
		static_cast<float>(DXTK->ScreenWidth), static_cast<float>(DXTK->ScreenHeight),
		D3D12_MIN_DEPTH, D3D12_MAX_DEPTH
	};
	sprite_batch->SetViewport(viewport);

	sprite_bg          = ResourceUpload.CreateTexture(L"タイトル画面.png", 0);
	sprite_player_mini = ResourceUpload.CreateTexture(L"自機ミニ.png", 1);

	ResourceUpload.ResourceUploadEnd(DXTK->PrimaryCommandQueue);
}

// Releasing resources required for termination.
void TitleScene::Terminate()
{
	DXTK->AudioEngine->Reset();
	DXTK->WaitForGpu();
}
// Direct3D resource cleanup.
void TitleScene::OnDeviceLost()
{
	sprite_batch.reset();
}

// Restart any looped sounds here
void TitleScene::OnRestartSound()
{
	bgm_loop->Play(true);
}

// Updates the scene.
NextScene TitleScene::Update(const float deltaTime)
{
	// If you use 'deltaTime', remove it.
	UNREFERENCED_PARAMETER(deltaTime);

	// TODO: Add your game logic here.

	if (!start_flag) {
		if (alpha <= 1.0f) {
			alpha += (0.35f * deltaTime);
		}
		else {
			//フェードイン終了したらstart_flagをtrueに↓
			start_flag = true;
		}
	}
	else{
		bgm_loop->Play(true);
		//次のシーンへ移行する処理↓
		if (!nextSceneFlag) {

			if (title_state == 0) {
				//プレイヤーミニの位置をゲームスタートの横に設定
				player_mini_x = 40;
				player_mini_y = 270;

				if (DXTK->KeyEvent->pressed.W) {
					//ゲームスタートからこのゲームの説明へ
					title_state      = 2;
					decision_sound_se->Play();
				}
				else if (DXTK->KeyEvent->pressed.S) {
					//ゲームスタートからゲームモード設定へ
					title_state      = 1;
					decision_sound_se->Play();
				}

				if (DXTK->KeyEvent->pressed.E) {
					スコア            = 100000000;
					スコア2           = 0;
					スコア3           = 0;
					engine_start_up_se->Play();
					nextSceneFlag     = true;
					nextScene         = NextScene::MainScene;
					//メイン画面へシーン切り替え
				}
			}
			else if (title_state == 1) {
				//プレイヤーミニの位置をゲームモード設定の横に設定
				player_mini_x = 570;
				player_mini_y = 610;

				if (DXTK->KeyEvent->pressed.W) {
					//ゲームモード設定からゲームスタートへ
					title_state      = 0;
					decision_sound_se->Play();
				}
				else if (DXTK->KeyEvent->pressed.S) {
					//ゲームモード設定からこのゲームの説明へ
					title_state      = 2;
					decision_sound_se->Play();
				}

				if (DXTK->KeyEvent->pressed.E) {
					engine_start_up_se->Play();
					nextSceneFlag = true;
					nextScene = NextScene::DifficultysettingScene;
					//ゲームモード設定画面へシーン切り替え
				}
			}
			else if (title_state == 2) {
				//プレイヤーミニの位置をこのゲームの説明の横に設定
				player_mini_x = 570;
				player_mini_y = 660;

				if (DXTK->KeyEvent->pressed.W) {
					//このゲームの説明からゲームモード設定へ
					title_state      = 1;
					decision_sound_se->Play();
				}
				else if (DXTK->KeyEvent->pressed.S) {
					//このゲームの説明からゲームスタートへ
					title_state      = 0;
					decision_sound_se->Play();
				}

				if (DXTK->KeyEvent->pressed.E) {
					engine_start_up_se->Play();
					nextSceneFlag     = true;
					nextScene         = NextScene::DescriptionScene;
					//説明画面へシーン切り替え
				}
			}
		}
		else
		{
			//フェードアウトが終了後、次のシーンへ移行する↓
			elapsedTime += deltaTime;
			alpha -= (0.35f * deltaTime);
			if (elapsedTime >= 4.3f)
				return nextScene;
		}
	}

	return NextScene::Continue;
}

// Draws the scene.
void TitleScene::Render()
{
	// TODO: Add your rendering code here.
	DXTK->Clear(PrimaryAdapter, Colors::Black);//CornflowerBlue

	ID3D12DescriptorHeap* heaps[] = {ResourceUpload.GetDescriptorHeap() };
	DXTK->PrimaryCommandList->SetDescriptorHeaps(_countof(heaps), heaps);
	sprite_batch->Begin(DXTK->PrimaryCommandList);

	sprite_batch->Draw(
		sprite_bg,
		XMUINT2(1280, 720),
		SimpleMath::Vector2(0.0f, 0.0f),
		SimpleMath::Vector4(alpha, alpha, alpha, alpha)
	);

	sprite_batch->Draw(
		sprite_player_mini,
		XMUINT2(69, 44),
		SimpleMath::Vector2(player_mini_x, player_mini_y),
		SimpleMath::Vector4(alpha, alpha, alpha, alpha)
	);

	sprite_batch->Draw(
		sprite_player_mini,
		XMUINT2(69, 44),
		SimpleMath::Vector2(player_mini_x + 10.0f, player_mini_y + 10.0f),
		SimpleMath::Vector4(alpha, alpha, alpha, alpha)
	);

	sprite_batch->End();

	DXTK->ExecutePrimaryCommandLists();

	DXTK->Direct2DBeginDraw();
	DXTK->Direct2D->SetTransform(D2D1::Matrix3x2F::Identity());

	ComPtr<ID2D1SolidColorBrush> text_brush;
	ComPtr<IDWriteTextFormat>    text_format;
	WCHAR* text_string;
	D2D1_RECT_F text_rect;

	DXTK->Direct2D->CreateSolidColorBrush(
		D2D1::ColorF(0.0f, 1.0f, 1.0f, alpha),
		&text_brush
	);
	//赤、青、緑、透明度
	DXTK->DirectWrite->CreateTextFormat(
		L"ＭＳ ゴシック", NULL, DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		50, // サイズ
		L"ja-JP", &text_format
	);
	text_string = L"ゲームスタート";//E ゲームスタート
	text_rect = D2D1::RectF(120, 270, 1280, 720);//130
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	DXTK->Direct2D->CreateSolidColorBrush(
		D2D1::ColorF(0.0f, 0.9f, 0.9f, alpha),
		&text_brush
	);
	//赤、青、緑、透明度
	DXTK->DirectWrite->CreateTextFormat(
		L"ＭＳ ゴシック", NULL, DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		50, // サイズ
		L"ja-JP", &text_format
	);
	text_string = L"ゲームモード設定";//F ゲームモード設定
	text_rect = D2D1::RectF(650, 610, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	DXTK->Direct2D->CreateSolidColorBrush(
		D2D1::ColorF(0.0f, 1.0f, 0.0f, alpha),
		&text_brush
	);
	//赤、青、緑、透明度
	DXTK->DirectWrite->CreateTextFormat(
		L"ＭＳ ゴシック", NULL, DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		50, // サイズ
		L"ja-JP", &text_format
	);
	text_string = L"このゲームの説明";//Q このゲームの説明
	text_rect = D2D1::RectF(650, 660, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	if (DifficultysettingScene::game_mode_state == 0) {
		game_mode_no_text_draw();
	}
	else if (DifficultysettingScene::game_mode_state == 1) {
		game_mode_ha_text_draw();
	}
	else if (DifficultysettingScene::game_mode_state == 2) {
		game_mode_ex_text_draw();
	}

	DXTK->Direct2DEndDraw();
}

void TitleScene::game_mode_no_text_draw()
{
	ComPtr<ID2D1SolidColorBrush> text_brush;
	ComPtr<IDWriteTextFormat>    text_format;
	WCHAR* text_string;
	D2D1_RECT_F text_rect;

	DXTK->Direct2D->CreateSolidColorBrush(
		D2D1::ColorF(1.0f, 0.0f, 1.0f, alpha),
		&text_brush
	);
	//赤、青、緑、透明度
	DXTK->DirectWrite->CreateTextFormat(
		L"ＭＳ ゴシック", NULL, DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		50, // サイズ
		L"ja-JP", &text_format
	);

	text_string = L"現在のゲームモード:N(ノーマルモード)";
	text_rect = D2D1::RectF(10, 10, 1280, 720);
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
		50, // サイズ
		L"ja-JP", &text_format
	);
	WCHAR high_score_text[256];//intなら %d、floatなら %f
	swprintf_s(high_score_text, 256, L"[N]最大の儲け:%d＄", ハイスコア);
	D2D1_RECT_F high_score_text_rect = D2D1::RectF(650, 510, 1280, 720);
	DXTK->Direct2D->DrawText(
		high_score_text, lstrlen(high_score_text),
		text_format.Get(), &high_score_text_rect, text_brush.Get()
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
		50, // サイズ
		L"ja-JP", &text_format
	);
	WCHAR shortest_time_text[256];//intなら %d、floatなら %f
	swprintf_s(high_score_text, 256, L"[N]最短の逃走成功:%d秒", 逃走タイム秒3);
	D2D1_RECT_F shortest_time_text_rect = D2D1::RectF(650, 560, 1280, 720);
	DXTK->Direct2D->DrawText(
		high_score_text, lstrlen(high_score_text),
		text_format.Get(), &shortest_time_text_rect, text_brush.Get()
	);
}

void TitleScene::game_mode_ha_text_draw() {
	ComPtr<ID2D1SolidColorBrush> text_brush;
	ComPtr<IDWriteTextFormat>    text_format;
	WCHAR* text_string;
	D2D1_RECT_F text_rect;

	DXTK->Direct2D->CreateSolidColorBrush(
		D2D1::ColorF(1.0f, 0.0f, 1.0f, alpha),
		&text_brush
	);
	//赤、青、緑、透明度
	DXTK->DirectWrite->CreateTextFormat(
		L"ＭＳ ゴシック", NULL, DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		50, // サイズ
		L"ja-JP", &text_format
	);

	text_string = L"現在のゲームモード:H(ハードモード)";
	text_rect = D2D1::RectF(10, 10, 1280, 720);
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
		50, // サイズ
		L"ja-JP", &text_format
	);
	WCHAR high_score_text[256];//intなら %d、floatなら %f
	swprintf_s(high_score_text, 256, L"[H]最大の儲け:%d＄", ハードハイスコア);
	D2D1_RECT_F high_score_text_rect = D2D1::RectF(650, 510, 1280, 720);
	DXTK->Direct2D->DrawText(
		high_score_text, lstrlen(high_score_text),
		text_format.Get(), &high_score_text_rect, text_brush.Get()
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
		50, // サイズ
		L"ja-JP", &text_format
	);
	WCHAR shortest_time_text[256];//intなら %d、floatなら %f
	swprintf_s(high_score_text, 256, L"[H]最短の逃走成功:%d秒", ハード逃走タイム秒3);
	D2D1_RECT_F shortest_time_text_rect = D2D1::RectF(650, 560, 1280, 720);
	DXTK->Direct2D->DrawText(
		high_score_text, lstrlen(high_score_text),
		text_format.Get(), &shortest_time_text_rect, text_brush.Get()
	);
}

void TitleScene::game_mode_ex_text_draw() {
	ComPtr<ID2D1SolidColorBrush> text_brush;
	ComPtr<IDWriteTextFormat>    text_format;
	WCHAR* text_string;
	D2D1_RECT_F text_rect;

	DXTK->Direct2D->CreateSolidColorBrush(
		D2D1::ColorF(1.0f, 0.0f, 1.0f, alpha),
		&text_brush
	);
	//赤、青、緑、透明度
	DXTK->DirectWrite->CreateTextFormat(
		L"ＭＳ ゴシック", NULL, DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		50, // サイズ
		L"ja-JP", &text_format
	);

	text_string = L"現在のゲームモード:EX(エクストラモード)";
	text_rect = D2D1::RectF(10, 10, 1280, 720);
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
		50, // サイズ
		L"ja-JP", &text_format
	);
	WCHAR high_score_text[256];//intなら %d、floatなら %f
	//swprintf_s(high_score_text, 256, L"[EX]最大の儲け:%d＄", ハードハイスコア);
	//D2D1_RECT_F high_score_text_rect = D2D1::RectF(650, 510, 1280, 720);
	//DXTK->Direct2D->DrawText(
	//	high_score_text, lstrlen(high_score_text),
	//	text_format.Get(), &high_score_text_rect, text_brush.Get()
	//);

	//---

	DXTK->Direct2D->CreateSolidColorBrush(
		D2D1::ColorF(1.0f, 0.0f, 0.0f, alpha),
		&text_brush
	);
	//赤、青、緑、透明度
	DXTK->DirectWrite->CreateTextFormat(
		L"ＭＳ ゴシック", NULL, DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		50, // サイズ
		L"ja-JP", &text_format
	);
	WCHAR shortest_time_text[256];//intなら %d、floatなら %f
	swprintf_s(high_score_text, 256, L"[EX]最大逃走時間:%d秒", ハード逃走タイム秒3);
	D2D1_RECT_F shortest_time_text_rect = D2D1::RectF(650, 560, 1280, 720);
	DXTK->Direct2D->DrawText(
		high_score_text, lstrlen(high_score_text),
		text_format.Get(), &shortest_time_text_rect, text_brush.Get()
	);
}