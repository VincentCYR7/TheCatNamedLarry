//Main.cpp
/*
# include <Siv3D.hpp> // Siv3D v0.6.14
#include "TrapManager.h"

using App = SceneManager<String>;


class Title : public App::Scene {
	
};


void MainZ()
{
	const Font font{ FontMethod::MSDF, 48, Typeface::Bold };
	TrapManager trapManager;

	// PLACEHOLDER CLASSES
	KingMoveManager* king = new KingMoveManager(100, 30, 120, 100, 10);
	EnemyManagerP enemyManagerP;
	PlayerP player;

	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	double time;


	const Texture emoji{ U"🧏"_emoji };

	double speed = 200.0;

	// プレイヤーの X 座標 | Player's X position
	double playerPosX = 400;
	double playerPosY = 400;

	bool isPlayerFacingRight = true;

	while (System::Update())
	{
		if (KeyA.pressed())
		{
			// プレイヤーが左に移動する | Player moves left
			playerPosX = Max((playerPosX - speed * Scene::DeltaTime()), 60.0);
			isPlayerFacingRight = false;
		}

		if (KeyW.pressed())
		{
			// プレイヤーが左に移動する | Player moves left
			playerPosY = Max((playerPosY - speed * Scene::DeltaTime()), 60.0);
		}

		if (KeyS.pressed())
		{
			// プレイヤーが左に移動する | Player moves left
			playerPosY = Min((playerPosY + speed * Scene::DeltaTime()), 740.0);
		}

		// 右キーが押されていたら | If right key is pressed
		if (KeyD.pressed())
		{
			// プレイヤーが右に移動する | Player moves right
			playerPosX = Min((playerPosX + speed * Scene::DeltaTime()), 740.0);
			isPlayerFacingRight = true;
		}

		if(KeySpace.down()){
			trapManager.TrapsPause(false);
		}

		
		trapManager.Update(*king, player, enemyManagerP.enemyArr);

		// プレイヤーを描く | Draw the player
		emoji.scaled(0.75).mirrored(isPlayerFacingRight).drawAt(playerPosX, playerPosY);
		//font(U"delta time: {}"_fmt(trapManager.deltaTime)).draw(32, Vec2{ 20, 70 }, ColorF{ 1 });

		king->Draw();
		enemyManagerP.Draw();
		player.Update();
	}
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要な場合があります。
//


*/