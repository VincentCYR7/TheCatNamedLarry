# include "Game.h"


Game::Game(const InitData& init)
	: IScene{ init }
{
	Window::Resize(1280, 720);
	Scene::SetBackground(ColorF{ 0.7, 0.7, 0.7 });


	player = new Player(Vec2{ 400,300 }, larryTexture, Size(77,77));

	entities.push_back(std::unique_ptr<Player>(player));
	
	collisionManager = new CollisionManager();

	//Vec2 startCamPos = Vec2{player->getHitbox().center().x - 700, player->getHitbox().center().y - 500};
	//m_camera.setCenter(startCamPos);
	m_camera.setCenter(player->getHitbox().center());
    m_camera.setScale(1.0);
	//m_deadZone.setCenter(startCamPos);



	for (int i = 0; i < 16; ++i) {
		Vec2 pos;
		if ( i > 11 ) {
			pos = Vec2{ 200 + i * 100, 600 }; 
		} else if (i > 9) {
			pos = Vec2{ 100 + i * 100, 500};
		} else if(i > 4) {
			pos = Vec2{ 100 + i * 100, 400 }; 
		} else {
			pos = Vec2{ 100 + i * 100, 500 }; 
		}
    	
    	std::unique_ptr<Entity> entityPtr = std::make_unique<GamePlatform>(pos, platformTex, Size{98, 98});

    	entities.push_back(std::move(entityPtr));

		platforms.push_back(static_cast<GamePlatform*>(entities.back().get()));

	}
}

Game::~Game()
{
}

void Game::update()
{

	accumulator += Scene::DeltaTime();

	while (accumulator >= h) {
		collisionManager->checkCollisions(entities);
		collisionManager->resolveGrounding(player, platforms);
		accumulator -= h;
		player->fixedUpdate();
		updateCamera();
	}
	player->update();

	std::sort(entities.begin(), entities.end(),
	[](const auto& a, const auto& b) { return a->getY() < b->getY(); });
	
	platforms.clear();
	platforms.reserve(entities.size());
	for (auto& e : entities) {
		if (auto* p = dynamic_cast<GamePlatform*>(e.get()))
			platforms.push_back(p);
	}

	
}

void Game::updateCamera() {

	const s3d::Vec2 camCenter = m_camera.getCenter();
	const s3d::Vec2 playerCenter = player->getHitbox().center();

	const s3d::Vec2 rel = playerCenter - camCenter;

	s3d::Vec2 camMove{ 0, 0 };


	if (rel.x < m_deadZone.leftX) camMove.x = rel.x - m_deadZone.leftX;
	else if (rel.x > m_deadZone.rightX) camMove.x = rel.x - m_deadZone.rightX;

	if (rel.y < m_deadZone.topY) camMove.y = rel.y - m_deadZone.topY;
	else if (rel.y > m_deadZone.bottomY) camMove.y = rel.y - m_deadZone.bottomY;

	if (camMove != s3d::Vec2{ 0, 0 }) {
		s3d::Vec2 newCenter = camCenter + camMove;
		newCenter.x = std::round(newCenter.x);
		newCenter.y = std::round(newCenter.y);
		m_camera.setCenter(newCenter);
	}

}

void Game::draw() const
{
	const double t = m_stopwatch.sF();

	nightSky.scaled(0.35).drawAt(Vec2{Scene::Size().x / 2, Scene::Size().y / 2});
	buildings.scaled(0.35).drawAt(Vec2{Scene::Size().x / 2, Scene::Size().y / 2});
 
	const Vec2 pos{ (Scene::Size().x / 2 + Periodic::Sine1_1(3s, t) * Scene::Size().y / 2), Scene::Size().y / 2 };

	{
        const auto _ = m_camera.createTransformer(); // RAII: applies camera to all draws in this scope
        for (auto& e : entities) {
            e->draw();
        }

		//Circle{ m_camera.getCenter(), 5 }.draw(Palette::Red);
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

