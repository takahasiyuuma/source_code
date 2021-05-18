//
// DifficultysettingScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"

extern void ExitGame() noexcept;

int DifficultysettingScene::game_mode_state;

// Initialize a variable and audio resources.
void DifficultysettingScene::Initialize()
{
	game_mode_state = 0;
	alpha           = 0.0f;
	elapsedTime     = 0.0f;
	next_scene_flag = false;
	start_flag      = false;

	bgm      = make_unique<SoundEffect>(DXTK->AudioEngine, L"BGM�ݒ�.wav");
	bgm_loop = bgm->CreateInstance();
	bgm_loop ->Stop(true);

	engine_stop_se    = make_unique<SoundEffect>(DXTK->AudioEngine, L"SE�G���W����~��.wav");
	decision_sound_se = make_unique<SoundEffect>(DXTK->AudioEngine, L"SE���艹.wav");
}

// Allocate all memory the Direct3D and Direct2D resources.
void DifficultysettingScene::LoadAssets()
{
	ResourceUpload.CreateDescriptorHeap(DXTK->PrimaryDevice, 1);//���\������摜�̐�
	ResourceUpload.ResourceUploadBegin(DXTK->PrimaryDevice);
	sprite_batch = ResourceUpload.CreateSpriteBatch();

	D3D12_VIEWPORT viewport = {
		0.0f, 0.0f,
		static_cast<float>(DXTK->ScreenWidth), static_cast<float>(DXTK->ScreenHeight),
		D3D12_MIN_DEPTH, D3D12_MAX_DEPTH
	};
	sprite_batch->SetViewport(viewport);

	sprite_bg = ResourceUpload.CreateTexture(L"��Փx�ݒ���.png", 0);

	ResourceUpload.ResourceUploadEnd(DXTK->PrimaryCommandQueue);
}

// Releasing resources required for termination.
void DifficultysettingScene::Terminate()
{
	DXTK->AudioEngine->Reset();
	DXTK->WaitForGpu();
}

// Direct3D resource cleanup.
void DifficultysettingScene::OnDeviceLost()
{
	sprite_batch.reset();
}

// Restart any looped sounds here
void DifficultysettingScene::OnRestartSound()
{
	bgm_loop->Play(true);
}

// Updates the scene.
NextScene DifficultysettingScene::Update(const float deltaTime)
{
	// If you use 'deltaTime', remove it.
	UNREFERENCED_PARAMETER(deltaTime);

	// TODO: Add your game logic here.

	if (!start_flag) {
		//�^�C�g����ʂ���̃��[�h��̃t�F�[�h�C����
		if (alpha <= 1.0f) {
			alpha += (0.35f * deltaTime);
		}
		else {
			//�t�F�[�h�C���I��������start_flag��true�Ɂ�
			start_flag = true;
		}
	}
	else {
		bgm_loop->Play(true);

		if (!next_scene_flag) {
			//�^�C�g����ʂ֖߂遫
			if (DXTK->KeyEvent->pressed.E) {
				next_scene_flag = true;
				//�^�C�g����ʂ�
			}
			//��Փx�ݒ聫
			if (game_mode_state == 0) {
				if (DXTK->KeyEvent->pressed.W) {
					//�m�[�}�����[�h����n�[�h���[�h��
					game_mode_state = 1;
					decision_sound_se->Play();
				}
				else if (DXTK->KeyEvent->pressed.S) {
					//�m�[�}�����[�h����G�N�X�g�����[�h��
					game_mode_state = 2;
					decision_sound_se->Play();
				}
			}
			else if (game_mode_state == 1) {
				if (DXTK->KeyEvent->pressed.W) {
					//�n�[�h���[�h����G�N�X�g�����[�h��
					game_mode_state = 2;
					decision_sound_se->Play();
				}
				else if (DXTK->KeyEvent->pressed.S) {
					//�n�[�h���[�h����m�[�}�����[�h��
					game_mode_state = 0;
					decision_sound_se->Play();
				}
			}
			else if (game_mode_state == 2) {
				if (DXTK->KeyEvent->pressed.W) {
					//�G�N�X�g�����[�h����m�[�}�����[�h��
					game_mode_state = 0;
					decision_sound_se->Play();
				}
				else if (DXTK->KeyEvent->pressed.S) {
					//�G�N�X�g�����[�h����n�[�h���[�h��
					game_mode_state = 1;
					decision_sound_se->Play();
				}
			}
		}
		else
		{
			//�t�F�[�h�A�E�g��
			elapsedTime += deltaTime;
			alpha -= (0.35f * deltaTime);
			if (elapsedTime >= 4.3f)
				return NextScene::TitleScene;
		}
	}

	return NextScene::Continue;
}

// Draws the scene.
void DifficultysettingScene::Render()
{
	// TODO: Add your rendering code here.
	DXTK->Clear(PrimaryAdapter, Colors::Black);//CornflowerBlue

	ID3D12DescriptorHeap* heaps[] = { ResourceUpload.GetDescriptorHeap() };
	DXTK->PrimaryCommandList->SetDescriptorHeaps(_countof(heaps), heaps);
	sprite_batch->Begin(DXTK->PrimaryCommandList);

	sprite_batch->Draw(
		sprite_bg,
		XMUINT2(1280, 720),
		SimpleMath::Vector2(0.0f, 0.0f),
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
		D2D1::ColorF(0.6f, 1.0f, 0.0f, alpha),
		&text_brush
	);
	//�ԁA�A�΁A�����x
	DXTK->DirectWrite->CreateTextFormat(
		L"�l�r �S�V�b�N", NULL, DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		50, // �T�C�Y
		L"ja-JP", &text_format
	);
	text_string = L"�Q�[�����[�h�ݒ�";
	text_rect = D2D1::RectF(35, 10, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	text_string = L"E �^�C�g����";
	text_rect = D2D1::RectF(950, 660, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	if (game_mode_state == 0) {
		game_mode_state_0_text_draw();
	}
	else if (game_mode_state == 1) {
		game_mode_state_1_text_draw();
	}
	else if (game_mode_state == 2) {
		game_mode_state_2_text_draw();
	}

	DXTK->Direct2D->CreateSolidColorBrush(
		D2D1::ColorF(1.0f, 0.1f, 0.1f, alpha),
		&text_brush
	);
	//�ԁA�A�΁A�����x
	DXTK->DirectWrite->CreateTextFormat(
		L"�l�r �S�V�b�N", NULL, DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		50, // �T�C�Y
		L"ja-JP", &text_format
	);
	text_string = L"���Q�[���V�X�e���Ȃǂ͂ǂ̃Q�[�����[�h�ł�";
	text_rect = D2D1::RectF(50, 500, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	text_string = L"��{�I�ɕς��܂���B�Ȃ��A�Q�[���V�X�e����";
	text_rect = D2D1::RectF(50, 550, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	text_string = L"�����̓^�C�g����ʂ���s����";
	text_rect = D2D1::RectF(50, 600, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	text_string = L"�u���̃Q�[���̐����v�ł��Ă��܂��B";
	text_rect = D2D1::RectF(50, 650, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	DXTK->Direct2DEndDraw();
}

void DifficultysettingScene::game_mode_state_0_text_draw()
{
	ComPtr<ID2D1SolidColorBrush> text_brush;
	ComPtr<IDWriteTextFormat>    text_format;
	WCHAR* text_string;
	D2D1_RECT_F text_rect;

	DXTK->Direct2D->CreateSolidColorBrush(
		D2D1::ColorF(1.0f, 0.45f, 0.0f, alpha),
		&text_brush
	);
	//�ԁA�A�΁A�����x
	DXTK->DirectWrite->CreateTextFormat(
		L"�l�r �S�V�b�N", NULL, DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		50, // �T�C�Y
		L"ja-JP", &text_format
	);
	text_string = L"W�ES�ŕύX�B���݂̃Q�[�����[�h:�m�[�}�����[�h";
	text_rect = D2D1::RectF(50, 100, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	DXTK->Direct2D->CreateSolidColorBrush(
		D2D1::ColorF(0.6f, 1.0f, 0.0f, alpha),
		&text_brush
	);
	//�ԁA�A�΁A�����x

	text_string = L"�m�[�}�����[�h�̐���";
	text_rect = D2D1::RectF(50, 200, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	text_string = L"��{�I�ȃQ�[�����[�h�B";
	text_rect = D2D1::RectF(50, 260, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);
}

void DifficultysettingScene::game_mode_state_1_text_draw()
{
	ComPtr<ID2D1SolidColorBrush> text_brush;
	ComPtr<IDWriteTextFormat>    text_format;
	WCHAR* text_string;
	D2D1_RECT_F text_rect;

	DXTK->Direct2D->CreateSolidColorBrush(
		D2D1::ColorF(1.0f, 0.45f, 0.0f, alpha),
		&text_brush
	);
	//�ԁA�A�΁A�����x
	DXTK->DirectWrite->CreateTextFormat(
		L"�l�r �S�V�b�N", NULL, DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		50, // �T�C�Y
		L"ja-JP", &text_format
	);
	text_string = L"W�ES�ŕύX�B���݂̃Q�[�����[�h:�n�[�h���[�h";
	text_rect = D2D1::RectF(50, 100, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	DXTK->Direct2D->CreateSolidColorBrush(
		D2D1::ColorF(0.6f, 1.0f, 0.0f, alpha),
		&text_brush
	);
	//�ԁA�A�΁A�����x

	text_string = L"�n�[�h���[�h�̐���";
	text_rect = D2D1::RectF(50, 200, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	text_string = L"�m�[�}�����[�h��蓦�������܂ł�";
	text_rect = D2D1::RectF(50, 260, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	text_string = L"�^�C����60�b�������Q�[�����[�h�B";
	text_rect = D2D1::RectF(50, 310, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	text_string = L"�G�̔z�u�A���Ȃǃm�[�}�����[�h�ɂ�";
	text_rect = D2D1::RectF(50, 360, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	text_string = L"���݂��Ȃ����̂��ǉ�����Ă��܂��B";
	text_rect = D2D1::RectF(50, 410, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);
}

void DifficultysettingScene::game_mode_state_2_text_draw()
{
	ComPtr<ID2D1SolidColorBrush> text_brush;
	ComPtr<IDWriteTextFormat>    text_format;
	WCHAR* text_string;
	D2D1_RECT_F text_rect;

	DXTK->Direct2D->CreateSolidColorBrush(
		D2D1::ColorF(1.0f, 0.45f, 0.0f, alpha),
		&text_brush
	);
	//�ԁA�A�΁A�����x
	DXTK->DirectWrite->CreateTextFormat(
		L"�l�r �S�V�b�N", NULL, DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		50, // �T�C�Y
		L"ja-JP", &text_format
	);
	text_string = L"W�ES�ŕύX�B���݂̃Q�[�����[�h:�G�N�X�g�����[�h";
	text_rect = D2D1::RectF(50, 100, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	DXTK->Direct2D->CreateSolidColorBrush(
		D2D1::ColorF(0.6f, 1.0f, 0.0f, alpha),
		&text_brush
	);
	//�ԁA�A�΁A�����x

	text_string = L"�G�N�X�g�����[�h�̐���";
	text_rect = D2D1::RectF(50, 200, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	text_string = L"�ł��邾���������Ԍx�@����";
		text_rect = D2D1::RectF(50, 260, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	text_string = L"�����邱�Ƃ��ڕW�̃Q�[�����[�h�B";
	text_rect = D2D1::RectF(50, 310, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	text_string = L"�G�̔z�u�A���Ȃǃm�[�}�����[�h�ɂ�";
	text_rect = D2D1::RectF(50, 360, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	text_string = L"���݂��Ȃ����̂��ǉ�����Ă��܂��B";
	text_rect = D2D1::RectF(50, 410, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);
}