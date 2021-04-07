#include "../StdAfx.h"
#include "clear.hpp"
#include "../GameMain.h"
/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load any non-graphic
/// related content.  Calling base.Initialize will enumerate through any components
/// and initialize them as well.
/// </summary>
bool clearScene::Initialize()
{
	// TODO: Add your initialization logic here
	GameMain::score;
	GameMain::perfect_;
	GameMain::good_;
	GameMain::miss_;
	player = GraphicsDevice.CreateSpriteFromFile(_T("ƒvƒŒƒCƒ„[ƒLƒƒƒ‰_20.png"));
	clear_ = GraphicsDevice.CreateSpriteFromFile(_T("clear.png"));

	a = GraphicsDevice.CreateSpriteFromFile(_T("A•]‰¿.png"));
	b = GraphicsDevice.CreateSpriteFromFile(_T("B•]‰¿.png"));
	c = GraphicsDevice.CreateSpriteFromFile(_T("C•]‰¿.png"));
	c.position = Vector3(1000, 380, -10);
	c.anchorPoint = Vector3(0, 200, 0);
	c.rotation.z = c_roll;
	c.scale = Vector3(b_big, b_big,0);

	txt = GraphicsDevice.CreateSpriteFont(_T("ContinueAL"), 50);
	bigtxt = GraphicsDevice.CreateSpriteFont(_T("ContinueAL"), 150);
	big_se = SoundDevice.CreateSoundFromFile(_T("bigw.wav"));
	small_se = SoundDevice.CreateSoundFromFile(_T("w.wav"));
	tin_se = SoundDevice.CreateSoundFromFile(_T("tin.wav"));

	ta_score = GraphicsDevice.CreateSpriteFromFile(_T("SCORE_.png"));
	bg = GraphicsDevice.CreateSpriteFromFile(_T("RESULT.png"));

	a_roll = 0;
	a_big = 4.6;
	b_big = 3;
	count = 0;
	c_roll = 0;

	clip_x = 0;
	bat_state = 0;
	second = 0;
	clip_x_max = 0;
	b_big2 = 3.5;
	score_state = 0;
	roll = 0;
	score_x = 850;
	score_y = 455;
	score_x2 = 900;
	score_y2 = 455;
	score_x3 = 950;
	score_y3 = 455;
	score_x4 = 1000;
	score_y4 = 455;
	score_x5 = 1050;
	score_y5 = 455;
	score_x6 = 440;
	score_y6 = 425;
	speed = 10;
	speed2 = 3;
	start_state = 0;
	b_big2 = 3;
	perfect_se = SoundDevice.CreateSoundFromFile(_T("perfect.wav"));
	if (GameMain::score >= 0 && GameMain::score < 300) tin_se->Play();
	if (GameMain::score >= 300 && GameMain::score < 1000)small_se->Play();
	if (GameMain::score >= 1000)big_se->Play();

	figure = GraphicsDevice.CreateSpriteFromFile(_T("0123456789.png"));
	figure_x = 50;

	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void clearScene::Finalize()
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
int clearScene::Update()
{
    // TODO: Add your update logic here

	KeyboardBuffer key_buf = Keyboard->GetBuffer();

	if (start_state == 0) {

		count++;
		if (count < 60)
		{
			a_big -= 0.06;
			a_roll += 6;
		}
		if (count >= 60)
		{
			a_roll = 0;
			a_big = 1;
		}
		if (b_big > 1)
		{
			b_big -= 0.05;
			b_big2 -= 0.05;
			b_big3 -= 0.05;
		}
		if (b_big <= 1)
		{
			b_big = 1;
			b_big2 = 1.5;
			b_big3 = 1;
		}
		if (count > 40)
		{
			c_roll = -35;
		}
		if (count >= 61) {
			start_state = 1;
		}
	}
	else if (start_state == 1) {

		if (key_buf.IsPressed(Keys_Enter))
		{
			bat_state = 1;
			start_state = 2;
			perfect_se->Play();
		}
	}
	else if(start_state == 2){

		if (bat_state == 1) {

			second += 1;

			if (second == 1) {
				clip_x += 350;
				clip_x_max += 1;
				second = 0;
			}

			if (clip_x_max == 10) {
				score_state = 1;
			}
			else if (clip_x_max == 19) {
				bat_state = 2;
			}
		}
		else if (bat_state == 2) {

			second += 1;

			if (second == 2) {
				clip_x -= 350;
				clip_x_max -= 1;
				second = 0;
			}

			if (clip_x_max == 2) {
				bat_state = 3;
			}
		}
		else if (bat_state == 3) {

			second += 1;

			if (second >= 200) {
				return GAME_SCENE(new titleScene);
				second = 0;
			}
		}

		if (score_state == 1) {
			b_big -= 0.002;
			b_big2 -= 0.006;
			b_big3 += 0.002;
			a_big -= 0.004;
			b_big -= 0.002;
			roll += 1;
			score_x += speed;
			score_y -= speed2;
			score_x2 += speed;
			score_y2 -= speed2;
			score_x3 += speed;
			score_y3 -= speed2;
			score_x4 += speed;
			score_y4 -= speed2;
			score_x5 += speed;
			score_y5 -= speed2;
			score_x6 += speed;
			score_y6 -= speed2;
		}
	}

	c.rotation.z = c_roll;
	c.scale = Vector3(b_big, b_big, 0);

	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void clearScene::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_CornflowerBlue);

	GraphicsDevice.BeginScene();
	SpriteBatch.Begin();

	int time_x;

	//score
	if (score_state == 0) {
		int ten_thousand = GameMain::score / 10000;
		time_x = (ten_thousand % 5) * figure_x;
		SpriteBatch.Draw(*figure, Vector3(score_x, score_y, -1.0f), RectWH(time_x, 0, figure_x, figure_x), 1.0f, Vector3(0, 0, roll), Vector3(50, 50, 0), Vector2(b_big, b_big));// –œ‚ÌˆÊ

		int fifteen_hundred = GameMain::score / 1000;
		time_x = (fifteen_hundred % 5) * figure_x;
		SpriteBatch.Draw(*figure, Vector3(score_x2, score_y2, -1.0f), RectWH(time_x, 0, figure_x, figure_x), 1.0f, Vector3(0, 0, roll), Vector3(50, 50, 0), Vector2(b_big, b_big));// ç‚ÌˆÊ

		int hundreds_place = GameMain::score / 100;
		time_x = (hundreds_place % 5) * figure_x;
		SpriteBatch.Draw(*figure, Vector3(score_x3, score_y3, -1.0f), RectWH(time_x, 0, figure_x, figure_x), 1.0f, Vector3(0, 0, roll), Vector3(50, 50, 0), Vector2(b_big, b_big));// •S‚ÌˆÊ

		int tens_place = GameMain::score / 10;
		time_x = (tens_place % 5) * figure_x;
		SpriteBatch.Draw(*figure, Vector3(score_x4, score_y4, -1.0f), RectWH(time_x, 0, figure_x, figure_x), 1.0f, Vector3(0, 0, roll), Vector3(50, 50, 0), Vector2(b_big, b_big));// \‚ÌˆÊ

		int ones_place = GameMain::score % 10;
		time_x = (ones_place % 5) * figure_x;
		SpriteBatch.Draw(*figure, Vector3(score_x5, score_y5, -1.0f), RectWH(time_x, 0, figure_x, figure_x), 1.0f, Vector3(0, 0, roll), Vector3(50, 50, 0), Vector2(b_big, b_big));// ˆê‚ÌˆÊ
	}
	else if (score_state == 1) {

		int ten_thousand = GameMain::score / 10000;
		time_x = (ten_thousand % 5) * figure_x;
		SpriteBatch.Draw(*figure, Vector3(score_x, score_y, -1.0f), RectWH(time_x, 0, figure_x, figure_x), 1.0f, Vector3(0, 0, roll), Vector3(50, 50, 0), Vector2(b_big3, b_big3));// –œ‚ÌˆÊ

		int fifteen_hundred = GameMain::score / 1000;
		time_x = (fifteen_hundred % 5) * figure_x;
		SpriteBatch.Draw(*figure, Vector3(score_x2, score_y2, -1.0f), RectWH(time_x, 0, figure_x, figure_x), 1.0f, Vector3(0, 0, roll), Vector3(50, 50, 0), Vector2(b_big3, b_big3));// ç‚ÌˆÊ

		int hundreds_place = GameMain::score / 100;
		time_x = (hundreds_place % 5) * figure_x;
		SpriteBatch.Draw(*figure, Vector3(score_x3, score_y3, -1.0f), RectWH(time_x, 0, figure_x, figure_x), 1.0f, Vector3(0, 0, roll), Vector3(50, 50, 0), Vector2(b_big3, b_big3));// •S‚ÌˆÊ

		int tens_place = GameMain::score / 10;
		time_x = (tens_place % 5) * figure_x;
		SpriteBatch.Draw(*figure, Vector3(score_x4, score_y4, -1.0f), RectWH(time_x, 0, figure_x, figure_x), 1.0f, Vector3(0, 0, roll), Vector3(50, 50, 0), Vector2(b_big3, b_big3));// \‚ÌˆÊ
	
		int ones_place = GameMain::score % 10;
		time_x = (ones_place % 5) * figure_x;
		SpriteBatch.Draw(*figure, Vector3(score_x5, score_y5, -1.0f), RectWH(time_x, 0, figure_x, figure_x), 1.0f, Vector3(0, 0, roll), Vector3(50, 50, 0), Vector2(b_big3, b_big3));// ˆê‚ÌˆÊ
	}


	
	//perfect_
	int time_x2;
	int tens_place2 = GameMain::perfect_ / 10;
	time_x2 = (tens_place2 % 5) * figure_x;
	SpriteBatch.Draw(*figure, Vector3(450.0f, 95.0f, -1.0f), RectWH(time_x2, 0, figure_x, figure_x), 1.0f, Vector3(0, 0, 0), Vector3(50, 50, 0), Vector2(b_big, b_big));// \‚ÌˆÊ

	int ones_place2 = GameMain::perfect_ % 10;
	time_x2 = (ones_place2 % 5) * figure_x;
	SpriteBatch.Draw(*figure, Vector3(500.0f, 95.0f, -1.0f), RectWH(time_x2, 0, figure_x, figure_x), 1.0f, Vector3(0, 0, 0), Vector3(50, 50, 0), Vector2(b_big, b_big));// ˆê‚ÌˆÊ


	//good_
	int time_x3;
	int tens_place3 = GameMain::good_ / 10;
	time_x3 = (tens_place3 % 5) * figure_x;
	SpriteBatch.Draw(*figure, Vector3(400.0f, 190.0f, -1.0f), RectWH(time_x3, 0, figure_x, figure_x), 1.0f, Vector3(0, 0, 0), Vector3(50, 50, 0), Vector2(b_big, b_big));// \‚ÌˆÊ

	int ones_place3 = GameMain::good_ % 10;
	time_x3 = (ones_place3 % 5) * figure_x;
	SpriteBatch.Draw(*figure, Vector3(450.0f, 190.0f, -1.0f), RectWH(time_x3, 0, figure_x, figure_x), 1.0f, Vector3(0, 0, 0), Vector3(50, 50, 0), Vector2(b_big, b_big));// ˆê‚ÌˆÊ


	//miss_
	int time_x4;
	int tens_place4 = GameMain::miss_ / 10;
	time_x4 = (tens_place4 % 5) * figure_x;
	SpriteBatch.Draw(*figure, Vector3(400.0f, 290.0f, -1.0f), RectWH(time_x4, 0, figure_x, figure_x), 1.0f, Vector3(0, 0, 0), Vector3(50, 50, 0), Vector2(b_big, b_big));// \‚ÌˆÊ

	int ones_place4 = GameMain::miss_ % 10;
	time_x4 = (ones_place4 % 5) * figure_x;
	SpriteBatch.Draw(*figure, Vector3(450.0f, 290.0f, -1.0f), RectWH(time_x4, 0, figure_x, figure_x), 1.0f, Vector3(0, 0, 0), Vector3(50, 50, 0), Vector2(b_big, b_big));// ˆê‚ÌˆÊ



	if (GameMain::score >= 0 && GameMain::score < 300)SpriteBatch.Draw(c);
	if (GameMain::score >= 300 && GameMain::score < 1000)SpriteBatch.Draw(*b, Vector3(950,150, -10), 1.0f, Vector3(0, 0, 0), Vector3(65, 100, 0), Vector2(b_big, b_big));
	if (GameMain::score >= 1000)SpriteBatch.Draw(*a, Vector3(950,150,-10), 1.0f, Vector3(0, 0, a_roll), Vector3(110, 110, 0), Vector2(a_big, a_big));
	SpriteBatch.Draw(*player, Vector3(70, 300, 0), RectWH(clip_x, 0, 350, 300),1.0f, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector2(b_big2, b_big2));
	if (score_state == 0) {
		SpriteBatch.Draw(*ta_score, Vector3(score_x6, score_y6, 0), 1.0f, Vector3(0, 0, roll), Vector3(372, 56, 0), Vector2(b_big, b_big));
	}
	else if (score_state == 1) {
		SpriteBatch.Draw(*ta_score, Vector3(score_x6, score_y6, 0), 1.0f, Vector3(0, 0, roll), Vector3(372, 56, 0), Vector2(b_big3, b_big3));
	}
	SpriteBatch.Draw(*bg, Vector3(0, 0, 10), 1.0f, Vector3(0, 0, 0), Vector3(640,360, 0), Vector2(b_big, b_big));

	SpriteBatch.End();

	GraphicsDevice.EndScene();
}
