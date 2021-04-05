#include "../StdAfx.h"
#include "title.hpp"
int titleScene::hard = 1;
/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load any non-graphic
/// related content.  Calling base.Initialize will enumerate through any components
/// and initialize them as well.
/// </summary>
bool titleScene::Initialize()
{
	// TODO: Add your initialization logic here
	description = GraphicsDevice.CreateSpriteFromFile(_T("ゲーム説明画面背景.png"));
	description_letter = GraphicsDevice.CreateSpriteFromFile(_T("ゲーム説明画面文章.png"));
	title = GraphicsDevice.CreateSpriteFromFile(_T("title.png"));
	memo = GraphicsDevice.CreateSpriteFromFile(_T("操作説明.png"));
	bat = GraphicsDevice.CreateSpriteFromFile(_T("bat.png"));
	nomal = GraphicsDevice.CreateSpriteFromFile(_T("ノーマルタイトル画面.png"));
	hard_sp = GraphicsDevice.CreateSpriteFromFile(_T("ハードタイトル画面.png"));
	title_title = GraphicsDevice.CreateSpriteFromFile(_T("タイトルタイトル画面.png"));
	perfect_se = SoundDevice.CreateSoundFromFile(_T("perfect.wav"));
	txt = GraphicsDevice.CreateSpriteFont(_T("ContinueAL"), 75);
	smalltxt = GraphicsDevice.CreateSpriteFont(_T("ContinueAL"), 35);
	count = 0;
	flg = false;
	scene = 0;
	hit = 0;
	txt_x = 0;
	txt_y = -50;
	txt_x2 = -130;
	txt_y2 = 120;
	bat_x = 270;
	bat_y = 330;
	roll = 0;
	roll2 = 0;
	bat_roll = 0;
	se_flg = false;
	font = GraphicsDevice.CreateRenderTarget(1024, 256, PixelFormat_RGBA8888, DepthFormat_Unknown);
	font2 = GraphicsDevice.CreateRenderTarget(1024, 256, PixelFormat_RGBA8888, DepthFormat_Unknown);
	scale_x = 1;
	scale_y = 1;
	scale_x2 = 1;
	scale_y2 = 1;
	scale_x3 = 1;
	scale_y3 = 1;
	scale_x5 = 1;
	scale_y5 = 1;

	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void titleScene::Finalize()
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
int titleScene::Update()
{
    // TODO: Add your update logic here
	KeyboardBuffer Key_buf = Keyboard->GetBuffer();
	if (scene == 0) 
	{
		if (Key_buf.IsPressed(Keys_Up))
		{
			bat_y = 330;
		}

		if (Key_buf.IsPressed(Keys_Down))
		{
			bat_y = 500;
		}

		if (bat_y == 330)
		{
			if (Key_buf.IsPressed(Keys_Space))
			{
				if (se_flg == false)
				{
					se_flg = true;
					perfect_se->Play();
				}
				flg = true;
			}
			if (flg == true)
			{
				count++;
				txt_x += 10;
				txt_y -= 3;
				bat_roll = 90;
				roll += 0.5;
				scale_x += 0.1;
				scale_y += 0.1;
				scale_x2 -= 0.01;
				scale_y2 -= 0.01;
				scale_x3 -= 0.01;
				scale_y3 -= 0.01;
				scale_x5 -= 0.01;
				scale_y5 -= 0.01;
			}

			if (count >= 70) {
				scale_x2 = 0;
				scale_y2 = 0;
				scale_x3 = 0;
				scale_y3 = 0;
				scale_x5 = 0;
				scale_y5 = 0;
			}

			if (count >= 80)
			{
				titleScene::hard = 1;
				return GAME_SCENE(new GameMain);
			}
		}
		else if (bat_y == 500) {

			if (Key_buf.IsPressed(Keys_Space))
			{
				if (se_flg == false)
				{
					se_flg = true;
					perfect_se->Play();
				}
				flg = true;
			}
			if (flg == true)
			{
				count++;
				txt_x2 += 15;
				txt_y2 -= 5;
				bat_roll = 90;
				roll2 += 1;
				scale_x2 += 0.1;
				scale_y2 += 0.1;
				scale_x -= 0.01;
				scale_y -= 0.01;
				scale_x3 -= 0.01;
				scale_y3 -= 0.01;
				scale_x5 -= 0.01;
				scale_y5 -= 0.01;
			}

			if (count >= 70) {
				scale_x = 0;
				scale_y = 0;
				scale_x3 = 0;
				scale_y3 = 0;
				scale_x5 = 0;
				scale_y5 = 0;
			}

			if (count >= 80)
			{
				titleScene::hard = 2;
				return GAME_SCENE(new GameMain);
			}
		}

		if (Key_buf.IsPressed(Keys_Enter))
		{
			scene = 1;
		}
	}
	if (scene == 1)
	{
		if (Key_buf.IsPressed(Keys_Space))
		{
			scene = 0;
		}
	}
	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void titleScene::Draw()
{
	// TODO: Add your drawing code here

	GraphicsDevice.BeginScene();

	GraphicsDevice.Clear(Color_CornflowerBlue);

	SpriteBatch.Begin();
	if (scene == 1)
	{
		SpriteBatch.Draw(*description, Vector3(0, 0, 0));
		SpriteBatch.Draw(*description_letter, Vector3(0, 0, 0));
	}
	if (scene == 0)
	{
		SpriteBatch.Draw(*title, Vector3(0, 0, 0));
		SpriteBatch.Draw(*title_title, Vector3(0, 0, 0), 1.0f, Vector3(0, 0, 0), Vector3(640,300, 0), Vector2(scale_x3, scale_y3));
		SpriteBatch.Draw(*bat, Vector3(bat_x, bat_y, -10), 1.0f, Vector3(0, 0, bat_roll), Vector3(70, 73, 0), Vector2(scale_x5, scale_y5));

		SpriteBatch.Draw(*nomal, Vector3(txt_x, txt_y, 0), 1.0f, Vector3(0, 0, roll), Vector3(634,414, 0), Vector2(scale_x, scale_y));
		SpriteBatch.Draw(*hard_sp, Vector3(txt_x2, txt_y2, 0), 1.0f, Vector3(0, 0, roll2), Vector3(700,350, 0), Vector2(scale_x2, scale_y2));
	}

	SpriteBatch.End();

	GraphicsDevice.EndScene();
}
