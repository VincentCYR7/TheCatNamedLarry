# include "Game.h"


Game::Game(const InitData& init)
	: IScene{ init }
{
	Window::Resize(1280, 720);
	Scene::SetBackground(ColorF{ 0.7, 0.7, 0.7 });



	player = new Player(Vec2{ 400,300 }, larryTexture, Size(100,100));

	entities.push_back(std::unique_ptr<Player>(player));

	scrolling = true;

}

Game::~Game()
{
}

void Game::update()
{
	//queen->SetPos(king->queenPos);
	if (not m_stopwatch.isStarted())
	{
		m_stopwatch.start();
	}

	std::sort(entities.begin(), entities.end(),
	[](const auto& a, const auto& b) { return a->getY() < b->getY(); });

}

void Game::draw() const
{
	const double t = m_stopwatch.sF();

	const Vec2 pos{ (Scene::Size().x / 2 + Periodic::Sine1_1(3s, t) * Scene::Size().y / 2), Scene::Size().y / 2 };

	for (auto& e : entities) { e->update(scrolling); e->draw(); }

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

