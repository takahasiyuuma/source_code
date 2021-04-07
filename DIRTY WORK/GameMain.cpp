// #include "Extension\DirectX11\DXGraphics11.hpp"
#include "StdAfx.h"
#include "GameMain.h"

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load all of your content.
/// Initialize will enumerate through any components and initialize them as well.
/// </summary>
bool GameMain::Initialize()
{
	// TODO: Add your initialization logic here
	WindowTitle(_T("ES Game Library"));

	//ゲームパッド初期化
	InputDevice.CreateGamePad(1);

	ゲームプレイ背景 = GraphicsDevice.CreateSpriteFromFile(_T("ゲームプレイ画面.png"));
	スタート背景 = GraphicsDevice.CreateSpriteFromFile(_T("スタート画面.png"));
	クリア背景 = GraphicsDevice.CreateSpriteFromFile(_T("クリア画面.png"));
	ゲームオーバー背景 = GraphicsDevice.CreateSpriteFromFile(_T("ゲームオーバー画面.png"));
	難易度設定背景 = GraphicsDevice.CreateSpriteFromFile(_T("難易度設定画面.png"));
	ゲームシステム背景 = GraphicsDevice.CreateSpriteFromFile(_T("ゲームシステム.png"));
	ゲーム操作説明背景 = GraphicsDevice.CreateSpriteFromFile(_T("ゲーム操作説明.png"));
	プレイヤー = GraphicsDevice.CreateSpriteFromFile(_T("自機.png"));
	プレイヤー上 = GraphicsDevice.CreateSpriteFromFile(_T("自機斜め1.png"));
	プレイヤー下 = GraphicsDevice.CreateSpriteFromFile(_T("自機斜め2.png"));
	赤車 = GraphicsDevice.CreateSpriteFromFile(_T("赤車.png"));
	青車 = GraphicsDevice.CreateSpriteFromFile(_T("青車.png"));
	壁パトカー = GraphicsDevice.CreateSpriteFromFile(_T("パトカー斜め.png"));
	歩行者 = GraphicsDevice.CreateSpriteFromFile(_T("歩行者.png"));
	歩行者2 = GraphicsDevice.CreateSpriteFromFile(_T("歩行者2.png"));
	追跡パトカー = GraphicsDevice.CreateSpriteFromFile(_T("パトカー.png"));
	衝突エフェクト = GraphicsDevice.CreateSpriteFromFile(_T("車衝突エフェクト.png"));
	＄袋 = GraphicsDevice.CreateSpriteFromFile(_T("＄袋.png"));
	＄袋2 = GraphicsDevice.CreateSpriteFromFile(_T("＄袋.png"));
	金額枠 = GraphicsDevice.CreateSpriteFromFile(_T("金額枠.png"));
	タイム枠 = GraphicsDevice.CreateSpriteFromFile(_T("タイム枠.png"));
	EXタイム枠 = GraphicsDevice.CreateSpriteFromFile(_T("EXタイム枠.png"));
	危険 = GraphicsDevice.CreateSpriteFromFile(_T("危険.png"));
	プレイヤー2 = GraphicsDevice.CreateSpriteFromFile(_T("自機2.png"));
	クリア画面金額枠 = GraphicsDevice.CreateSpriteFromFile(_T("クリア画面金額枠"));
	/*フォントスタート = GraphicsDevice.CreateSpriteFont(_T("MSゴシック"), 150);*/
	フォント = GraphicsDevice.CreateSpriteFont(_T("MSゴシック"), 50);
	フォント2 = GraphicsDevice.CreateSpriteFont(_T("MSゴシック"), 50);
	フォント3 = GraphicsDevice.CreateSpriteFont(_T("MSゴシック"), 50);
	フォント4 = GraphicsDevice.CreateSpriteFont(_T("MSゴシック"), 50);
	フォント操作説明 = GraphicsDevice.CreateSpriteFont(_T("MSゴシック"), 30);
	注意フォント = GraphicsDevice.CreateSpriteFont(_T("けいふぉんと"), 100);

	ゲームプレイBGM = SoundDevice.CreateMusicFromFile(_T("メインBGM.wav"));

	衝突SE = SoundDevice.CreateSoundFromFile(_T("衝突SE.wav"));
	走行中SE = SoundDevice.CreateSoundFromFile(_T("走行中SE.wav"));
	エンジン起動SE = SoundDevice.CreateSoundFromFile(_T("エンジンをかける.wav"));
	通過SE = SoundDevice.CreateSoundFromFile(_T("通過SE.wav"));
	上下移動SE = SoundDevice.CreateSoundFromFile(_T("上下移動ブレーキSE.wav"));
	上下移動SE2 = SoundDevice.CreateSoundFromFile(_T("上下移動ブレーキSE.wav"));
	事故SE = SoundDevice.CreateSoundFromFile(_T("ゲームオーバー事故SE.wav"));
	シャッターSE = SoundDevice.CreateSoundFromFile(_T("シャッターSE.wav"));
	
	サイレンSE = SoundDevice.CreateSoundFromFile(_T("サイレンSE.wav"),true);
    サイレンSE3D = サイレンSE->GetSound3D();
	サイレンSE2 = SoundDevice.CreateSoundFromFile(_T("サイレンSE.wav"), true);
	サイレンSE3D2 = サイレンSE2->GetSound3D();
	サイレンSE3 = SoundDevice.CreateSoundFromFile(_T("サイレンSE.wav"));


	注意Color = Color(255, 255, 255, 0);
	点滅_flag = true;
	点滅 = 0;
	背景_x = 0.0f;
	画面_state = 0;
	無敵_state = 0;
	無敵 = 0;
	無敵2 = 0;
	プレイヤー_x = 500;
    プレイヤー_y = 370;
	スピード_x = 0;
	スピード_y = 0;
	赤車_x = 1300;
	赤車_y = 0;
	青車_x = 500;
	青車_y = 500;
	追跡パトカー_x = 100;
	追跡パトカー_y = 500;
	歩行者_x = 1100;
	歩行者_y = 280;
	歩行者2_x = 400;
	歩行者2_y = 280;
	一秒 = 0;
	タイム秒 = 60;
	逃走タイム秒 = 0;
	逃走タイム秒2 = 0;
	逃走タイム秒3 = 0;
	ハード逃走タイム秒3 = 0;
	逃走タイム_state = 0;
	スコア = 100000000;
	スコア2 = 0;
	スコア3 = 0;
	ハイスコア = 0;
	ハードハイスコア = 0;
	衝突_state = 0;
	衝突表示時間 = 0;
	衝突表示時間2 = 0;
	スピード加速 = 1;
	スピード加速秒 = 0;
	スピード加速秒2 = 0;
	＄袋_x = 0;
	＄袋_y = 0;
	＄袋_state = 0;
	＄袋2_x = 0;
	＄袋2_y = 0;
	＄袋2_state = 0;
	追跡_state = 0;
	プレイヤー_state = 0;
	プレイヤー向き_state = 0;
	逮捕_state = 0;
	逮捕 = 0;
	逮捕2 = 0;
	逃走_state = 0;
	逃走 = 0;
	逃走2 = 0;
	パトカー壁秒数 = 0;
	パトカー壁秒数2 = 0;
	パトカー壁_state = 0;
	パトカー壁ランダム = 0;
	壁パトカー_x = 1200;
	壁パトカー2_x = 1200;
	壁パトカー3_x = 1200;
	壁パトカー4_x = 1200;
	壁パトカー_y = 335;
	壁パトカー2_y = 435;
	壁パトカー3_y = 535;
	壁パトカー4_y = 635;
	ゲームモード設定_state = 0;
	EXモード秒 = 0;
	EXモード秒2 = 0;
	EXモード秒3 = 0;
	説明_state = 0;
	衝突エフェクト_x = 0;
	衝突 = 0;
	衝突2 = 0;
	スピード_state = 0;
	スピードタイム = 0;
	プレイヤー描画_x = 0;
	プレイヤー描画_state = 0;

	//初期値　　　　　　　　　　　　　　　 //範囲
	/*プレイヤー_collision = Rect(プレイヤー_x + 15, プレイヤー_y + 25, プレイヤー_x + 120, プレイヤー_y + 65);
	赤車_collision = Rect(赤車_x + 5, 赤車_y + 10, 赤車_x + 105, 赤車_y + 80);
	青車_collision = Rect(青車_x + 5, 青車_y + 10, 青車_x + 105, 青車_y + 80);
	壁パトカー_collision = Rect(壁パトカー_x + 10, 壁パトカー_y + 15, 壁パトカー_x + 100, 壁パトカー_y + 80);
	壁パトカー2_collision = Rect(壁パトカー2_x + 10, 壁パトカー2_y + 15, 壁パトカー2_x + 100, 壁パトカー2_y + 80);
	壁パトカー3_collision = Rect(壁パトカー3_x + 10, 壁パトカー3_y + 15, 壁パトカー3_x + 100, 壁パトカー3_y + 80);
	壁パトカー4_collision = Rect(壁パトカー4_x + 10, 壁パトカー4_y + 15, 壁パトカー4_x + 100, 壁パトカー4_y + 80);*/

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

/// <summary>
/// Allows the game to run logic such as updating the world,
/// checking for collisions, gathering input, and playing audio.
/// </summary>
/// <returns>
/// Scene continued value.
/// </returns>
int GameMain::Update()
{
	// TODO: Add your update logic here

	//共通処理

	//キーボード
	Keystate = Keyboard->GetState();
	Key_buffer = Keyboard->GetBuffer();

	//ゲームパッド
	pad = GamePad(0)->GetState();
	pad_buffer = GamePad(0)->GetBuffer();

	サイレンSE3D->SetPosition((追跡パトカー_x - 640) / 256, 0, 0); 128;

	if (パトカー壁ランダム == 0) {
		サイレンSE3D2->SetPosition((壁パトカー_x - 640) / 256, 0, 0); 128;
	}
	else if(パトカー壁ランダム == 1){
		サイレンSE3D2->SetPosition((壁パトカー_x - 640) / 256, 0, 0); 128;
	}
	else if (パトカー壁ランダム == 2) {
		サイレンSE3D2->SetPosition((壁パトカー2_x - 640) / 256, 0, 0); 128;
	}
	else if (パトカー壁ランダム == 3) {
		サイレンSE3D2->SetPosition((壁パトカー3_x - 640) / 256, 0, 0); 128;
	}
	else if (パトカー壁ランダム == 4) {
		サイレンSE3D2->SetPosition((壁パトカー4_x - 640) / 256, 0, 0); 128;
	}

	//ここまで

	if (画面_state == タイトル画面) {
		タイトル初期化();
		タイトル処理();
	}
	else if (画面_state == メイン画面) {
		メイン処理();
		プレイヤー処理();
		エネミー処理();
		壁エネミー処理();
		当たり判定処理();
	}
	else if (画面_state == 説明画面) {
		操作説明処理();
	}
    else if (画面_state == ゲームオーバー画面) {
		ゲームオーバー処理();
	}
	else if (画面_state == ゲームクリア画面) {
		ゲームクリア処理();
	}
	else if (画面_state == 難易度設定画面) {
		難易度設定処理();
	}

	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void GameMain::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_CornflowerBlue);

	GraphicsDevice.BeginScene();


	SpriteBatch.Begin();

	//タイトル画面
	if (画面_state == 0) {
	タイトル描画();
	}
	//ゲームプレイ
	else if (画面_state == 1) {
	メイン描画();
	壁エネミー描画();
	}
	//操作方法確認画面
	else if (画面_state == 2) {
	操作説明描画();
	}
	//ゲームオーバー画面
	else if (画面_state == 3) {
	ゲームオーバー描画();
	}
	//ゲームクリア画面
	else if (画面_state == 4) {
	ゲームクリア描画();
	}
	//ショップ画面
	else if (画面_state == 5) {
	難易度設定描画();
	}

	SpriteBatch.End();

	GraphicsDevice.EndScene();

	Canvas canvas = GraphicsDevice.LockCanvas();

	Paint paint;

	paint.SetPaintColor(Color_Blue);
	canvas.DrawRect(プレイヤー_collision, paint);

	paint.SetPaintColor(Color_Yellow);
	canvas.DrawRect(赤車_collision, paint);

	paint.SetPaintColor(Color_Yellow);
	canvas.DrawRect(青車_collision, paint);

	paint.SetPaintColor(Color_Red);
	canvas.DrawRect(壁パトカー_collision, paint);

	paint.SetPaintColor(Color_Red);
	canvas.DrawRect(壁パトカー2_collision, paint);

	paint.SetPaintColor(Color_Red);
	canvas.DrawRect(壁パトカー3_collision, paint);

	paint.SetPaintColor(Color_Red);
	canvas.DrawRect(壁パトカー4_collision, paint);

	GraphicsDevice.UnlockCanvas();
}

void GameMain::タイトル初期化() {

	無敵_state = 0;
	無敵 = 0;
	無敵2 = 0;
	プレイヤー_x = 500;
	プレイヤー_y = 500;
	赤車_x = 1300;
	赤車_y = 385;
	青車_x = 500;
	青車_y = 650;
	追跡パトカー_x = 100;
	追跡パトカー_y = 500;
	歩行者_x = 1100;
	歩行者_y = 220;
	歩行者2_x = 300;
	歩行者2_y = 220;
	一秒 = 0;

	if (ゲームモード設定_state == 0) {
		タイム秒 = 60;
	}
	else if (ゲームモード設定_state == 1) {
		タイム秒 = 120;
	}

	逃走タイム秒 = 0;
	逃走タイム秒2 = 0;
	衝突_state = 0;
	衝突表示時間 = 0;
	衝突表示時間2 = 0;
	スピード加速 = 1;
	スピード加速秒 = 0;
	スピード加速秒2 = 0;
	＄袋_x = 0;
	＄袋_y = 0;
	＄袋_state = 0;
	＄袋2_x = 0;
	＄袋2_y = 0;
	＄袋2_state = 0;
	追跡_state = 0;
	プレイヤー_state = 0;
	プレイヤー向き_state = 0;
	逮捕_state = 0;
	逮捕 = 0;
	逮捕2 = 0;
	逃走_state = 0;
	逃走 = 0;
	逃走2 = 0;
	パトカー壁秒数 = 0;
	パトカー壁秒数2 = 0;
	パトカー壁_state = 0;
	パトカー壁ランダム = 0;
	壁パトカー_x = 1200;
	壁パトカー2_x = 1200;
	壁パトカー3_x = 1200;
	壁パトカー4_x = 1200;
	壁パトカー_y = 335;
	壁パトカー2_y = 435;
	壁パトカー3_y = 535;
	壁パトカー4_y = 635;
	スピード_state = 0;
	スピードタイム = 0;
	注意Color = Color(255, 255, 255, 0);
	点滅_flag = true;
	点滅 = 0;
	説明_state = 0;
	衝突エフェクト_x = 0;
	衝突 = 0;
	衝突2 = 0;
	EXモード秒 = 0;
	EXモード秒2 = 0;
	プレイヤー描画_x = 140;
	プレイヤー描画_state = 0;
	ゲームプレイBGM->Stop();
	サイレンSE->Stop();
	サイレンSE2->Stop();
	サイレンSE3->Stop();
	走行中SE->Stop();
	衝突SE->Stop();
	通過SE->Stop();
	事故SE->Stop();
	シャッターSE->Stop();
	上下移動SE->Stop();
	上下移動SE2->Stop();
}

void GameMain::タイトル処理() {

	if (Key_buffer.IsPressed(Keys_E) || pad_buffer.IsPressed(DIJOFS_BUTTON7)) {
		画面_state = 1;
		スコア = 100000000;
		スコア2 = 0;
		スコア3 = 0;
		エンジン起動SE->Play();
	}
	if (Key_buffer.IsPressed(Keys_Q) || pad_buffer.IsPressed(DIJOFS_BUTTON6)) {
		画面_state = 2;
		エンジン起動SE->Play();
	}

	if (Key_buffer.IsPressed(Keys_F) || pad_buffer.IsPressed(DIJOFS_BUTTON1)) {
		画面_state = 5;
	}

	//クリア画面へ　デバック
	/*if (Key_buffer.IsPressed(Keys_U) || pad_buffer.IsPressed(DIJOFS_BUTTON1)) {
		画面_state = 4;
		スコア2 = 100000000;
	}*/
}

void GameMain::タイトル描画() {

	SpriteBatch.Draw(*スタート背景, Vector3(0.0f, 0.0f, 0.0f));
	/*SpriteBatch.DrawString(フォントスタート, Vector2(20, 10), Color(148, 0, 211), _T("dirty work"));*/
	SpriteBatch.DrawString(フォント, Vector2(650, 660), Color(0, 255, 0), _T("Q このゲームの説明"));
	if (ゲームモード設定_state == 0) {
		SpriteBatch.DrawString(フォント2, Vector2(650, 560), Color(255, 0, 0), _T("最短逃走成功タイム：%d秒"), 逃走タイム秒3);
		SpriteBatch.DrawString(フォント, Vector2(650, 510), Color(255, 255, 0), _T("最大取得金額：%d＄"), ハイスコア);
	}
	else if (ゲームモード設定_state == 1) {
		SpriteBatch.DrawString(フォント2, Vector2(650, 560), Color(255, 0, 0), _T("最短逃走成功タイム：%d秒"), ハード逃走タイム秒3);
		SpriteBatch.DrawString(フォント, Vector2(650, 510), Color(255, 255, 0), _T("最大取得金額：%d＄"),ハードハイスコア);
	}
	else if (ゲームモード設定_state == 2) {
		SpriteBatch.DrawString(フォント2, Vector2(650, 560), Color(0, 0, 255), _T("最長逃走タイム：%d秒"), EXモード秒3);
	}
	SpriteBatch.DrawString(フォント3, Vector2(650, 610), Color(0, 200, 200), _T("F 難易度設定"));
	SpriteBatch.DrawString(フォント, Vector2(130, 270), Color(0, 255, 255), _T("E ゲームスタート"));

	if (ゲームモード設定_state == 0) {
		SpriteBatch.DrawString(フォント, Vector2(10, 10), Color(255, 0, 255), _T("ノーマルモード"));
	}
	else if (ゲームモード設定_state == 1) {
		SpriteBatch.DrawString(フォント, Vector2(10,10), Color(255, 0, 255), _T("ハードモード"));
	}
	else if (ゲームモード設定_state == 2) {
		SpriteBatch.DrawString(フォント, Vector2(10, 10), Color(255, 0, 255), _T("EXモード"));
	}
}

void GameMain::メイン処理() {

		//当たり判定の確認
		/*プレイヤー_collision = Rect(プレイヤー_x + 15, プレイヤー_y + 25, プレイヤー_x + 120, プレイヤー_y + 65);
		赤車_collision = Rect(赤車_x + 5, 赤車_y + 10, 赤車_x + 105, 赤車_y + 80);
		青車_collision = Rect(青車_x + 5, 青車_y + 10, 青車_x + 105, 青車_y + 80);
		壁パトカー_collision = Rect(壁パトカー_x + 10, 壁パトカー_y + 15, 壁パトカー_x + 100, 壁パトカー_y + 80);
		壁パトカー2_collision = Rect(壁パトカー2_x + 10, 壁パトカー2_y + 15, 壁パトカー2_x + 100, 壁パトカー2_y + 80);
		壁パトカー3_collision = Rect(壁パトカー3_x + 10, 壁パトカー3_y + 15, 壁パトカー3_x + 100, 壁パトカー3_y + 80);
		壁パトカー4_collision = Rect(壁パトカー4_x + 10, 壁パトカー4_y + 15, 壁パトカー4_x + 100, 壁パトカー4_y + 80);*/

		if (!ゲームプレイBGM->IsPlaying())
			ゲームプレイBGM->Play();

		if (!サイレンSE->IsPlaying())
			サイレンSE->Play();

		if (!サイレンSE2->IsPlaying())
			サイレンSE2->Play();

		if (!走行中SE->IsPlaying())
			走行中SE->Play();

		if (プレイヤー_x <= 赤車_x) {
			if (!通過SE->IsPlaying())
				通過SE->Play();
		}

		if (プレイヤー_x <= 青車_x) {
			if (!通過SE->IsPlaying())
				通過SE->Play();
		}


		背景_x = 背景_x - 38 - (スピード加速 / 100);
		if (背景_x <= -2720.0f) {
			背景_x = 0.0f;
		}

		if (ゲームモード設定_state == 0 || ゲームモード設定_state == 1) {

			if (逮捕_state == 0) {
				一秒 += 1;
				スコア2 = スコア;
				スコア3 = スコア2;

				//ゲームオーバー
				if (スコア < 0) {
					スコア = 0;
					画面_state = 3;
				}

				if (プレイヤー描画_state == 0) {

					プレイヤー描画_x = 1;

					if (一秒 == 1) {
						プレイヤー描画_state = 1;
					}
				}
				else if (プレイヤー描画_state == 1) {

					プレイヤー描画_x = 140;

					if (一秒 == 1) {
						プレイヤー描画_state = 0;
					}
				}

				if (一秒 == 60) {

					タイム秒 -= スピードタイム;
					一秒 = 0;

					if (スピード加速 == 0) {
						スピード_state = 0;
					}
					else if (スピード加速 == 20) {
						スピード_state = 1;
					}
					else if (スピード加速 == 50) {
						スピード_state = 2;
					}
				}

				if (スピード_state == 0) {
					スピードタイム = 1;
				}
				else if (スピード_state == 1) {
					スピードタイム = 2;
				}
				else if (スピード_state == 2) {
					スピードタイム = 3;
				}

				//クリア条件
				if (タイム秒 <= -1) {
					プレイヤー_state = 2;
					逃走_state = 1;
				}
			}

			逃走タイム秒 += 1;

			if (逃走タイム秒 == 60) {
				逃走タイム秒2 += 1;
				逃走タイム秒 = 0;
			}
		}
		else if (ゲームモード設定_state == 2) {
			EXモード秒 += 1;

			if (EXモード秒 == 60) {
				EXモード秒2 += 1;
				EXモード秒 = 0;
			}

			if (スコア < 0) {
				スコア = 0;
				画面_state = 3;
			}
		}

		if (プレイヤー_state == 2) {

			if (逃走_state == 1) {

				逃走 += 1;

				プレイヤー_x = プレイヤー_x + 10;
				プレイヤー向き_state = 0;

				if (逃走 == 60) {
					逃走2 += 1;
					逃走 = 0;
				}

				if (逃走2 == 2) {
					画面_state = 4;
				}
			}
		}

		if (ゲームモード設定_state == 0) {

			if (タイム秒 > 65) {
				タイム秒 = 65;
			}
		}
		else if (ゲームモード設定_state == 1) {

			if (タイム秒 > 125) {
				タイム秒 = 125;
			}
		}

		if (点滅_flag == true && 点滅 >= 255)
		{
			点滅_flag = false;
		}

		if (点滅_flag == false && 点滅 <= 0)
		{
			点滅_flag = true;
		}

		if (点滅_flag)
		{
			点滅 += 5;
		}
		else
		{
			点滅 -= 5;
		}
	}

void GameMain::プレイヤー処理() {

	if (プレイヤー_state == 0) {

		if (Keystate.IsKeyDown(Keys_W) || pad.Buttons[3] != 0) {
			スピード_y = スピード_y - 0.2 - (スピード加速 / 1000);

			if (スピード_y < -5) {
				スピード_y = -5;
			}

			if (!上下移動SE->IsPlaying())
				上下移動SE->Play();

			プレイヤー向き_state = 1;
		}

		if (Keystate.IsKeyDown(Keys_S) || pad.Buttons[0] != 0) {
			スピード_y = スピード_y + 0.2 + (スピード加速 / 1000);

			if (スピード_y > 5) {
				スピード_y = 5;
			}

			if (!上下移動SE2->IsPlaying())
				上下移動SE2->Play();

			プレイヤー向き_state = 2;
		}

		if (Keystate.IsKeyUp(Keys_W) && pad.Buttons[0] == 0 && Keystate.IsKeyUp(Keys_S) && pad.Buttons[3] == 0) {
			if (スピード_y > 0) {
				スピード_y = スピード_y - 0.1;
			}

			if (スピード_y < 0) {
				スピード_y = スピード_y + 0.1;
			}

			プレイヤー向き_state = 0;
		}

		if (プレイヤー_y > 295) {

			スピード加速秒 = スピード加速秒 + 1.0f;

			if (スピード加速秒 == 30) {
				スピード加速 = スピード加速 + 1;
				スピード加速秒 = 0;
			}
		}
		else if (プレイヤー_y < 295) {

			スピード加速秒2 = スピード加速秒2 + 2.0f;

			if (スピード加速秒2 == 30) {
				スピード加速 = スピード加速 - 1;
				スピード加速秒2 = 0;
			}
		}

		if (スピード加速 < -10) {
			スピード加速 = -10;
		}

		プレイヤー_x = プレイヤー_x + スピード_x;
		プレイヤー_y = プレイヤー_y + スピード_y;

		if (プレイヤー_x > 1000) {
			プレイヤー_x = 1000;
		}

		if (プレイヤー_x < 0) {
			プレイヤー_x = 0;
		}

		if (プレイヤー_y < 245) {
			プレイヤー_y = 245;
			プレイヤー向き_state = 0;
		}

		if (プレイヤー_y > 650) {
			プレイヤー_y = 650;
			プレイヤー向き_state = 0;
		}
	}
}

void GameMain::エネミー処理() {

		赤車_x = 赤車_x - MathHelper_Random(10, 20) - (スピード加速 / 100);
		if (赤車_x <= -130.0f) {
			赤車_x = 1300;
			MathHelper_Random(330, 650);
		}

		青車_x = 青車_x - MathHelper_Random(10, 20) - (スピード加速 / 100);
		if (青車_x <= -130.0f) {
			青車_x = 1300;
			青車_y = MathHelper_Random(330, 650);
		}

		歩行者_x = 歩行者_x - 8 - (スピード加速 / 100);
		if (歩行者_x <= -130.0f) {
			歩行者_x = 1300;
			歩行者_y = MathHelper_Random(245, 250);
		}

		歩行者2_x = 歩行者2_x - 8 - (スピード加速 / 100);
		if (歩行者2_x <= -130.0f) {
			歩行者2_x = 1300;
			歩行者2_y = MathHelper_Random(245, 250);
		}

		if (追跡パトカー_y < プレイヤー_y) {
			追跡パトカー_y = 追跡パトカー_y + 1;

			if (追跡パトカー_y == プレイヤー_y) {
				追跡パトカー_y = プレイヤー_y;
			}
		}
		else if (追跡パトカー_y > プレイヤー_y) {
			追跡パトカー_y = 追跡パトカー_y - 1;

			if (追跡パトカー_y == プレイヤー_y) {
				追跡パトカー_y = プレイヤー_y;
			}
		}

		if (ゲームモード設定_state == 0) {

			if (タイム秒 > 55) {
				追跡_state = 1;
			}
			else if (タイム秒 < 55) {
				追跡_state = 2;
			}
		}
		else if (ゲームモード設定_state == 1) {

			if (タイム秒 > 115) {
				追跡_state = 1;
			}
			else if (タイム秒 < 115) {
				追跡_state = 2;
			}
		}

		if (追跡_state == 1) {
			追跡パトカー_x = 追跡パトカー_x + 0.1;
		}
		else if (追跡_state == 2) {
			追跡パトカー_x = 追跡パトカー_x - 0.01;
		}

		if (追跡パトカー_y < プレイヤー_x) {
			if (追跡パトカー_y > 650) {
				追跡パトカー_y = 650;
			}

			if (追跡パトカー_y < 295) {
				追跡パトカー_y = 295;
			}
		}
		else if (追跡パトカー_y > プレイヤー_x) {
			if (追跡パトカー_y > 650) {
				追跡パトカー_y = 650;
			}
		}
	}

void GameMain::壁エネミー処理() {

	if (逃走_state == 0) {

		パトカー壁秒数 += 1;

		if (パトカー壁秒数 == 60) {
			パトカー壁秒数 = 0;
			パトカー壁秒数2 += 1;
		}
		else if (パトカー壁秒数2 == 1) {
			パトカー壁ランダム = MathHelper_Random(1, 4);
		}
		else if (パトカー壁秒数2 == 3) {
			パトカー壁_state = 1;
			壁パトカー_x = 1200;
			壁パトカー2_x = 1200;
			壁パトカー3_x = 1200;
			壁パトカー4_x = 1200;
			壁パトカー_y = 335;
			壁パトカー2_y = 435;
			壁パトカー3_y = 535;
			壁パトカー4_y = 635;
		}
		else if (パトカー壁秒数2 == 5) {
			パトカー壁_state = 2;
		}
		else if (パトカー壁秒数2 == 10) {
			パトカー壁ランダム = 0;
			パトカー壁_state = 3;
		}
		else if (パトカー壁秒数2 == 13) {
			パトカー壁ランダム = MathHelper_Random(1, 4);
		}
		else if (パトカー壁秒数2 == 15) {
			パトカー壁_state = 4;
			壁パトカー_x = 1200;
			壁パトカー2_x = 1200;
			壁パトカー3_x = 1200;
			壁パトカー4_x = 1200;
			壁パトカー_y = 335;
			壁パトカー2_y = 435;
			壁パトカー3_y = 535;
			壁パトカー4_y = 635;
		}
		else if (パトカー壁秒数2 == 20) {
			パトカー壁_state = 5;
		}
		else if (パトカー壁秒数2 == 25) {
			パトカー壁ランダム = 0;
			パトカー壁_state = 6;
		}
		else if (パトカー壁秒数2 == 28) {
			パトカー壁ランダム = MathHelper_Random(1, 4);
		}
		else if (パトカー壁秒数2 == 30) {
			パトカー壁_state = 7;
			壁パトカー_x = 1200;
			壁パトカー2_x = 1200;
			壁パトカー3_x = 1200;
			壁パトカー4_x = 1200;
			壁パトカー_y = 335;
			壁パトカー2_y = 435;
			壁パトカー3_y = 535;
			壁パトカー4_y = 635;
		}
		else if (パトカー壁秒数2 == 35) {
			パトカー壁_state = 8;
		}
		else if (パトカー壁秒数2 == 40) {
			パトカー壁ランダム = 0;
			パトカー壁_state = 9;
		}
		else if (パトカー壁秒数2 == 43) {
			パトカー壁ランダム = MathHelper_Random(1, 4);
		}
		else if (パトカー壁秒数2 == 45) {
			パトカー壁_state = 10;
			壁パトカー_x = 1200;
			壁パトカー2_x = 1200;
			壁パトカー3_x = 1200;
			壁パトカー4_x = 1200;
			壁パトカー_y = 335;
			壁パトカー2_y = 435;
			壁パトカー3_y = 535;
			壁パトカー4_y = 635;
		}
		else if (パトカー壁秒数2 == 50) {
			パトカー壁_state = 11;
		}
		else if (パトカー壁秒数2 == 55) {
			パトカー壁ランダム = 0;
			パトカー壁_state = 12;
		}
		else if (パトカー壁秒数2 == 58) {
			パトカー壁ランダム = MathHelper_Random(1, 4);
		}
		else if (パトカー壁秒数2 == 60) {
			パトカー壁_state = 13;
			壁パトカー_x = 1200;
			壁パトカー2_x = 1200;
			壁パトカー3_x = 1200;
			壁パトカー4_x = 1200;
			壁パトカー_y = 335;
			壁パトカー2_y = 435;
			壁パトカー3_y = 535;
			壁パトカー4_y = 635;
		}
		else if (パトカー壁秒数2 == 65) {
		    パトカー壁_state = 14;
		}
		else if (パトカー壁秒数2 == 70) {
		パトカー壁ランダム = 0;
		パトカー壁_state = 15;
		}
		else if (パトカー壁秒数2 == 73) {
		パトカー壁ランダム = MathHelper_Random(1, 4);
		}
		else if (パトカー壁秒数2 == 75) {
		パトカー壁_state = 16;
		壁パトカー_x = 1200;
		壁パトカー2_x = 1200;
		壁パトカー3_x = 1200;
		壁パトカー4_x = 1200;
		壁パトカー_y = 335;
		壁パトカー2_y = 435;
		壁パトカー3_y = 535;
		壁パトカー4_y = 635;
		}
		else if (パトカー壁秒数2 == 80) {
		パトカー壁_state = 17;
		}
		else if (パトカー壁秒数2 == 85) {
		パトカー壁ランダム = 0;
		パトカー壁_state = 18;
		}
		else if (パトカー壁秒数2 == 88) {
		パトカー壁ランダム = MathHelper_Random(1, 4);
		}
		else if (パトカー壁秒数2 == 90) {
		パトカー壁_state = 19;
		壁パトカー_x = 1200;
		壁パトカー2_x = 1200;
		壁パトカー3_x = 1200;
		壁パトカー4_x = 1200;
		壁パトカー_y = 335;
		壁パトカー2_y = 435;
		壁パトカー3_y = 535;
		壁パトカー4_y = 635;
		}
		else if (パトカー壁秒数2 == 95) {
		パトカー壁_state = 20;
		}
		else if (パトカー壁秒数2 == 100) {
		パトカー壁ランダム = 0;
		パトカー壁_state = 21;
		}
		else if (パトカー壁秒数2 == 103) {
		パトカー壁ランダム = MathHelper_Random(1, 4);
		}
		else if (パトカー壁秒数2 == 105) {
		パトカー壁_state = 22;
		壁パトカー_x = 1200;
		壁パトカー2_x = 1200;
		壁パトカー3_x = 1200;
		壁パトカー4_x = 1200;
		壁パトカー_y = 335;
		壁パトカー2_y = 435;
		壁パトカー3_y = 535;
		壁パトカー4_y = 635;
		}
		else if (パトカー壁秒数2 == 110) {
		パトカー壁_state = 23;
		}
		else if (パトカー壁秒数2 == 115) {
		パトカー壁ランダム = 0;
		パトカー壁_state = 24;
		}
		else if (パトカー壁秒数2 == 120) {
		パトカー壁秒数2 = 85;
        }
		
		if (パトカー壁_state == 2 || パトカー壁_state == 5) {
			
			if (パトカー壁ランダム == 1) {
				壁パトカー_x = 壁パトカー_x - 10 - (スピード加速 / 100);
			}
			else if (パトカー壁ランダム == 2) {
				壁パトカー2_x = 壁パトカー2_x - 10 - (スピード加速 / 100);
			}
			else if (パトカー壁ランダム == 3) {
				壁パトカー3_x = 壁パトカー3_x - 10 - (スピード加速 / 100);
			}
			else if (パトカー壁ランダム == 4) {
				壁パトカー4_x = 壁パトカー4_x - 10 - (スピード加速 / 100);
			}
		}
		else if (パトカー壁_state == 8 || パトカー壁_state == 11) {

			if (パトカー壁ランダム == 1) {
				壁パトカー_x = 壁パトカー_x - 10 - (スピード加速 / 100);
				壁パトカー2_x = 壁パトカー2_x - 10 - (スピード加速 / 100);
			}
			else if (パトカー壁ランダム == 2) {
				壁パトカー2_x = 壁パトカー2_x - 10 - (スピード加速 / 100);
				壁パトカー4_x = 壁パトカー4_x - 10 - (スピード加速 / 100);
			}
			else if (パトカー壁ランダム == 3) {
				壁パトカー3_x = 壁パトカー3_x - 10 - (スピード加速 / 100);
				壁パトカー_x = 壁パトカー_x - 10 - (スピード加速 / 100);
			}
			else if (パトカー壁ランダム == 4) {
				壁パトカー4_x = 壁パトカー4_x - 10 - (スピード加速 / 100);
				壁パトカー3_x = 壁パトカー3_x - 10 - (スピード加速 / 100);
			}
		}
		else if (パトカー壁_state == 14 || パトカー壁_state == 17) {

			if (パトカー壁ランダム == 1) {
				壁パトカー_x = 壁パトカー_x - 10 - (スピード加速 / 100);
				壁パトカー2_x = 壁パトカー2_x - 10 - (スピード加速 / 100);
				壁パトカー3_x = 壁パトカー3_x - 10 - (スピード加速 / 100);
			}
			else if (パトカー壁ランダム == 2) {
				壁パトカー2_x = 壁パトカー2_x - 10 - (スピード加速 / 100);
				壁パトカー4_x = 壁パトカー4_x - 10 - (スピード加速 / 100);
				壁パトカー_x = 壁パトカー_x - 10 - (スピード加速 / 100);
			}
			else if (パトカー壁ランダム == 3) {
				壁パトカー3_x = 壁パトカー3_x - 10 - (スピード加速 / 100);
				壁パトカー_x = 壁パトカー_x - 10 - (スピード加速 / 100);
				壁パトカー4_x = 壁パトカー4_x - 10 - (スピード加速 / 100);
			}
			else if (パトカー壁ランダム == 4) {
				壁パトカー4_x = 壁パトカー4_x - 10 - (スピード加速 / 100);
				壁パトカー3_x = 壁パトカー3_x - 10 - (スピード加速 / 100);
				壁パトカー2_x = 壁パトカー2_x - 10 - (スピード加速 / 100);
			}
		}
		else if (パトカー壁_state == 20 || パトカー壁_state == 23) {

			if (パトカー壁ランダム == 1) {
				壁パトカー_x = 壁パトカー_x - 10 - (スピード加速 / 100);
				壁パトカー2_x = 壁パトカー2_x - 10 - (スピード加速 / 100);
				壁パトカー3_x = 壁パトカー3_x - 10 - (スピード加速 / 100);
				壁パトカー4_x = 壁パトカー4_x - 10 - (スピード加速 / 100);
			}
			else if (パトカー壁ランダム == 2) {
				壁パトカー_x = 壁パトカー_x - 10 - (スピード加速 / 100);
				壁パトカー2_x = 壁パトカー2_x - 10 - (スピード加速 / 100);
				壁パトカー3_x = 壁パトカー3_x - 5 - (スピード加速 / 100);
				壁パトカー4_x = 壁パトカー4_x - 5 - (スピード加速 / 100);
			}
			else if (パトカー壁ランダム == 3) {
				壁パトカー_x = 壁パトカー_x - 5 - (スピード加速 / 100);
				壁パトカー2_x = 壁パトカー2_x - 5 - (スピード加速 / 100);
				壁パトカー3_x = 壁パトカー3_x - 10 - (スピード加速 / 100);
				壁パトカー4_x = 壁パトカー4_x - 10 - (スピード加速 / 100);
			}
			else if (パトカー壁ランダム == 4) {
				壁パトカー_x = 壁パトカー_x - 12 - (スピード加速 / 100);
				壁パトカー2_x = 壁パトカー2_x - 9 - (スピード加速 / 100);
				壁パトカー3_x = 壁パトカー3_x - 6 - (スピード加速 / 100);
				壁パトカー4_x = 壁パトカー4_x - 3 - (スピード加速 / 100);
			}
		}
	}
}

void GameMain::当たり判定処理() {

	if (プレイヤー_state == 1) {

		if (逮捕_state == 1) {

			逮捕 += 1;

			プレイヤー_x = プレイヤー_x + 3;
			プレイヤー_y = プレイヤー_y + 3;
			プレイヤー向き_state = 2;

			if (逮捕 == 60) {
				逮捕2 += 1;
				逮捕 = 0;
			}

			if(逮捕2 == 3) {
				スコア = 0;
			}
			else if (逮捕2 == 6) {
				画面_state = 3;
			}
		}
	}
	else if (プレイヤー_state == 0) {

		if (無敵_state == 1) {
			無敵 += 1;

			if (無敵 == 30) {
				無敵2 += 1;
				無敵 = 0;
			}

			if (無敵2 == 1) {
				無敵 = 0;
				無敵2 = 0;
				無敵_state = 0;
			}
		}

		if (衝突_state == 0) {
			衝突エフェクト_x = 0;
			衝突 = 0;
			衝突2 = 0;
		}
		else if (衝突_state == 1) {

			衝突表示時間 += 1;

			if (衝突表示時間 == 40) {
				衝突表示時間2 += 1;
				衝突表示時間 = 0;
			}

			if (衝突表示時間2 == 1) {
				衝突表示時間 = 0;
				衝突表示時間2 = 0;
				衝突_state = 0;
			}

			衝突 += 1;

			if (衝突 == 10) {
				衝突2 += 1;
				衝突 = 0;
			}

			if (衝突2 == 1) {
				衝突エフェクト_x = 110;
			}
			else if (衝突2 == 2) {
				衝突エフェクト_x = 220;
			}
			else if (衝突2 == 3) {
				衝突エフェクト_x = 330;
			}
			else if (衝突2 == 4) {
				衝突エフェクト_x = 440;
			}
		}

		if (＄袋_state == 0) {
			＄袋_x = プレイヤー_x;
			＄袋_y = プレイヤー_y;
		}
		else if (＄袋_state == 1) {

			＄袋_x = ＄袋_x - 10;

			if (＄袋_x < -50) {
				＄袋_state = 0;
			}
		}

		if (＄袋2_state == 0) {
			＄袋2_x = プレイヤー_x;
			＄袋2_y = プレイヤー_y;
		}
		else if (＄袋2_state == 1) {

			＄袋2_x = ＄袋2_x - 10;

			if (＄袋2_x < -50) {
				＄袋2_state = 0;
			}
		}

		if (無敵_state == 0) {

			if (プレイヤー_x + 15 > 赤車_x + 100.0f || プレイヤー_x + 125.0f < 赤車_x + 5 ||
				プレイヤー_y + 25 > 赤車_y + 75.0f || プレイヤー_y + 70.0f < 赤車_y + 10) {
				// 当たっていない

			}
			else {
				// 当たっている
				スコア -= MathHelper_Random(3000000, 5000000);;
				無敵_state = 1;
				衝突_state = 1;
				スピード加速 = 1;
				スピード加速秒 = 0;
				＄袋_state = 1;
				タイム秒 += 1;
				スピード_state = 0;

				if (!衝突SE->IsPlaying())
					衝突SE->Play();
			}

			if (プレイヤー_x + 15 > 青車_x + 100.0f || プレイヤー_x + 120.0f < 青車_x + 10 ||
				プレイヤー_y + 25 > 青車_y + 75.0f || プレイヤー_y + 65.0f < 青車_y + 15) {
				// 当たっていない

			}
			else {
				// 当たっている
				スコア -= MathHelper_Random(3000000, 5000000);;
				無敵_state = 1;
				衝突_state = 1;
				スピード加速 = 1;
				スピード加速秒 = 0;
				＄袋2_state = 1;
				タイム秒 += 1;
				スピード_state = 0;

				if (!衝突SE->IsPlaying())
					衝突SE->Play();
			}

			if (プレイヤー_x > 歩行者_x + 20.0f || プレイヤー_x + 120.0f < 歩行者_x ||
				プレイヤー_y > 歩行者_y + 80.0f || プレイヤー_y + 70.0f < 歩行者_y) {
				// 当たっていない

			}
			else {
				// 当たっている

			}

			if (プレイヤー_x > 追跡パトカー_x + 140.0f || プレイヤー_x + 140.0f < 追跡パトカー_x ||
				プレイヤー_y > 追跡パトカー_y + 90.0f || プレイヤー_y + 88.0f < 追跡パトカー_y) {
				// 当たっていない

			}
			else {
				// 当たっている

				逮捕_state = 1;
				プレイヤー_state = 1;

				if (!衝突SE->IsPlaying())
					衝突SE->Play();

				if (!事故SE->IsPlaying())
					事故SE->Play();
			}

			/*プレイヤー_collision = Rect(プレイヤー_x + 15, プレイヤー_y + 25, プレイヤー_x + 120, プレイヤー_y + 65);
			赤車_collision = Rect(赤車_x + 5, 赤車_y + 10, 赤車_x + 105, 赤車_y + 80);
			青車_collision = Rect(青車_x + 5, 青車_y + 10, 青車_x + 105, 青車_y + 80);
			壁パトカー_collision = Rect(壁パトカー_x + 10, 壁パトカー_y + 15, 壁パトカー_x + 100, 壁パトカー_y + 80);
			壁パトカー2_collision = Rect(壁パトカー2_x + 10, 壁パトカー2_y + 15, 壁パトカー2_x + 100, 壁パトカー2_y + 80);
			壁パトカー3_collision = Rect(壁パトカー3_x + 10, 壁パトカー3_y + 15, 壁パトカー3_x + 100, 壁パトカー3_y + 80);
			壁パトカー4_collision = Rect(壁パトカー4_x + 10, 壁パトカー4_y + 15, 壁パトカー4_x + 100, 壁パトカー4_y + 80);*/

			if (プレイヤー_x + 15 > 壁パトカー_x + 100.0f || プレイヤー_x + 120.0f < 壁パトカー_x + 10 ||
				プレイヤー_y + 25 > 壁パトカー_y + 80.0f || プレイヤー_y + 65.0f < 壁パトカー_y + 15) {
				// 当たっていない

			}
			else {
				// 当たっている

				逮捕_state = 1;
				プレイヤー_state = 1;

				if (!衝突SE->IsPlaying())
					衝突SE->Play();

				if (!事故SE->IsPlaying())
					事故SE->Play();
			}

			if (プレイヤー_x + 15 > 壁パトカー2_x + 100.0f || プレイヤー_x + 120.0f < 壁パトカー2_x + 10 ||
				プレイヤー_y + 25 > 壁パトカー2_y + 80.0f || プレイヤー_y + 65.0f < 壁パトカー2_y + 15) {
				// 当たっていない

			}
			else {
				// 当たっている

				逮捕_state = 1;
				プレイヤー_state = 1;

				if (!衝突SE->IsPlaying())
					衝突SE->Play();

				if (!事故SE->IsPlaying())
					事故SE->Play();
			}

			if (プレイヤー_x + 15 > 壁パトカー3_x + 100.0f || プレイヤー_x + 120.0f < 壁パトカー3_x + 10 ||
				プレイヤー_y + 25 > 壁パトカー3_y + 80.0f || プレイヤー_y + 65.0f < 壁パトカー3_y + 15) {
				// 当たっていない

			}
			else {
				// 当たっている

				逮捕_state = 1;
				プレイヤー_state = 1;

				if (!衝突SE->IsPlaying())
					衝突SE->Play();

				if (!事故SE->IsPlaying())
					事故SE->Play();
			}

			if (プレイヤー_x + 15 > 壁パトカー4_x + 100.0f || プレイヤー_x + 120.0f < 壁パトカー4_x + 10 ||
				プレイヤー_y + 25 > 壁パトカー4_y + 80.0f || プレイヤー_y + 65.0f < 壁パトカー4_y + 15) {
				// 当たっていない

			}
			else {
				// 当たっている

				逮捕_state = 1;
				プレイヤー_state = 1;

				if (!衝突SE->IsPlaying())
					衝突SE->Play();

				if (!事故SE->IsPlaying())
					事故SE->Play();
			}

		}
	}
}

void GameMain::メイン描画() {

	SpriteBatch.Draw(*ゲームプレイ背景, Vector3(背景_x, 0.0f, 3.0f));

	if (プレイヤー向き_state == 0) {
		SpriteBatch.Draw(*プレイヤー, Vector3(プレイヤー_x, プレイヤー_y, 0.0f),RectWH(プレイヤー描画_x, 0,140, 90));
	}
	else if (プレイヤー向き_state == 1) {
		SpriteBatch.Draw(*プレイヤー上, Vector3(プレイヤー_x, プレイヤー_y, 0.0f));
	}
	else if (プレイヤー向き_state == 2) {
		SpriteBatch.Draw(*プレイヤー下, Vector3(プレイヤー_x, プレイヤー_y, 0.0f));
	}

	SpriteBatch.Draw(*赤車, Vector3(赤車_x, 赤車_y, 1.0f));
	SpriteBatch.Draw(*青車, Vector3(青車_x, 青車_y, 1.0f));
	SpriteBatch.Draw(*歩行者, Vector3(歩行者_x, 歩行者_y, 2.0f));
	SpriteBatch.Draw(*歩行者2, Vector3(歩行者2_x, 歩行者2_y, 2.0f));
	SpriteBatch.Draw(*追跡パトカー, Vector3(追跡パトカー_x, 追跡パトカー_y, 0.0f));
	SpriteBatch.Draw(*金額枠, Vector3(0.0f, 5.0f, 3.0f));

	if (衝突_state == 0) {
		SpriteBatch.DrawString(フォント, Vector2(85, 18), Color(255, 255, 0), _T("%d＄"), スコア);
	}
	else if (衝突_state == 1) {
		SpriteBatch.DrawString(フォント, Vector2(85, 18), Color(255, 0, 0), _T("%d＄"), スコア);
	}

	if (ゲームモード設定_state == 0 || ゲームモード設定_state == 1) {
		SpriteBatch.DrawString(フォント2, Vector2(820, 22), Color(0, 0, 255), _T("%d秒"), タイム秒);
		SpriteBatch.Draw(*タイム枠, Vector3(500.0f, 0.0f, 3.0f));
	}
	else if (ゲームモード設定_state == 2) {
		SpriteBatch.DrawString(フォント2, Vector2(700, 22), Color(0, 0, 255), _T("%d秒"), EXモード秒2);
		SpriteBatch.Draw(*EXタイム枠, Vector3(600.0f, 0.0f, 3.0f));
	}

	SpriteBatch.DrawString(フォント2, Vector2(1000, 22), Color(255, 0,0), _T("スピード：%d"), スピード加速);

	/*SpriteBatch.DrawString(フォント2, Vector2(0, 200), Color(0, 0, 255), _T("追跡パトカースピード：%f"), 追跡パトカー_x);*/
	/*if (追跡_state == 0||追跡_state == 2) {
		SpriteBatch.DrawString(フォント2, Vector2(0, 200), Color(0, 0, 255), _T("逃走中"));
	}
	else if (追跡_state == 1) {
		SpriteBatch.DrawString(フォント2, Vector2(0, 200), Color(0, 0, 255), _T("パトカー接近中"));
	}*/
	/*SpriteBatch.DrawString(フォント2, Vector2(0, 250), Color(0, 0, 255), _T("状態：%d"), パトカー壁_state);
	SpriteBatch.DrawString(フォント2, Vector2(0, 300), Color(0, 0, 255), _T("秒数：%d"), パトカー壁秒数2);*/

	if (衝突_state == 1 && プレイヤー_state == 0) {
		//SpriteBatch.Draw(*衝突エフェクト, Vector3((プレイヤー_x + 15),プレイヤー_y, 0.0f),RectWH(衝突エフェクト_x,0,110,70));
		SpriteBatch.Draw(*衝突エフェクト, Vector3((プレイヤー_x - 30),(プレイヤー_y + 90),0.0f), RectWH(衝突エフェクト_x, 0, 110, 70), 1.0f, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector2(2, -2));
	}

	if (逮捕_state == 0) {

		if (＄袋_state == 1) {
			SpriteBatch.Draw(*＄袋, Vector3((＄袋_x - 5), (＄袋_y - 50), 0.0f));
		}

		if (＄袋2_state == 1) {
			SpriteBatch.Draw(*＄袋2, Vector3((＄袋2_x - 5), (＄袋2_y - 50), 0.0f));
		}
	}
}

void GameMain::壁エネミー描画() {

	if (パトカー壁_state == 1 || パトカー壁_state == 4) {

		if (パトカー壁ランダム == 1) {
			SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 330), Color(255, 0, 0, 点滅));
			SpriteBatch.Draw(*危険, Vector3(1100, 330, 0.0f));
		}
		else if (パトカー壁ランダム == 2) {
			SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 430), Color(255, 0, 0, 点滅));
			SpriteBatch.Draw(*危険, Vector3(1100, 430, 0.0f));
		}
		else if (パトカー壁ランダム == 3) {
			SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 530), Color(255, 0, 0, 点滅));
			SpriteBatch.Draw(*危険, Vector3(1100, 530, 0.0f));
		}
		else if (パトカー壁ランダム == 4) {
			SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 630), Color(255, 0, 0, 点滅));
			SpriteBatch.Draw(*危険, Vector3(1100, 630, 0.0f));
		}
	}
	else if (パトカー壁_state == 2 || パトカー壁_state == 5) {

		if (パトカー壁ランダム == 1) {
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー_x, 壁パトカー_y, 0.0f));
		}
		else if (パトカー壁ランダム == 2) {
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー2_x, 壁パトカー2_y, 0.0f));
		}
		else if (パトカー壁ランダム == 3) {
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー3_x, 壁パトカー3_y, 0.0f));
		}
		else if (パトカー壁ランダム == 4) {
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー4_x, 壁パトカー4_y, 0.0f));
		}
	}
	else if (パトカー壁_state == 7 || パトカー壁_state == 10) {

		if (パトカー壁ランダム == 1) {
			SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 330), Color(255, 0, 0, 点滅));
			SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 430), Color(255, 0, 0, 点滅));
			SpriteBatch.Draw(*危険, Vector3(1100, 330, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1100, 430, 0.0f));
		}
		else if (パトカー壁ランダム == 2) {
			SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 430), Color(255, 0, 0, 点滅));
			SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 630), Color(255, 0, 0, 点滅));
			SpriteBatch.Draw(*危険, Vector3(1100, 430, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1100, 630, 0.0f));
		}
		else if (パトカー壁ランダム == 3) {
			SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 530), Color(255, 0, 0, 点滅));
			SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 330), Color(255, 0, 0, 点滅));
			SpriteBatch.Draw(*危険, Vector3(1100, 530, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1100, 330, 0.0f));
		}
		else if (パトカー壁ランダム == 4) {
			SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 630), Color(255, 0, 0, 点滅));
			SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 530), Color(255, 0, 0, 点滅));
			SpriteBatch.Draw(*危険, Vector3(1100, 630, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1100, 530, 0.0f));
		}
	}
	else if (パトカー壁_state == 8 || パトカー壁_state == 11) {

		if (パトカー壁ランダム == 1) {
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー_x, 壁パトカー_y, 0.0f));
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー2_x, 壁パトカー2_y, 0.0f));
		}
		else if (パトカー壁ランダム == 2) {
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー2_x, 壁パトカー2_y, 0.0f));
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー4_x, 壁パトカー4_y, 0.0f));
		}
		else if (パトカー壁ランダム == 3) {
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー3_x, 壁パトカー3_y, 0.0f));
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー_x, 壁パトカー_y, 0.0f));
		}
		else if (パトカー壁ランダム == 4) {
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー4_x, 壁パトカー4_y, 0.0f));
			SpriteBatch.Draw(*壁パトカー, Vector3(壁パトカー3_x, 壁パトカー3_y, 0.0f));
		}
	}
	else if (パトカー壁_state == 13 || パトカー壁_state == 16) {

		if (パトカー壁ランダム == 1) {
			SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 330), Color(255, 0, 0, 点滅));
			SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 430), Color(255, 0, 0, 点滅));
			SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 530), Color(255, 0, 0, 点滅));
			SpriteBatch.Draw(*危険, Vector3(1100, 330, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1100, 430, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1100, 530, 0.0f));
		}
		else if (パトカー壁ランダム == 2) {
			SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 430), Color(255, 0, 0, 点滅));
			SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 630), Color(255, 0, 0, 点滅));
			SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 330), Color(255, 0, 0, 点滅));
			SpriteBatch.Draw(*危険, Vector3(1100, 430, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1100, 630, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1100, 330, 0.0f));
		}
		else if (パトカー壁ランダム == 3) {
			SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 530), Color(255, 0, 0, 点滅));
			SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 330), Color(255, 0, 0, 点滅));
			SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 630), Color(255, 0, 0, 点滅));
			SpriteBatch.Draw(*危険, Vector3(1100, 530, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1100, 330, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1100, 630, 0.0f));
		}
		else if (パトカー壁ランダム == 4) {
			SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 630), Color(255, 0, 0, 点滅));
			SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 530), Color(255, 0, 0, 点滅));
			SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 430), Color(255, 0, 0, 点滅));
			SpriteBatch.Draw(*危険, Vector3(1100, 630, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1100, 530, 0.0f));
			SpriteBatch.Draw(*危険, Vector3(1100, 430, 0.0f));
		}
	}
	else if (パトカー壁_state == 14 || パトカー壁_state == 17) {

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
	else if (パトカー壁_state == 19 || パトカー壁_state == 22) {

	if (パトカー壁ランダム == 1) {
		SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 330), Color(255, 0, 0, 点滅));
		SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 430), Color(255, 0, 0, 点滅));
		SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 530), Color(255, 0, 0, 点滅));
		SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 630), Color(255, 0, 0, 点滅));
		SpriteBatch.Draw(*危険, Vector3(1100, 330, 0.0f));
		SpriteBatch.Draw(*危険, Vector3(1100, 430, 0.0f));
		SpriteBatch.Draw(*危険, Vector3(1100, 530, 0.0f));
		SpriteBatch.Draw(*危険, Vector3(1100, 630, 0.0f));
	}
	    else if (パトカー壁ランダム == 2) {
		SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(900, 330), Color(255, 0, 0, 点滅));
		SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(900, 430), Color(255, 0, 0, 点滅));
		SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 530), Color(255, 0, 0, 点滅));
		SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 630), Color(255, 0, 0, 点滅));
		SpriteBatch.Draw(*危険, Vector3(1000, 330, 0.0f));
		SpriteBatch.Draw(*危険, Vector3(1000, 430, 0.0f));
		SpriteBatch.Draw(*危険, Vector3(1100, 530, 0.0f));
		SpriteBatch.Draw(*危険, Vector3(1100, 630, 0.0f));
	}
	    else if (パトカー壁ランダム == 3) {
		SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 330), Color(255, 0, 0, 点滅));
		SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 430), Color(255, 0, 0, 点滅));
		SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(900, 530), Color(255, 0, 0, 点滅));
		SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(900, 630), Color(255, 0, 0, 点滅));
		SpriteBatch.Draw(*危険, Vector3(1100, 330, 0.0f));
		SpriteBatch.Draw(*危険, Vector3(1100, 430, 0.0f));
		SpriteBatch.Draw(*危険, Vector3(1000, 530, 0.0f));
		SpriteBatch.Draw(*危険, Vector3(1000, 630, 0.0f));
	}
	    else if (パトカー壁ランダム == 4) {
		SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(900, 330), Color(255, 0, 0, 点滅));
		SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(950, 430), Color(255, 0, 0, 点滅));
		SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1000, 530), Color(255, 0, 0, 点滅));
		SpriteBatch.DrawString(注意フォント, _T("!!"), Vector2(1050, 630), Color(255, 0, 0, 点滅));
		SpriteBatch.Draw(*危険, Vector3(1150, 330, 0.0f));
		SpriteBatch.Draw(*危険, Vector3(1100, 430, 0.0f));
		SpriteBatch.Draw(*危険, Vector3(1050, 530, 0.0f));
		SpriteBatch.Draw(*危険, Vector3(1000, 630, 0.0f));
	}
	}
	else if (パトカー壁_state == 20 || パトカー壁_state == 23) {

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

void GameMain::操作説明処理() {

	背景_x = 背景_x - 38 - (スピード加速 / 100);
	if (背景_x <= -2720.0f) {
		背景_x = 0.0f;
	}

	if (Keystate.IsKeyDown(Keys_W) || pad.Buttons[3] != 0) {
		スピード_y = スピード_y - 0.2 - (スピード加速 / 1000);

		if (スピード_y < -10) {
			スピード_y = -10;
		}

		if (!上下移動SE->IsPlaying())
			上下移動SE->Play();

		プレイヤー向き_state = 1;
	}

	if (Keystate.IsKeyDown(Keys_S) || pad.Buttons[0] != 0) {
		スピード_y = スピード_y + 0.2 + (スピード加速 / 1000);

		if (スピード_y > 10) {
			スピード_y = 10;
		}

		if (!上下移動SE2->IsPlaying())
			上下移動SE2->Play();

		プレイヤー向き_state = 2;
	}

	if (Keystate.IsKeyUp(Keys_W) && pad.Buttons[0] == 0 && Keystate.IsKeyUp(Keys_S) && pad.Buttons[3] == 0) {
		if (スピード_y > 0) {
			スピード_y = スピード_y - 0.1;
		}

		if (スピード_y < 0) {
			スピード_y = スピード_y + 0.1;
		}

		プレイヤー向き_state = 0;
	}

	if (プレイヤー_y > 295) {

		スピード加速秒 = スピード加速秒 + 1.0f;

		if (スピード加速秒 == 30) {
			スピード加速 = スピード加速 + 1;
			スピード加速秒 = 0;
		}
	}
	else if (プレイヤー_y < 295) {

		スピード加速秒2 = スピード加速秒2 + 2.0f;

		if (スピード加速秒2 == 30) {
			スピード加速 = スピード加速 - 1;
			スピード加速秒2 = 0;
		}
	}

	if (スピード加速 < -10) {
		スピード加速 = -10;
	}

	プレイヤー_x = プレイヤー_x + スピード_x;
	プレイヤー_y = プレイヤー_y + スピード_y;

	if (プレイヤー_x > 1000) {
		プレイヤー_x = 1000;
	}

	if (プレイヤー_x < 0) {
		プレイヤー_x = 0;
	}

	if (プレイヤー_y < 245) {
		プレイヤー_y = 245;
		プレイヤー向き_state = 0;
		if (スピード_y <= -6)
			スピード_y = -5;
	}

	if (プレイヤー_y > 650) {
		プレイヤー_y = 650;
		プレイヤー向き_state = 0;
		if (スピード_y >= 6)
			スピード_y = 5;
	}

	if (説明_state == 0) {

		if (Key_buffer.IsPressed(Keys_E) || pad_buffer.IsPressed(DIJOFS_BUTTON7)) {
			画面_state = 0;
			エンジン起動SE->Stop();
		}

		if (Key_buffer.IsPressed(Keys_Q) || pad_buffer.IsPressed(DIJOFS_BUTTON7)) {
			説明_state = 1;
		}
	}
	else if (説明_state == 1) {

		if (Key_buffer.IsPressed(Keys_E) || pad_buffer.IsPressed(DIJOFS_BUTTON7)) {
			説明_state = 0;
		}

	}

	if (!走行中SE->IsPlaying())
		走行中SE->Play();
}

void GameMain::操作説明描画() {

	SpriteBatch.Draw(*ゲームプレイ背景, Vector3(背景_x, 0.0f, 10.0f));

	if (プレイヤー_state == 0) {

		if (プレイヤー向き_state == 0) {
			SpriteBatch.Draw(*プレイヤー2, Vector3(プレイヤー_x, プレイヤー_y, 0.0f));
		}
		else if (プレイヤー向き_state == 1) {
			SpriteBatch.Draw(*プレイヤー上, Vector3(プレイヤー_x, プレイヤー_y, 0.0f));
		}
		else if (プレイヤー向き_state == 2) {
			SpriteBatch.Draw(*プレイヤー下, Vector3(プレイヤー_x, プレイヤー_y, 0.0f));
		}
	}

	if (説明_state == 0) {
		SpriteBatch.Draw(*ゲーム操作説明背景, Vector3(0.0f, 0.0f, 0.0f));
		SpriteBatch.DrawString(フォント, Vector2(30, 10), Color(255, 0, 0), _T("Q ゲームシステム　　　　　　   　   　　　    E タイトルへ戻る"));
		SpriteBatch.DrawString(フォント, Vector2(30, 70), Color(255, 0, 0), _T("ゲームプレイ中の操作方法"));
		SpriteBatch.DrawString(フォント, Vector2(30, 120), Color(255, 0, 0), _T("キーボード: 上への移動 W, 下への移動 S"));
		SpriteBatch.DrawString(フォント, Vector2(30, 170), Color(255, 0, 0), _T("ゲームパッド: 上への移動 3ボタン, 下への移動 0ボタン"));
		SpriteBatch.DrawString(フォント, Vector2(30, 220), Color(255, 0, 0), _T("Eキー =  7ボタン, Qキー = 6ボタン, Fキー = 1ボタン"));
	}
	else if (説明_state == 1) {
		SpriteBatch.Draw(*ゲームシステム背景, Vector3(0.0f, 0.0f, 0.0f));
		SpriteBatch.DrawString(フォント操作説明, Vector2(30, 10), Color(124, 252, 0), _T("ゲームシステムの説明"));
		SpriteBatch.DrawString(フォント操作説明, Vector2(30, 40), Color(255, 241, 0), _T("＄ = スコア、ライフ。敵に衝突することで減り、０になったらゲームオーバー。"));
		SpriteBatch.DrawString(フォント操作説明, Vector2(30, 70), Color(148, 0, 211), _T("タイム = 時間経過で減っていき、タイムが０になったらゲームクリア。"));
		SpriteBatch.DrawString(フォント操作説明, Vector2(30, 100), Color(255, 0, 0), _T("敵 = パトカー、一般車。当たっても大丈夫 = 歩行者。"));
		SpriteBatch.DrawString(フォント操作説明, Vector2(30, 130), Color(255, 140, 0), _T("敵を避け続ければ加速していき、敵などの移動スピードが速くなり、プレイヤーの操作が速くなり、"));
		SpriteBatch.DrawString(フォント操作説明, Vector2(30, 160), Color(255, 140, 0), _T("タイムの減る秒数も増える。歩道は敵と衝突しないので安置だがスピードが遅くなり、タイムが"));
		SpriteBatch.DrawString(フォント操作説明, Vector2(30, 190), Color(255, 140, 0), _T("増えていく。タイムが55秒を超えると後方からパトカーが接近してくる。そのパトカーに当たった"));
		SpriteBatch.DrawString(フォント操作説明, Vector2(30, 220), Color(255, 140, 0), _T("場合はゲームオーバーとなる。一定時間で壁のパトカーがランダム（４パターン)で出現する。"));
		SpriteBatch.DrawString(フォント操作説明, Vector2(30, 250), Color(255, 140, 0), _T("出現する場所は【!!】が表示された所。時間が経てば経つほどこのパトカーは多く出現する。"));
		SpriteBatch.DrawString(フォント操作説明, Vector2(30, 280), Color(255, 140, 0), _T("このパトカーに当たった場合は逮捕されてゲームオーバーとなる。"));
		SpriteBatch.DrawString(フォント操作説明, Vector2(30, 310), Color(255, 140, 0), _T("スピード30以上で一秒で二秒減る。スピード50以上で一秒で三秒減る。　　　　E 操作画面に戻る"));
	}
}

void GameMain::ゲームオーバー処理() {

	ゲームプレイBGM->Stop();
	サイレンSE->Stop();
	サイレンSE2->Stop();
	走行中SE->Stop();
	衝突SE->Stop();
	通過SE->Stop();

	if (!サイレンSE3->IsPlaying())
		サイレンSE3->Play();

	if (!シャッターSE->IsPlaying())
		シャッターSE->Play();

	if (ハイスコア < スコア3) {
		ハイスコア = スコア3;
	}

	if(ゲームモード設定_state == 2) {

		if (EXモード秒3 < EXモード秒2) {
			EXモード秒3 = EXモード秒2;
		}
	}

	if (Key_buffer.IsPressed(Keys_E) || pad_buffer.IsPressed(DIJOFS_BUTTON7)) {
		画面_state = 0;
	}
}

void GameMain::ゲームオーバー描画() {

	SpriteBatch.Draw(*ゲームオーバー背景, Vector3(0.0f, 0.0f, 0.0f));
	SpriteBatch.DrawString(フォント, Vector2(0, 20), Color(0, 255, 0), _T("スコア：%d"), スコア2);
	SpriteBatch.DrawString(フォント2, Vector2(0, 100), Color(0, 0, 255), _T("タイム：%d秒"),EXモード秒2);
	SpriteBatch.DrawString(フォント3, Vector2(900, 640), Color(255, 255, 0), _T("E タイトルへ戻る"));
}

void GameMain::ゲームクリア処理() {

	ゲームプレイBGM->Stop();
	サイレンSE->Stop();
	サイレンSE2->Stop();
	走行中SE->Stop();
	衝突SE->Stop();
	通過SE->Stop();

	if (ゲームモード設定_state == 0) {

		if (逃走タイム_state == 0) {
			逃走タイム秒3 = 逃走タイム秒2;
			逃走タイム_state = 1;
		}
		else if (逃走タイム_state == 1) {

			if (逃走タイム秒2 < 逃走タイム秒3) {
				逃走タイム秒3 = 逃走タイム秒2;
			}
		}

		if (ハイスコア < スコア3) {
			ハイスコア = スコア3;
		}
	}
	if (ゲームモード設定_state == 1) {

		if (逃走タイム_state == 0) {
			ハード逃走タイム秒3 = 逃走タイム秒2;
			逃走タイム_state = 1;
		}
		else if (逃走タイム_state == 1) {

			if (逃走タイム秒2 < ハード逃走タイム秒3) {
				ハード逃走タイム秒3 = 逃走タイム秒2;
			}
		}

		if (ハードハイスコア < スコア3) {
			ハードハイスコア = スコア3;
		}
	}

	if (Key_buffer.IsPressed(Keys_E) || pad_buffer.IsPressed(DIJOFS_BUTTON7)) {
		画面_state = 0;
	}
}

void GameMain::ゲームクリア描画() {

	SpriteBatch.Draw(*クリア背景, Vector3(0.0f, 0.0f, 0.0f));
	SpriteBatch.Draw(*クリア画面金額枠, Vector3(460.0f, 160.0f, 0.0f));
	SpriteBatch.DrawString(フォント, Vector2(430, 185), Color(255, 255, 0), _T("報酬:%d＄"), スコア2);
	SpriteBatch.DrawString(フォント2, Vector2(0, 640), Color(0, 0, 255), _T("今回の逃走成功タイム：%d秒"),逃走タイム秒2);
	SpriteBatch.DrawString(フォント, Vector2(900, 640), Color(255, 0, 0), _T("E タイトルへ戻る"));
}

void GameMain::難易度設定処理() {

	if (ゲームモード設定_state == 0) {

		if (Key_buffer.IsPressed(Keys_W) || pad_buffer.IsPressed(DIJOFS_BUTTON3)) {
			ゲームモード設定_state = 1;
		}
	}
	else if (ゲームモード設定_state == 1) {

		if (Key_buffer.IsPressed(Keys_W) || pad_buffer.IsPressed(DIJOFS_BUTTON3)) {
			ゲームモード設定_state = 2;
		}
	}
	else if (ゲームモード設定_state == 2) {

		if (Key_buffer.IsPressed(Keys_W) || pad_buffer.IsPressed(DIJOFS_BUTTON3)) {
			ゲームモード設定_state = 0;
		}
	}

	if (Key_buffer.IsPressed(Keys_E) || pad_buffer.IsPressed(DIJOFS_BUTTON7)) {
		画面_state = 0;
	}
}

void GameMain::難易度設定描画() {

	SpriteBatch.Draw(*難易度設定背景, Vector3(0.0f, 0.0f, 0.0f));
	/*SpriteBatch.DrawString(フォント3, Vector2(10, 50), Color(255, 140, 0), _T("タイムの設定(60 or 120) ※ノーマルモードのみ適応。"));
	SpriteBatch.DrawString(フォント3, Vector2(10, 100), Color(255, 140, 0), _T("W で変更。現在のタイム = % d"),タイム秒設定);*/
	SpriteBatch.DrawString(フォント3, Vector2(10, 50), Color(255, 140, 0), _T("ゲームモードの設定"));

	if (ゲームモード設定_state == 0) {
		SpriteBatch.DrawString(フォント3, Vector2(10, 100), Color(255, 140, 0), _T("W で変更。現在のゲームモード = ノーマルモード"));
	}
	else if (ゲームモード設定_state == 1) {
		SpriteBatch.DrawString(フォント3, Vector2(10, 100), Color(255, 140, 0), _T("W で変更。現在のゲームモード = ハードモード"));
	}
	else if (ゲームモード設定_state == 2) {
		SpriteBatch.DrawString(フォント3, Vector2(10, 100), Color(255, 140, 0), _T("W で変更。現在のゲームモード = EXモード"));
	}

	SpriteBatch.DrawString(フォント3, Vector2(10, 150), Color(255, 140, 0), _T("ノーマルモード = 基本的なゲームモード。"));
	SpriteBatch.DrawString(フォント3, Vector2(10, 200), Color(255, 140, 0), _T("ハードモード = ノーマルモードよりタイムが60秒増えたゲームモード。"));
	SpriteBatch.DrawString(フォント3, Vector2(10, 250), Color(255, 140, 0), _T("EXモード = どれだけ長く逃走ができるかを目指すゲームモード。"));
	SpriteBatch.DrawString(フォント3, Vector2(900, 640), Color(0, 255, 0), _T("E タイトルへ戻る"));
}