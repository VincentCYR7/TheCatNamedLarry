#pragma once

# include <Siv3D.hpp>
# include "Entity.h"
# include "Player.h"
# include "GamePlatform.h"
# include "CollisionManager.h"


class Game : public SceneManager<String>::Scene
{
public:

	Game(const InitData& init);
	~Game();

	void update() override;

	void draw() const override;

	void drawFadeIn(double t) const override;

	void drawFadeOut(double t) const override;

	bool scrolling;

private:

	Texture m_emoji;

	Stopwatch m_stopwatch;
	const Texture larryTexture{U"Assets/Larry/Larry0.png"};
	const Texture platformTex{ U"Assets/rooftop.png" };
	const Texture nightSky{U"Assets/nightSky.png"};
	const Texture buildings{U"Assets/buildings.png"};
	const Vec2 test{400,300};
	std::vector<std::unique_ptr<Entity>> entities;
	std::vector<GamePlatform*> platforms;


	Player* player;
	CollisionManager* collisionManager;

	double accumulator = 0.0;
	const double h = 1.0/120.0;

};