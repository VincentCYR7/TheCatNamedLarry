# include "Game.h"


Game::Game(const InitData& init)
	: IScene{ init }
{
	Window::Resize(1280, 720);
	Scene::SetBackground(ColorF{ 0.7, 0.7, 0.7 });


	player = new Player(Vec2{ 400,300 }, larryTexture, Size(77,77));

	entities.push_back(std::unique_ptr<Player>(player));
	
	collisionManager = new CollisionManager();




	for (int i = 0; i < 5; ++i) {

    	Vec2 pos{ 100 + i * 100, 500 }; 
    	std::unique_ptr<Entity> entityPtr = std::make_unique<GamePlatform>(pos, platformTex, Size{100, 100});

    	entities.push_back(std::move(entityPtr));

		platforms.push_back(static_cast<GamePlatform*>(entities.back().get()));

	}


	scrolling = false;

}

Game::~Game()
{
}

void Game::update()
{

	accumulator += Scene::DeltaTime();

	while (accumulator >= h) {
		//collisionManager->checkGrounded(player, platforms);
		collisionManager->resolveGrounding(player, platforms);
		accumulator -= h;
		player->update();
		
	}

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

	nightSky.scaled(0.35).drawAt(Vec2{Scene::Size().x / 2, Scene::Size().y / 2});
	buildings.scaled(0.35).drawAt(Vec2{Scene::Size().x / 2, Scene::Size().y / 2});
 
	const Vec2 pos{ (Scene::Size().x / 2 + Periodic::Sine1_1(3s, t) * Scene::Size().y / 2), Scene::Size().y / 2 };

	for (auto& e : entities) { //e->update(scrolling); 
		e->draw(); 
	}

}

void Game::drawFadeIn(double t) const
{
	draw();
	Circle{ Scene::Size().x / 2, Scene::Size().y / 2, Scene::Size().x }
	.drawFrame(((1 - t) * Scene::Size().x), 0, ColorF{ 0, 0, 0 });
}

void Game::drawFadeOut(double t) const
{
	draw();

	Circle{ Scene::Size().x / 2, Scene::Size().y / 2, Scene::Size().x }
	.drawFrame((t * Scene::Size().x), 0, ColorF{ 0.2, 0.3, 0.4 });
}

