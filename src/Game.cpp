# include "Game.h"


Game::Game(const InitData& init)
	: IScene{ init }
{
	Window::Resize(1280, 720);
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.7, 0.7, 0.7 });



	king = new KingMoveManager(100, 75, 120, 100, 10);

	player = new Player(Vec2{ 400,300 }, knightTexture);

	queen = new Entity(king->queenPos, queenTexture);

	for (int i = 0; i < 8; i++) {
		enemyArray.push_back(new Enemy(Vec2{ Scene::Width() + i * 200,Random(100, Scene::Height() - 100) }, enemyTexture));
	}

	for (int i = 0; i < 20; i++) {
		grassArray.push_back(new Entity(Vec2{ Random(200,Scene::Width() - 200),Random(100, Scene::Height() - 100) }, grassTexture));
	}

	entities.push_back(std::unique_ptr<Player>(player));
	entities.push_back(std::unique_ptr<Entity>(queen));
	//entities.push_back(std::make_unique<King>(Vec2{200,350}, kingTexture));
	// make random grass
	for (int i = 0; i < grassArray.size(); i++) {
		entities.push_back(std::unique_ptr<Entity>(grassArray[i]));
	}
	for (int i = 0; i < enemyArray.size(); i++) {
		entities.push_back(std::unique_ptr<Enemy>(enemyArray[i]));
	}


	Vec2 kingPos = Vec2(150, 250); 		// King starting position

	scrolling = true;

}

Game::~Game()
{
}

void Game::update()
{
	queen->SetPos(king->queenPos);
	if (not m_stopwatch.isStarted())
	{
		m_stopwatch.start();
	}

	for (int i = 0; i < enemyArray.size(); i++) {
		if (!enemyArray[i]->fallen) {
			if (enemyArray[i]->collider.intersects(king->collider)) {
				king->OnKingDamaged();
				enemyArray[i]->MoveTo(Vec2{ Scene::Width() + 100,Random(100, Scene::Height() - 100) });
			}

			if (enemyArray[i]->collider.intersects(player->hitbox) && player->isAttacking) {
				int nearestTrap = -1;
				for (int j = 0; j < trapManager.trapArr.size(); j++) {

					if (!trapManager.trapArr[j].activated && nearestTrap == -1)
						nearestTrap = j;

				}

				if (nearestTrap != -1) {
					enemyArray[i]->PushTo(trapManager.trapArr[nearestTrap].collider.center, 10.0);

				}else enemyArray[i]->PushTo(Vec2{enemyArray[i]->collider.center.x + 200, enemyArray[i]->collider.center.y}, 10.0);


			}
		}

		for (int j = 0; j < trapManager.trapArr.size(); j++) {

			if (trapManager.trapArr[j].collider.intersects(enemyArray[i]->collider) && enemyArray[i]->movingTime > 0.0) {
				enemyArray[i]->fallen = true;
				continue;
			}

		}

		if (enemyArray[i]->collider.x < -100) {
			enemyArray[i]->MoveTo(Vec2{ Scene::Width() + 100,Random(100, Scene::Height() - 100) });
			enemyArray[i]->fallen = false;
		}

	}

	for (int i = 0; i < grassArray.size(); i++) {
		if(grassArray[i]->GetPos().x < -100)
			grassArray[i]->SetPos(Vec2{ Scene::Width() + 100,Random(100, Scene::Height() - 100) });
	}

	player->scrolling = !king->fallen;

	trapManager.Update(*king, *player, enemyArray);

	std::sort(entities.begin(), entities.end(),
	[](const auto& a, const auto& b) { return a->getY() < b->getY(); });

	king->Update();
	scrolling = !king->fallen;

	if (king->ReturnGameStatus() & 0b0100)
		changeScene(U"Win", 1.5s); //WON

	if (king->ReturnGameStatus() & 0b0010)
		changeScene(U"Lose", 1.5s); //LOST
}

void Game::draw() const
{
	//Scene::SetBackground(ColorF(0.0, 0.6, 0.4));

	const double t = m_stopwatch.sF();

	const Vec2 pos{ (Scene::Size().x / 2 + Periodic::Sine1_1(3s, t) * Scene::Size().y / 2), Scene::Size().y / 2 };

	//m_emoji.drawAt(pos);




	for (auto& e : entities) { e->update(scrolling); e->draw(); }


	king->Draw();
}

void Game::drawFadeIn(double t) const
{
	draw();
	Circle{ Scene::Size().x / 2, Scene::Size().y / 2, Scene::Size().x }
	.drawFrame(((1 - t) * Scene::Size().x), 0, ColorF{ 0.2, 0.3, 0.4 });
}

void Game::drawFadeOut(double t) const
{
	draw();

	Circle{ Scene::Size().x / 2, Scene::Size().y / 2, Scene::Size().x }
	.drawFrame((t * Scene::Size().x), 0, ColorF{ 0.2, 0.3, 0.4 });
}

