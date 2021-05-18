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
	engine_se      = make_unique<SoundEffect>(DXTK->AudioEngine, L"SE���s��.wav");
	engine_se_loop = engine_se->CreateInstance();
	engine_se_loop ->Stop(true);

	abrupt_steering_up_se      = make_unique<SoundEffect>(DXTK->AudioEngine, L"SE�}�n���h��.wav");
	abrupt_steering_up_se_loop = abrupt_steering_up_se->CreateInstance();

	abrupt_steering_down_se      = make_unique<SoundEffect>(DXTK->AudioEngine, L"SE�}�n���h��.wav");
	abrupt_steering_down_se_loop = abrupt_steering_down_se->CreateInstance();

	engine_stop_se    = make_unique<SoundEffect>(DXTK->AudioEngine, L"SE�G���W����~��.wav");
	decision_sound_se = make_unique<SoundEffect>(DXTK->AudioEngine, L"SE���艹.wav");

	bgm      = make_unique<SoundEffect>(DXTK->AudioEngine, L"BGM����.wav");
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
	ResourceUpload.CreateDescriptorHeap(DXTK->PrimaryDevice, 6);//���\������摜�̐�
	ResourceUpload.ResourceUploadBegin(DXTK->PrimaryDevice);
	sprite_batch = ResourceUpload.CreateSpriteBatch();

	D3D12_VIEWPORT viewport = {
		0.0f, 0.0f,
		static_cast<float>(DXTK->ScreenWidth), static_cast<float>(DXTK->ScreenHeight),
		D3D12_MIN_DEPTH, D3D12_MAX_DEPTH
	};
	sprite_batch->SetViewport(viewport);

	sprite_main_screen        = ResourceUpload.CreateTexture(L"�Q�[���v���C���.png", 0);
	sprite_player             = ResourceUpload.CreateTexture(L"���@.png", 1);
	sprite_player_up          = ResourceUpload.CreateTexture(L"���@�΂ߏ�.png", 2);
	sprite_player_down        = ResourceUpload.CreateTexture(L"���@�΂߉�.png", 3);
	sprite_explanation_window = ResourceUpload.CreateTexture(L"�Q�[���������.png", 4);
	sprite_game_system_window = ResourceUpload.CreateTexture(L"�Q�[���V�X�e��.png", 5);

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
	//�t�F�[�h�C���I���܂ŃX�^�[�g���Ȃ��悤��start_flag�ŊǗ��� flase=��~ true=�J�n
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
		engine_se_loop->Play(true);
		//�Q�[�����������ʎ��̏�����
		if (description_state == 0) {
			if (!next_scene_flag) {
				//�Q�[���V�X�e��������ʂ�\�����遫
				if (DXTK->KeyEvent->pressed.Q) {
					decision_sound_se ->Play();
					description_state = 1;
				}
				//�^�C�g����ʂ֖߂遫
				if (DXTK->KeyEvent->pressed.E) {
					engine_stop_se  ->Play();
					next_scene_flag = true;
					next_scene      = NextScene::TitleScene;
					//�^�C�g����ʂ�
				}
			}
			else
			{
				//�t�F�[�h�A�E�g��
				elapsedTime += deltaTime;
				alpha -= (0.35f * deltaTime);
				if (elapsedTime >= 4.3f)
					return next_scene;
			}
		}//�Q�[���V�X�e�����������ʎ��̏�����
		else if (description_state == 1) {
			//�Q�[�����������ʂ֖߂遫
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
	//�ԁA�A�΁A�����x
	DXTK->DirectWrite->CreateTextFormat(
		L"�l�r �S�V�b�N", NULL, DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		50, // �T�C�Y
		L"ja-JP", &text_format
	);
	text_string = L"Q �Q�[���V�X�e���@�@�@�@�@�@    �@�@E �^�C�g����";
	text_rect = D2D1::RectF(35, 10, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	text_string = L"�Q�[���v���C���̑�����@";
	text_rect = D2D1::RectF(35, 60, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	text_string = L"�L�[�{�[�h: ��ւ̈ړ� W�L�[, ���ւ̈ړ� S�L�[";
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
	//�ԁA�A�΁A�����x
	DXTK->DirectWrite->CreateTextFormat(
		L"�l�r �S�V�b�N", NULL, DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		30, // �T�C�Y
		L"ja-JP", &text_format
	);
	text_string = L"�Q�[���V�X�e���̐���";
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
	//�ԁA�A�΁A�����x
	DXTK->DirectWrite->CreateTextFormat(
		L"�l�r �S�V�b�N", NULL, DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		30, // �T�C�Y
		L"ja-JP", &text_format
	);
	text_string = L"���@�@ = �X�R�A�A���C�t�B�G�ɏՓ˂��邱�ƂŌ���A0�ɂȂ�����Q�[���I�[�o�[�B";
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
	//�ԁA�A�΁A�����x
	DXTK->DirectWrite->CreateTextFormat(
		L"�l�r �S�V�b�N", NULL, DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		30, // �T�C�Y
		L"ja-JP", &text_format
	);
	text_string = L"�^�C�� = ���Ԍo�߂Ō����Ă����A�^�C����0�ɂȂ�����Q�[���N���A�B";
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
	//�ԁA�A�΁A�����x
	DXTK->DirectWrite->CreateTextFormat(
		L"�l�r �S�V�b�N", NULL, DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		30, // �T�C�Y
		L"ja-JP", &text_format
	);
	text_string = L"�G�@�@ = �p�g�J�[�A��ʎԁB������ƃp�g�J�[�̏ꍇ�͑����A��ʎԂ̏ꍇ�́�������B";
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
	//�ԁA�A�΁A�����x
	DXTK->DirectWrite->CreateTextFormat(
		L"�l�r �S�V�b�N", NULL, DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		30, // �T�C�Y
		L"ja-JP", &text_format
	);
	text_string = L"�G�ɓ����炸�ɔ���������Ή������A�v���C���[�̑��삪�����Ȃ�����A��b�Ō���";
	text_rect = D2D1::RectF(30, 130, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	text_string = L"�^�C����������B�X�s�[�h30�ȏ��2�b�A�X�s�[�h50�ȏ��3�b����悤�ɂȂ�B������";
	text_rect = D2D1::RectF(30, 160, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	text_string = L"����ƃX�s�[�h�������Ă����A�^�C����������B�^�C����55�b�𒴂���ƌ���̃p�g�J�[��";
	text_rect = D2D1::RectF(30, 190, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	text_string = L"�ڋ߂��Ă���B��莞�Ԃœ��H�𕕍����Ă���p�g�J�[���o������B���̃p�g�J�[�̏o��";
	text_rect = D2D1::RectF(30, 220, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	text_string = L"�ʒu�́y!!�z���\�����ꂽ�Ԑ��B���Ԃ��o�ĂΌo�قǓ��H�𕕍�����p�g�J�[��������B";
	text_rect = D2D1::RectF(30, 250, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);

	//---

	text_string = L"                                                                         Q �Ŗ߂�";
	text_rect = D2D1::RectF(30, 300, 1280, 720);
	DXTK->Direct2D->DrawText(
		text_string, lstrlenW(text_string),
		text_format.Get(), &text_rect, text_brush.Get()
	);
}